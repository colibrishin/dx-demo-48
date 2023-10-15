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

		//PlayScene::Load();

		//Player
		{
			mPlayer = new Player();
			mPlayer->Initialize();

			MeshRenderer* meshRenderer = mPlayer->AddComponent<MeshRenderer>();
			meshRenderer->SetMesh(Resources::Find<Mesh>(L"TriangleMesh"));
			meshRenderer->SetShader(Resources::Find<Shader>(L"ColorShader"));

			Transform* tr = mPlayer->GetComponent<Transform>();
			auto cld1 = mPlayer->GetComponent<Collider>();
			auto rb = mPlayer->GetComponent<Rigidbody>();
			mPlayer->AddComponent<PlayerScript>();

			tr->SetPosition(Vector3(-2.5f, 0.2f, 1.0f));
			tr->SetScale(Vector3(1.0f, 1.0f, 1.0f));

			cld1->SetSize(Vector3(1.0f, 1.0f, 1.0f));

			// ** 테스트용으로 플레이어의 중력을 없애놨음. 나중에 풀어야 함!! **
			rb->SetGravity(Vector3::Zero);

			rb->SetFriction(0.25f);

			AddGameObject(mPlayer, LAYER::PLAYER);
			AddGameObject(mPlayer->GetPlayerShadow(), LAYER::PLAYER);
			AddGameObject(mPlayer->GetMeleeHitBox(), LAYER::ATTACK);
			AddGameObject(mPlayer->GetPlayerShadow()->GetMeleeHitBox(), LAYER::ATTACK);
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
			turret->SetPlayer(mPlayer);
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

			Light* bco_light = new Light(3.0f);
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

		Camera::SetZoom(10.f);
	}

	void PlayScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::U))
		{
			PlayScene::Load();
		}
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}

	void PlayScene::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = L"..\\Resources\\Map\\Stage_R.tm";

		// rb : 이진수로 파일을 읽음
		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"rb");

		if (pFile == nullptr)
			return;

		while (true)
		{
			int	myX = -1;
			int myY = -1;

			Tile::eTileType myType = Tile::eTileType::End;

			//Vector3 myPos = Vector3::Zero;

			if (fread(&myX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&myY, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&myType, sizeof(Tile::eTileType), 1, pFile) == NULL)
				break;
			//if (fread(&myPos, sizeof(Vector3), 1, pFile) == NULL)
				//break;


			Vector3 offset = Vector3::Zero;

			Tile* tile = new Tile();

			tile->GetComponent<Transform>()->SetPosition(myX * (TILE_WIDTH)+offset.x + LEFT_TOP_X
				, myY * (TILE_HEIGHT)+offset.y + LEFT_TOP_Y, 1);

			//tile->GetComponent<Transform>()->SetPosition(myPos);

			tile->SetTileIdx(myX, myY);
			// 불러온 myType을 tile 객체에 텋는다
			tile->SetType(myType);

			if (tile->GetType() == Tile::eTileType::Circle)
			{
				tile->SetCircle(tile);

			}
			else if (tile->GetType() == Tile::eTileType::Triangle)
			{
				tile->SetTriangle(tile);
			}
			else if (tile->GetType() == Tile::eTileType::Square)
			{
				tile->SetSquare(tile);
			}
			else if (tile->GetType() == Tile::eTileType::Floor)
			{
				tile->SetFloor(tile);
			}

			AddGameObject(tile, LAYER::TILE);

			mTiles.push_back(tile);
		}

		// 메모리 할당된 것을 삭제해주는 함수
		fclose(pFile);
	}
}
