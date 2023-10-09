#pragma once
#include "yaResource.h"
#include <wrl/client.h>

#include "yaShader.h"

namespace ya
{
	using namespace Microsoft::WRL;
	using namespace DirectX;

	class Texture : public Resource
	{
	public:
		Texture(const std::wstring& name, const std::filesystem::path& path);
		Texture(const Texture& other) = delete;
		~Texture() override = default;

		UINT GetWidth() const { return mDesc.Width; }
		UINT GetHeight() const { return mDesc.Height; }

		HRESULT Load(const std::filesystem::path& path) override;
		void Update() const;

	private:
		ComPtr<ID3D11ShaderResourceView> mShaderResourceView;
		ComPtr<ID3D11Resource> mResource;
		ComPtr<ID3D11Texture2D> mTexture2D;
		D3D11_TEXTURE2D_DESC mDesc;
	};
}
