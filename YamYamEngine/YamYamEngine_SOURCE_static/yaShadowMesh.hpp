#pragma once
#include "yaMesh.h"
#include <vector>
#include "yaRenderer.h"

namespace ya
{
	class ShadowMesh : public Mesh
	{
	public:
		ShadowMesh();
		~ShadowMesh() override = default;

		void ChangeTopPosition(Vector3 normal) { mVertices[0].pos = normal; }
		void ChangeLeftPosition(Vector3 normal) { mVertices[2].pos = normal; }
		void ChangeRightPosition(Vector3 normal) { mVertices[1].pos = normal; }

	protected:
		renderer::Vertex* SetVertexData() override;
		UINT* SetIndexData() override;
		UINT SetVertexCount() override;
		UINT SetIndexCount() override;

	private:
		std::vector<renderer::Vertex> mVertices;
		std::vector<UINT> mIndices;
	};

	inline ShadowMesh::ShadowMesh()
	{
		mVertices.resize(3);

		mVertices[0].pos = Vector3(0.f, sqrt(3) / 3, 0.f);
		mVertices[0].color = Vector4(0.f, 0.f, 0.f, 0.f);
		mVertices[0].uv = Vector2(0.5f, 0.f);

		mVertices[1].pos = Vector3(0.5f, -sqrt(3) / 6, 0.f);
		mVertices[1].color = Vector4(0.f, 0.f, 0.f, 0.6f);
		mVertices[1].uv = Vector2(1.f, 1.f);

		mVertices[2].pos = Vector3(-0.5f, -(sqrt(3) / 6), 0.f);
		mVertices[2].color = Vector4(0.f, 0.f, 0.f, 0.6f);
		mVertices[2].uv = Vector2(0.f, 1.f);

		mIndices = {0, 1, 2};

		ShadowMesh::Load({});
	}

	inline renderer::Vertex* ShadowMesh::SetVertexData()
	{
		return mVertices.data();
	}

	inline UINT* ShadowMesh::SetIndexData()
	{
		return mIndices.data();
	}

	inline UINT ShadowMesh::SetVertexCount()
	{
		return mVertices.size();
	}

	inline UINT ShadowMesh::SetIndexCount()
	{
		return mIndices.size();
	}
}
