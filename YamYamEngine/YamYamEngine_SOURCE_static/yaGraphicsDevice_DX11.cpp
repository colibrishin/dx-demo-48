#include "yaGraphicsDevice_DX11.h"
#include "yaApplication.h"
#include "yaRenderer.h"
#include "yaMesh.h"
#include "yaShader.h"
#include "yaConstantBuffer.h"
#include <WICTextureLoader.h>

extern ya::Application application;


namespace ya::graphics
{
    GraphicsDevice_DX11::GraphicsDevice_DX11()
    {
        HWND hWnd = application.GetHwnd();

        // Device , Device Context
        UINT DeviceFlag = D3D11_CREATE_DEVICE_DEBUG;
        D3D_FEATURE_LEVEL FeatureLevel = (D3D_FEATURE_LEVEL)0;

        ID3D11Device* pDevice = nullptr;
        HRESULT hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr
                                        , DeviceFlag, nullptr, 0
                                        , D3D11_SDK_VERSION
                                        , mDevice.GetAddressOf()
                                        , &FeatureLevel
                                        , mContext.GetAddressOf());

        DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

        swapChainDesc.OutputWindow = application.GetHwnd();	                // Front Buffer 를 출력시킬 윈도우 핸들
        swapChainDesc.Windowed = true;		                // 윈도우, 전체화면 모드
        swapChainDesc.BufferCount = 2;
        swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD; // 이전 프레임 장면을 유지하지 않는다.

        swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        swapChainDesc.BufferDesc.Width = application.GetWidth();
        swapChainDesc.BufferDesc.Height = application.GetHeight();
        swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        swapChainDesc.BufferDesc.RefreshRate.Numerator = 144;
        swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
        swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
        swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

        swapChainDesc.SampleDesc.Count = 1;
        swapChainDesc.SampleDesc.Quality = 0;

        if (!CreateSwapChain(swapChainDesc))
            return;

