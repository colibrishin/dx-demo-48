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
#include "IJ_Button.h"
#include "IJ_BCO_Light.h"
#include "yaTile.h"

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

		//Player
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

			player->Initialize();
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
			turrettr->SetPosition(Vector3(2.5f, 0.f, 1.0f));
			turrettr->SetScale(Vector3(0.5f, 0.5f, 1.0f));

			MeshRenderer* turretmr = turret->AddComponent<MeshRenderer>();
			turretmr->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
			turretmr->SetShader(Resources::Find<Shader>(L"ColorShader"));
			turret->AddComponent<TurretScript>();
			AddGameObject(turret, LAYER::TURRET);
			turret->AddComponent<Collider>()->SetSize(Vector3(0.1f, 0.1f, 1.0f));
		}

		// Light
		//{
		//	Light* light = new Light(5.0f);
		//	light->Initialize();
		//	light->GetComponent<Transform>()->SetPosition(Vector3(0.1f, 0.1f, 1.0f));
		//	AddGameObject(light, LAYER::LIGHT);

		//	for(const auto& lights : light->GetLightings())
		//	{
		//		AddGameObject(lights, LAYER::LIGHT);
		//	}
		//}

		// Button
		{
			IJ::GO_Button* button = new IJ::GO_Button();
			button->Initialize();
			button->SetButtonType(IJ::GO_Button::eButtonType::Toggle);
			button->GetComponent<Transform>()->SetPosition(Vector3(-3.0f, -3.0f, 1.0f));

			IJ::BCO_Light* bco_light = new IJ::BCO_Light(3.0f);
			bco_light->Initialize();
			bco_light->GetComponent<Transform>()->SetPosition(Vector3(0.1f, 0.1f, 1.0f));
			AddGameObject(bco_light, LAYER::LIGHT);

			for (const auto& lights : bco_light->GetLightings())
			{
				AddGameObject(lights, LAYER::LIGHT);
			}

			button->ConnectGameObject(bco_light);
			AddGameObject(button, LAYER::ITEM);
		}

		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::PLAYER, true);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::PORTAL, true);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::LIGHT, true);
		CollisionManager::CollisionLayerCheck(LAYER::PLAYER, LAYER::ITEM, true);
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

	//void PlayScene::Load()
	//{
	//	OPENFILENAME ofn = {};

	//	// 맵 저장한 파일 경로
	//	wchar_t szFilePath[256] = L"..\\Resources\\Tile\\F.tm";

	//	// rb : 이진수로 파일을 읽음
	//	FILE* pFile = nullptr;
	//	_wfopen_s(&pFile, szFilePath, L"rb");

	//	if (pFile == nullptr)
	//		return;

	//	while (true)
	//	{
	//		int sourceX = -1;
	//		int sourceY = -1;

	//		int	myX = -1;
	//		int myY = -1;

	//		if (fread(&sourceX, sizeof(int), 1, pFile) == NULL)
	//			break;
	//		if (fread(&sourceY, sizeof(int), 1, pFile) == NULL)
	//			break;
	//		if (fread(&myX, sizeof(int), 1, pFile) == NULL)
	//			break;
	//		if (fread(&myY, sizeof(int), 1, pFile) == NULL)
	//			break;

	//		Vector2 offset = Vector2((TILE_WIDTH) / 2.0f, (TILE_HEIGHT) / 2.0f);


	//		Tile* tile = new Tile();
	//		Vector3 pos = tile->GetComponent<Transform>()->SetPosition(Vector3(myX * (TILE_WIDTH)+offset.x + LEFT_TOP_X
	//			, myY * (TILE_HEIGHT)+offset.y + LEFT_TOP_Y), 1.f);

	//		tile->SetTile(sourceX, sourceY);
	//		// Crack(부서지며 충돌체가 있는 타일)
	//		if ((sourceX == 0 && sourceY == 0) ||
	//			(sourceX == 1 && sourceY == 0) ||
	//			(sourceX == 2 && sourceY == 0))
	//		{
	//			tile->SetType(Tile::eTileType::);
	//		}
	//		// Uncrushable(부서지지는 않지만 충돌체는 있는 타입)
	//		if ((sourceX == 0 && sourceY == 3) ||
	//			(sourceX == 1 && sourceY == 3))
	//		{
	//			tile->SetType(Tile::eTileType::Uncrushable);
	//		}
	//		// None(충돌체가 없는 바닥같은 타일)
	//		if ((sourceX == 0 && sourceY == 1))
	//		{
	//			tile->SetType(Tile::eTileType::None);
	//		}

	//		if (tile->GetType() == Tile::eTileType::Crack || tile->GetType() == Tile::eTileType::Uncrushable)
	//		{
	//			Collider* Col = tile->AddComponent<Collider>();;
	//			Col->SetSize(Vector2(40.0f, 40.0f));

	//			CollisionManager::CollisionLayerCheck(LAYER::TILE, LAYER::PLAYER, true);

	//		}

	//		tile->SetSourceTileIdx(sourceX, sourceY);
	//		tile->SetTileIdx(myX, myY);

	//		mTiles.push_back(tile);
	//	}
	//	fclose(pFile);
	//}
}
