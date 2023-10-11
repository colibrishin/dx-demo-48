#pragma once
#include "yaMesh.h"

namespace ya
{
	constexpr int CIRCLE_MESH_TRIANGLES = 16;

	class CircleMesh : public Mesh
	{
	public:
		CircleMesh();
		~CircleMesh() override = default;

	protected:
		renderer::Vertex* SetVertexData() override;
		UINT* SetIndexData() override;
		UINT SetVertexCount() override;
		UINT SetIndexCount() override;

	private:
		void GenerateIndices();
		void GenerateVertices();

		std::vector<renderer::Vertex> mVertices;
		std::vector<UINT> mIndices;
	};

	inline void CircleMesh::GenerateIndices()
	{
		int index = 0;
		int first = 1;
		int last = 2;

		mIndices.resize(CIRCLE_MESH_TRIANGLES * 3);

		for(int i = 0; i < CIRCLE_MESH_TRIANGLES; ++i)
		{
			mIndices[index] = 0;
			mIndices[index + 1] = first;
			mIndices[index + 2] = last;
			first = last;
			last += 1;

			// TODO: better recurrence relation
			std::swap(mIndices[index + 1], mIndices[index + 2]);

			index += 3;
		}

		mIndices[0] = 0;
		mIndices[((CIRCLE_MESH_TRIANGLES) * 3) - 2] = 1;
	}

	inline void CircleMesh::GenerateVertices()
	{
		mVertices.resize(CIRCLE_MESH_TRIANGLES + 1);

		mVertices[0] = {{0, 0, 0,}, {1, 1, 1, 1}};

		constexpr float deltaTheta = DirectX::XM_2PI / CIRCLE_MESH_TRIANGLES;

		for (int i = 1; i <= CIRCLE_MESH_TRIANGLES; i++) 
		{
			mVertices[i] = renderer::Vertex{{cosf(deltaTheta * i) / 2, sinf(deltaTheta * i) / 2, 0}, {1.0f, 1.0f, 0.0f, 1.0f}};
		}
	}

	inline CircleMesh::CircleMesh()
	{
		GenerateVertices();
		GenerateIndices();

		CircleMesh::Load({});
	}

	inline renderer::Vertex* CircleMesh::SetVertexData()
	{
		return mVertices.data();
	}

	inline UINT* CircleMesh::SetIndexData()
	{
		return mIndices.data();
	}

	inline UINT CircleMesh::SetVertexCount()
	{
		return mVertices.size();
	}

	inline UINT CircleMesh::SetIndexCount()
	{
		return mIndices.size();
	}
}
