#pragma once
#include "yaResource.h"
#include "yaGraphics.h"

namespace ya
{
	using namespace math;
	namespace renderer
	{
		struct Vertex;
	}

	class Mesh : public Resource
	{
	public:
		void Initialize();
		Mesh();
		~Mesh() override;

		virtual HRESULT Load(const std::filesystem::path& path) override;

		bool CreateVertexBuffer(void* data, UINT Count);
		bool CreateIndexBuffer(void* data, UINT Count);
		void BindBuffer();
		void Render();

		void SetColor(const Vector4& color) { mColor = color; }
		Vector4 GetColor() const { return mColor; }

	protected:
		virtual renderer::Vertex* SetVertexData() = 0;
		virtual UINT* SetIndexData() = 0;

		virtual UINT SetVertexCount() = 0;
		virtual UINT SetIndexCount() = 0;

		Vector4 mColor;
		bool mBTex;

	private:
		renderer::Vertex* mBufferVertices;

		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
		D3D11_BUFFER_DESC mVBDesc;

		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;
		D3D11_BUFFER_DESC mIBDesc;
		UINT mIndexCount;
	};
}
