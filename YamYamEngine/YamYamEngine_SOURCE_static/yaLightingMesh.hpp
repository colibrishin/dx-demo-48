#pragma once
#include "yaMesh.h"
#include "yaRenderer.h"
#include <vector>

namespace ya
{
	class LightingMesh : public Mesh
	{
	public:
		LightingMesh();
		~LightingMesh() override = default;

	protected:
		renderer::Vertex* SetVertexData() override;
		UINT* SetIndexData() override;
		UINT SetVertexCount() override;
		UINT SetIndexCount() override;

	private:
		std::vector<renderer::Vertex> mVertices;
		std::vector<UINT> mIndices;
	};

	inline LightingMesh::LightingMesh()
	{
		mVertices.resize(3);

		mVertices[0].pos = Vector3(0.f, 0.5f, 0.f);
		mVertices[0].color = Vector4(1.f, 1.f, 1.f, 0.7f);
		mVertices[0].uv = Vector2(0.5f, 0.f);

		mVertices[1].pos = Vector3(0.5f, -0.5f, 0.f);
		mVertices[1].color = Vector4(1.f, 1.f, 1.f, 0.f);
		mVertices[1].uv = Vector2(1.f, 1.f);

		mVertices[2].pos = Vector3(-0.5f, -0.5f, 0.f);
		mVertices[2].color = Vector4(1.f, 1.f, 1.f, 0.f);
		mVertices[2].uv = Vector2(0.f, 1.f);

		mIndices = {0, 1, 2};

		LightingMesh::Load({});
	}

	inline renderer::Vertex* LightingMesh::SetVertexData()
	{
		return mVertices.data();
	}

	inline UINT* LightingMesh::SetIndexData()
	{
		return mIndices.data();
	}

	inline UINT LightingMesh::SetVertexCount()
	{
		return mVertices.size();
	}

	inline UINT LightingMesh::SetIndexCount()
	{
		return mIndices.size();
	}
}
