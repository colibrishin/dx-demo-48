#pragma once
#include "yaComponent.h"
#include "yaMesh.h"
#include "yaShader.h"
#include "yaTexture.hpp"


namespace ya
{
	using namespace graphics;

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer() override;
		
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetMesh(Mesh* mesh) { mMesh = mesh; }
		void SetShader(Shader* shader) { mShader = shader; }
		void SetTexture(Texture* texture) { mTexture = texture; }
		void SetColor(const Vector4& color) { mColor = color; }

	private:
		Mesh* mMesh;
		Shader* mShader;
		Texture* mTexture;
		Vector4 mColor;
	};
}
