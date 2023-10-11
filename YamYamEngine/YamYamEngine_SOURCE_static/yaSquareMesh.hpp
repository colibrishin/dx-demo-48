#pragma once
#include "yaMesh.h"

namespace ya
{
	class SquareMesh : public Mesh
	{
	public:
		SquareMesh();
		~SquareMesh() override = default;

	protected:
		renderer::Vertex* SetVertexData() override;
		UINT* SetIndexData() override;
		UINT SetVertexCount() override;
		UINT SetIndexCount() override;

	private:
		std::vector<renderer::Vertex> mVertices;
		std::vector<UINT> mIndices;
	};

	inline SquareMesh::SquareMesh()
	{
		mVertices.resize(4);

		mVertices[0].pos = Vector3(-0.5f, 0.5f, 0.f);
		mVertices[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		mVertices[0].uv = Vector2(0.f, 0.f);

		mVertices[1].pos = Vector3(0.5f, 0.5f, 0.f);
		mVertices[1].color = Vector4(1.f, 0.f, 0.f, 1.f);
		mVertices[1].uv = Vector2(1.f, 0.f);

		mVertices[2].pos = Vector3(-0.5f, -0.5f, 0.f);
		mVertices[2].color = Vector4(0.f, 0.f, 1.f, 1.f);
		mVertices[2].uv = Vector2(0.f, 1.f);

		mVertices[3].pos = Vector3(0.5f, -0.5f, 0.f);
		mVertices[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		mVertices[3].uv = Vector2(1.f, 1.f);

		mIndices = {0, 1, 2, 1, 3, 2};

		SquareMesh::Load({});
	}

	inline renderer::Vertex* SquareMesh::SetVertexData()
	{
		return mVertices.data();
	}

	inline UINT* SquareMesh::SetIndexData()
	{
		return mIndices.data();
	}

	inline UINT SquareMesh::SetVertexCount()
	{
		return mVertices.size();
	}

	inline UINT SquareMesh::SetIndexCount()
	{
		return mIndices.size();
	}
}
