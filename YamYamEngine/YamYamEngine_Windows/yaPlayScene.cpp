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

		//Player1
		Player* player = new Player();

		Transform* tr = player->AddComponent<Transform>();
		tr->SetPosition(Vector3(-2.5f, 0.2f, 1.0f));
		tr->SetScale(Vector3(0.5f, 0.5f, 0.5f));

		MeshRenderer* meshRenderer = player->AddComponent<MeshRenderer>();
		meshRenderer->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		meshRenderer->SetShader(Resources::Find<Shader>(L"TriangleShader"));

		AddGameObject(player, LAYER::PLAYER);
		player->AddComponent<PlayerScript>();
		player->AddComponent<Collider>()->SetSize(Vector3(0.1f, 0.1f, 1.0f));

		//Player2
		//Player* player2 = new Player();

		//Transform* tr2 = player2->AddComponent<Transform>();
		//tr2->SetPosition(Vector3(0.1f, 0.2f, 1.0f));
		//tr2->SetScale(Vector3(0.1f, 0.1f, 1.0f));

		//MeshRenderer* meshRenderer2 = player2->AddComponent<MeshRenderer>();
		//meshRenderer2->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		//meshRenderer2->SetShader(Resources::Find<Shader>(L"TriangleShader"));

		//AddGameObject(player2, LAYER::PLAYER);
		//player2->AddComponent<Collider>()->SetSize(Vector3(0.1f, 0.1f, 1.0f));

		//CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::PLAYER, true);

		//Turret
		Turret* turret = new Turret();

		Transform* turrettr = turret->AddComponent<Transform>();
		turrettr->SetPosition(Vector3(2.5f, 0.2f, 1.0f));
		turrettr->SetScale(Vector3(0.5f, 0.5f, 0.5f));

		MeshRenderer* turretmr = turret->AddComponent<MeshRenderer>();
		turretmr->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
		turretmr->SetShader(Resources::Find<Shader>(L"TriangleShader"));
		turret->AddComponent<TurretScript>();

		AddGameObject(turret, LAYER::TURRET);
		turret->AddComponent<Collider>()->SetSize(Vector3(0.1f, 0.1f, 1.0f));
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
