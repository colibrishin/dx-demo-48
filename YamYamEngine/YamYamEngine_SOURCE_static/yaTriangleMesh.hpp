#pragma once
#include "yaMesh.h"

namespace ya
{
	class TriangleMesh : public Mesh
	{
	public:
		TriangleMesh();
		~TriangleMesh() override = default;

	protected:
		renderer::Vertex* SetVertexData() override;
		UINT* SetIndexData() override;
		UINT SetVertexCount() override;
		UINT SetIndexCount() override;

	private:
		std::vector<renderer::Vertex> mVertices;
		std::vector<UINT> mIndices;
	};

	inline TriangleMesh::TriangleMesh()
	{
		mVertices.resize(3);

		mVertices[0].pos = Vector3(0.f, sqrt(3) / 3, 0.f);
		mVertices[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		mVertices[0].uv = Vector2(0.5f, 0.f);

		mVertices[1].pos = Vector3(0.5f, -sqrt(3) / 6, 0.f);
		mVertices[1].color = Vector4(1.f, 0.f, 0.f, 1.f);
		mVertices[1].uv = Vector2(1.f, 1.f);

		mVertices[2].pos = Vector3(-0.5f, -(sqrt(3) / 6), 0.f);
		mVertices[2].color = Vector4(0.f, 0.f, 1.f, 1.f);
		mVertices[2].uv = Vector2(0.f, 1.f);

		mIndices = {0, 1, 2};

		TriangleMesh::Load({});
	}

	inline renderer::Vertex* TriangleMesh::SetVertexData()
	{
		return mVertices.data();
	}

	inline UINT* TriangleMesh::SetIndexData()
	{
		return mIndices.data();
	}

	inline UINT TriangleMesh::SetVertexCount()
	{
		return mVertices.size();
	}

	inline UINT TriangleMesh::SetIndexCount()
	{
		return mIndices.size();
	}
}
