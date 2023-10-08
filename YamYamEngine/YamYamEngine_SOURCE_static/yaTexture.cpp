#include "yaTexture.hpp"

#include "yaGraphicsDevice_DX11.h"

namespace ya
{
	Texture::Texture(const std::wstring& name, const std::filesystem::path& path)
	{
		SetKey(name);
		SetPath(path);
		Texture::Load(path);
	}

	HRESULT Texture::Load(const std::filesystem::path& path)
	{
		const auto absPath = std::filesystem::absolute(path);

		if (!graphics::GetDevice()->CreateTexture(absPath, mResource.ReleaseAndGetAddressOf(), mShaderResourceView.ReleaseAndGetAddressOf()))
		{
			return E_FAIL;
		}

		if(const auto hr = mResource.As(&mTexture2D); FAILED(hr))
		{
			return hr;
		}

		mTexture2D->GetDesc(&mDesc);

		return S_OK;
	}

	void Texture::Update() const
	{
		graphics::GetDevice()->BindShaderResourceView(mShaderResourceView.Get(), graphics::eRSType::Texture, graphics::eShaderStage::PS);
	}
}
