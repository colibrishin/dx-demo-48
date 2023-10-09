#include "yaPlayScene.h"
#include "yaResources.h"
#include "yaCollider.h"
#include "yaGameObject.h"
#include "yaTransform.h"
#include "yaMeshRenderer.h"
#include "yaPlayerScript.h"
#include "yaPlayer.h"
#include "yaInput.h"
#include "yaRigidbody.h"
#include "yaCollisionManager.h"
#include "yaLight.h"
#include "yaPortal.hpp"
#include "yaTurret.h"
#include "yaTurretScript.h"

namespace ya
{
	PlayScene::PlayScene()
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		Scene::Initialize();

		{
			Player* player = new Player();
			player->Initialize();

			MeshRenderer* meshRenderer = player->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
			meshRenderer->SetShader(Resources::Find<Shader>(L"ColorShader"));

			Transform* tr = player->GetComponent<Transform>();
			auto cld1 = player->GetComponent<Collider>();
			auto rb = player->GetComponent<Rigidbody>();
			player->AddComponent<PlayerScript>();

			tr->SetPosition(Vector3(-2.5f, 0.2f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			cld1->SetSize(Vector3(1.0f, 1.0f, 1.0f));

			// ** 테스트용으로 플레이어의 중력을 없애놨음. 나중에 풀어야 함!! **
			rb->SetGravity(Vector3::Zero);

			rb->SetFriction(0.25f);

			AddGameObject(player, LAYER::PLAYER);
		}

		GameObject* wall_a = new GameObject();
		GameObject* wall_b = new GameObject();

		// ù��° ��
		{
			Transform* tr = wall_a->AddComponent<Transform>();
			auto cld1 = wall_a->AddComponent<Collider>();
			tr->SetPosition({1.0f, 0.0f, 1.0f});
			tr->SetScale(Vector3::One);

			cld1->SetSize(Vector3::One);
		}

		// �ι�° ��
		{
			Transform* tr = wall_b->AddComponent<Transform>();
			auto cld1 = wall_b->AddComponent<Collider>();
			tr->SetPosition(Vector3(-1.0f, 0.0f, 1.0f));
			tr->SetScale(Vector3::One);

			cld1->SetSize(Vector3::One);
		}

		Portal* portal_a = new Portal(wall_a);
		Portal* portal_b = new Portal(wall_b);

		// ù��° ��Ż
		{
			MeshRenderer* meshRenderer = portal_a->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(Resources::Find<Mesh>(L"SquareMesh"));
			meshRenderer->SetShader(Resources::Find<Shader>(L"TextureShader"));
			meshRenderer->SetTexture(Resources::Find<Texture>(L"Texture"));

			Transform* tr = portal_a->GetComponent<Transform>();
			auto cld1 = portal_a->GetComponent<Collider>();
			tr->SetPosition({1.1f, 0.0f, 1.0f});
			tr->SetScale(Vector3::One);

			cld1->SetSize(Vector3::One);

			portal_a->SetOtherPortal(portal_b);
			AddGameObject(portal_a, LAYER::PORTAL);
		}

		// �ι�° ��Ż
		{
			MeshRenderer* meshRenderer = portal_b->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(Resources::Find<Mesh>(L"SquareMesh"));
			meshRenderer->SetShader(Resources::Find<Shader>(L"ColorShader"));

			Transform* tr = portal_b->GetComponent<Transform>();
			auto cld1 = portal_b->GetComponent<Collider>();
			tr->SetPosition({-1.1f, 0.0f, 1.0f});
			tr->SetScale(Vector3::One);
		

			cld1->SetSize(Vector3::One);

			portal_b->SetOtherPortal(portal_a);
			AddGameObject(portal_b, LAYER::PORTAL);
		}

		//Turret
		{
			Turret* turret = new Turret();

			Transform* turrettr = turret->AddComponent<Transform>();
			turrettr->SetPosition(Vector3(2.5f, 0.2f, 1.0f));
			turrettr->SetScale(Vector3(0.5f, 0.5f, 0.5f));

			MeshRenderer* turretmr = turret->AddComponent<MeshRenderer>();
			turretmr->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
			turretmr->SetShader(Resources::Find<Shader>(L"ColorShader"));
			turret->AddComponent<TurretScript>();
			AddGameObject(turret, LAYER::TURRET);
			turret->AddComponent<Collider>()->SetSize(Vector3(0.1f, 0.1f, 1.0f));
		}

		// Light
		{
			Light* light = new Light(2.5f);
			light->Initialize();
			light->GetComponent<Transform>()->SetPosition(Vector3(0.1f, 0.1f, 1.0f));
			AddGameObject(light, LAYER::LIGHT);
		}

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::PLAYER, true);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::PORTAL, true);
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}