        // Get render target by Swapchain
        hr = mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)mFrameBuffer.GetAddressOf());

        // Create Rendertarget view
        hr = mDevice->CreateRenderTargetView(mFrameBuffer.Get(), nullptr, mRenderTargetView.GetAddressOf());
        


        // DepthStencilTexture
        D3D11_TEXTURE2D_DESC texdesc = {};

        texdesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;

        texdesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
        texdesc.CPUAccessFlags = 0;

        texdesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        texdesc.Width = (UINT)1600;
        texdesc.Height = (UINT)900;
        texdesc.ArraySize = 1;

        texdesc.SampleDesc.Count = 1;
        texdesc.SampleDesc.Quality = 0;

        texdesc.MipLevels = 0;
        texdesc.MiscFlags = 0;

        if (!CreateTexture(texdesc))
            return;


        //RECT winRect;
        //GetClientRect(application.GetHwnd(), &winRect);
        //mViewPort = { 0.0f, 0.0f, (FLOAT)(winRect.right - winRect.left), (FLOAT)(winRect.bottom - winRect.top)};
        //BindViewports(&mViewPort);
        //mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
    }

    GraphicsDevice_DX11::~GraphicsDevice_DX11()
    {

    }

    bool GraphicsDevice_DX11::CreateSwapChain(DXGI_SWAP_CHAIN_DESC desc)
    {
        Microsoft::WRL::ComPtr<IDXGIDevice>     pDXGIDevice = nullptr;
        Microsoft::WRL::ComPtr<IDXGIAdapter>    pAdapter = nullptr;
        Microsoft::WRL::ComPtr<IDXGIFactory>    pFactory = nullptr;

        if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), (void**)pDXGIDevice.GetAddressOf())))
            return false;

        if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)pAdapter.GetAddressOf())))
            return false;

        if (FAILED(pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)pFactory.GetAddressOf())))
            return false;
        
        if (FAILED(pFactory->CreateSwapChain(mDevice.Get(), &desc, mSwapChain.GetAddressOf())))
            return false;

        return true;
    }

    bool GraphicsDevice_DX11::CreateBuffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* initial_data, ID3D11Buffer** buffer)
    {
        if (FAILED(mDevice->CreateBuffer(desc, initial_data, buffer)))
            return false;

        return true;
    }

    bool GraphicsDevice_DX11::CreateTexture(const D3D11_TEXTURE2D_DESC desc)
    {
        // Create Depth Stencil Buffer
        if (FAILED(mDevice->CreateTexture2D(&desc, nullptr, mDepthStencilBuffer.GetAddressOf())))
            return false;

        // Create Depth Stencil Buffer View
        if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilBuffer.Get(), nullptr, mDepthStencilView.GetAddressOf())))
            return false;

        return true;
    }

    bool GraphicsDevice_DX11::CreateTexture(const std::filesystem::path& path, ID3D11Resource** texture,
	    ID3D11ShaderResourceView** srv)
    {
        if (FAILED(CreateWICTextureFromFile(mDevice.Get(), path.c_str(), texture, srv)))
        {
	        return false;
        }

        return true;
    }

    bool GraphicsDevice_DX11::CreateSampler(ID3D11SamplerState** sampler) 
    {
        D3D11_SAMPLER_DESC sampler_desc;

		sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampler_desc.MipLODBias = 0.0f;
		sampler_desc.MaxAnisotropy = 1;
		sampler_desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		sampler_desc.BorderColor[0] = 0;
		sampler_desc.BorderColor[1] = 0;
		sampler_desc.BorderColor[2] = 0;
		sampler_desc.BorderColor[3] = 0;
		sampler_desc.MinLOD = 0;
		sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

        return SUCCEEDED(mDevice->CreateSamplerState(&sampler_desc, sampler));
    }

    //bool GraphicsDevice_DX11::CreateShader(const graphics::eShaderStage stage, const std::wstring& file, const std::string& funcName)
    //{

    //    // Triangle Vertex Shader
    //    std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
    //    shaderPath += "\\Shaders_SOURCE\\";

    //    std::wstring vsPath(shaderPath.c_str());
    //    vsPath += L"TriangleVS.hlsl";
    //    D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
    //        , "VS_Test", "vs_5_0", 0, 0, &renderer::triangleVSBlob, &renderer::errorBlob);

    //    mDevice->CreateVertexShader(renderer::triangleVSBlob->GetBufferPointer()
    //        , renderer::triangleVSBlob->GetBufferSize()
    //        , nullptr
    //        , &renderer::triangleVSShader);

    //    std::wstring psPath(shaderPath.c_str());
    //    psPath += L"TrianglePS.hlsl";
    //    D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
    //        , "PS_Test", "ps_5_0", 0, 0, &renderer::trianglePSBlob, &renderer::errorBlob);

    //    mDevice->CreatePixelShader(renderer::trianglePSBlob->GetBufferPointer()
    //        , renderer::trianglePSBlob->GetBufferSize()
    //        , nullptr
    //        , &renderer::trianglePSShader);


    //    // Input layout 정점 구조 정보
    //    D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

    //    arrLayout[0].AlignedByteOffset = 0;
    //    arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    //    arrLayout[0].InputSlot = 0;
    //    arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    //    arrLayout[0].SemanticName = "POSITION";
    //    arrLayout[0].SemanticIndex = 0;

    //    arrLayout[1].AlignedByteOffset = 12;
    //    arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    //    arrLayout[1].InputSlot = 0;
    //    arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
    //    arrLayout[1].SemanticName = "COLOR";
    //    arrLayout[1].SemanticIndex = 0;

    //    mDevice->CreateInputLayout(arrLayout, 2
    //        , renderer::triangleVSBlob->GetBufferPointer()
    //        , renderer::triangleVSBlob->GetBufferSize()
    //        , &renderer::triangleLayout);

    //    return true;
    //}

    bool GraphicsDevice_DX11::CreateInputLayout(const D3D11_INPUT_ELEMENT_DESC* pInputElementDescs, UINT NumElements
        , const void* pShaderBytecodeWithInputSignature, SIZE_T BytecodeLength, ID3D11InputLayout** ppInputLayout)
    {
        if (FAILED(mDevice->CreateInputLayout(pInputElementDescs, NumElements
            , pShaderBytecodeWithInputSignature
            , BytecodeLength
            , ppInputLayout)))
            return false;

        return true;
    }

    bool GraphicsDevice_DX11::CompileFromFile(const std::wstring& fileName
        , const std::string& funcName
        , const std::string& version
        , ID3DBlob** ppCode)
    {
        std::filesystem::path path = std::filesystem::current_path().parent_path();
        path += "\\Shaders_SOURCE\\";

        std::wstring filePath(path.c_str());
        filePath += fileName;

        UINT flag = D3DCOMPILE_ENABLE_STRICTNESS;
        flag |= D3DCOMPILE_DEBUG;
        flag |= D3DCOMPILE_SKIP_OPTIMIZATION;

        ID3DBlob* errorBlob = nullptr;
        if (FAILED(D3DCompileFromFile(filePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
            , funcName.c_str(), version.c_str()
            , flag, 0, ppCode, &errorBlob)))
            return false;

        return true;
    }

    bool GraphicsDevice_DX11::CreateVertexShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11VertexShader** ppVertexShader)
    {
        if (FAILED(mDevice->CreateVertexShader(pShaderBytecode
            , BytecodeLength
            , nullptr
            , ppVertexShader)))
            return false;

        return true;
    }

    bool GraphicsDevice_DX11::CreatePixelShader(const void* pShaderBytecode, SIZE_T BytecodeLength, ID3D11PixelShader** ppVertexShader)
    {
        if (FAILED(mDevice->CreatePixelShader(pShaderBytecode
            , BytecodeLength
            , nullptr
            , ppVertexShader)))
            return false;

        return true;
    }

    void GraphicsDevice_DX11::BindInputLayout(ID3D11InputLayout* pInputLayout)
    {
        mContext->IASetInputLayout(pInputLayout);
    }

    void GraphicsDevice_DX11::BindPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology)
    {
        mContext->IASetPrimitiveTopology(Topology);
    }

    void GraphicsDevice_DX11::BindVertexBuffer(UINT startSlot, UINT numBuffers, ID3D11Buffer* const* ppVertexBuffers, const UINT stride, const UINT offset)
    {
        mContext->IASetVertexBuffers(startSlot, numBuffers, ppVertexBuffers, &stride, &offset);
    }

    void GraphicsDevice_DX11::BindIndexBuffer(ID3D11Buffer* pIndexBuffer, DXGI_FORMAT format, UINT Offset)
    {
        mContext->IASetIndexBuffer(pIndexBuffer, format, Offset);
    }

    void GraphicsDevice_DX11::BindVertexShader(ID3D11VertexShader* pVertexShader)
    {
        mContext->VSSetShader(pVertexShader, 0, 0);
    }

    void GraphicsDevice_DX11::BindPixelShader(ID3D11PixelShader* pPixelShader)
    {
        mContext->PSSetShader(pPixelShader, 0, 0);
    }

    void GraphicsDevice_DX11::BindShaderResourceView(ID3D11ShaderResourceView* srv, graphics::eRSType type, graphics::eShaderStage stage)
    {
		switch (stage)
		{
			case ya::graphics::eShaderStage::VS:
			{
				mContext->VSSetShaderResources((UINT)type, 1, &srv);
			}
			break;
		case ya::graphics::eShaderStage::HS:
			{
				mContext->HSSetShaderResources((UINT)type, 1, &srv);
			}
			break;
		case ya::graphics::eShaderStage::DS:
			{
				mContext->DSSetShaderResources((UINT)type, 1, &srv);
			}
			break;
		case ya::graphics::eShaderStage::GS:
			{
				mContext->GSSetShaderResources((UINT)type, 1, &srv);
			}
			break;
		case ya::graphics::eShaderStage::PS:
			{
				mContext->PSSetShaderResources((UINT)type, 1, &srv);
			}
			break;
		case ya::graphics::eShaderStage::CS:
			{
				mContext->CSSetShaderResources((UINT)type, 1, &srv);
			}
			break;
		default:
			break;
		}
    }

    void GraphicsDevice_DX11::BindViewports(D3D11_VIEWPORT* viewPort)
    {
        mContext->RSSetViewports(1, viewPort);
    }

    void GraphicsDevice_DX11::BindConstantBuffer(ID3D11Buffer* buffer, void* data, UINT size)
    {
        D3D11_MAPPED_SUBRESOURCE subRes = {};
        mContext->Map(buffer, 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &subRes);
        memcpy(subRes.pData, data, size);
        mContext->Unmap(buffer, 0);
    }

    void GraphicsDevice_DX11::SetConstantBuffer(eShaderStage stage, eCBType type, ID3D11Buffer* buffer)
    {
        switch (stage)
        {
        case ya::graphics::eShaderStage::VS:
            {
                mContext->VSSetConstantBuffers((UINT)type, 1, &buffer);
            }
            break;
        case ya::graphics::eShaderStage::HS:
            {
                mContext->HSSetConstantBuffers((UINT)type, 1, &buffer);
            }
            break;
        case ya::graphics::eShaderStage::DS:
            {
                mContext->DSSetConstantBuffers((UINT)type, 1, &buffer);
            }
            break;
        case ya::graphics::eShaderStage::GS:
            {
                mContext->GSSetConstantBuffers((UINT)type, 1, &buffer);
            }
            break;
        case ya::graphics::eShaderStage::PS:
            {
                mContext->PSSetConstantBuffers((UINT)type, 1, &buffer);
            }
            break;
        case ya::graphics::eShaderStage::CS:
            {
                mContext->CSSetConstantBuffers((UINT)type, 1, &buffer);
            }
            break;
        default:
            break;
        }
    }

    void GraphicsDevice_DX11::Clear()
    {
        FLOAT backgroundColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
        mContext->ClearRenderTargetView(mRenderTargetView.Get(), backgroundColor);
        mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
    }

    void GraphicsDevice_DX11::AdjustViewport()
    {
        // ViewPort, RenderTaget
        RECT winRect;
        GetClientRect(application.GetHwnd(), &winRect);
        D3D11_VIEWPORT mViewPort = { 0.0f, 0.0f, (FLOAT)(winRect.right - winRect.left), (FLOAT)(winRect.bottom - winRect.top), 0.0f, 1.0f };
        BindViewports(&mViewPort);
        mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
    }

    void GraphicsDevice_DX11::Draw(UINT VertexCount, UINT StartVertexLocation)
    {
        mContext->Draw(VertexCount, StartVertexLocation);
    }

    void GraphicsDevice_DX11::DrawIndexed(UINT IndexCount, UINT StartIndexLocation, INT BaseVertexLocation)
    {
        mContext->DrawIndexed(IndexCount, StartIndexLocation, BaseVertexLocation);
    }

    void GraphicsDevice_DX11::Present()
    {
        // 백버퍼에 그려준다
        mSwapChain->Present(0, 0);
    }

    void GraphicsDevice_DX11::BindSampler(ID3D11SamplerState* sampler, eShaderStage stage) const
    {
        switch(stage)
        {
	        case ya::graphics::eShaderStage::VS:
	        	mContext->VSSetSamplers(0, 1, &sampler);
				break;
            case ya::graphics::eShaderStage::HS:
	        	mContext->HSSetSamplers(0, 1, &sampler);
				break;
            case ya::graphics::eShaderStage::DS:
                mContext->DSSetSamplers(0, 1, &sampler);
				break;
            case ya::graphics::eShaderStage::GS:
				mContext->GSSetSamplers(0, 1, &sampler);
				break;
            case ya::graphics::eShaderStage::PS:
                mContext->PSSetSamplers(0, 1, &sampler);
				break;
            case ya::graphics::eShaderStage::CS:
				mContext->CSSetSamplers(0, 1, &sampler);
				break;
            default:
				break;
        }
    }

    bool GraphicsDevice_DX11::CreateBlendState(ID3D11BlendState** blend_state) const
    {
        D3D11_BLEND_DESC blendStateDesc{};
		blendStateDesc.AlphaToCoverageEnable = FALSE;
		blendStateDesc.IndependentBlendEnable = FALSE;        
		blendStateDesc.RenderTarget[0].BlendEnable = TRUE;
		blendStateDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendStateDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendStateDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendStateDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
		blendStateDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_DEST_ALPHA;
		blendStateDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendStateDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		        
		if(FAILED(mDevice->CreateBlendState(&blendStateDesc, blend_state)))
		{
		    return false;
		}

        return true;
    }

    void GraphicsDevice_DX11::BindBlendState(ID3D11BlendState* blend_state)
    {
        mContext->OMSetBlendState(blend_state, nullptr, 0xFFFFFFFF);
    }
}
