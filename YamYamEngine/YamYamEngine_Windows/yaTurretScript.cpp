#include "yaTurretScript.h"
#include "yaTransform.h"
#include "yaBullet.h"
#include "yaBulletScript.h"
#include "yaTime.h"
#include "yaMeshRenderer.h"
#include "yaResources.h"
#include "yaGameObject.h"
#include "yaSceneManager.h"

namespace ya
{
	float TurretScript::mTime = 0.0f;

	TurretScript::TurretScript()
	{
	}
	TurretScript::~TurretScript()
	{
	}
	void TurretScript::Initialize()
	{
	}
	void TurretScript::Update()
	{
		GameObject* obj = GetOwner();
		Transform* tr = obj->GetComponent<Transform>();
		Vector3 turretPos = tr->GetPosition();
		Vector3 turretScale = tr->GetScale();

		mTime += Time::DeltaTime();

		if (mTime >= 0.5f)
		{
			Bullet* bullet = new Bullet();

			Transform* bullettr = bullet->AddComponent<Transform>();
			bullettr->SetPosition(tr->GetPosition());
			bullettr->SetScale(tr->GetScale());
			bullet->AddComponent<BulletScript>();

			MeshRenderer* bulletmr = bullet->AddComponent<MeshRenderer>();
			bulletmr->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
			bulletmr->SetShader(Resources::Find<Shader>(L"ColorShader"));

			SceneManager::GetActiveScene()->AddGameObject(bullet, LAYER::TURRET);

			mTime = 0.0f;
		}

		tr->SetPosition(turretPos);
		tr->SetScale(turretScale);
	}
	void TurretScript::LateUpdate()
	{
	}
	void TurretScript::Render()
	{
	}
}