#include "yaToolScene.h"
#include "yaRenderer.h"
#include "yaInput.h"
#include "yaTexture.hpp"
#include "yaTransform.h"
#include "yaResources.h"
#include "yaCamera.h"
#include "yaTile.h"
#include "yaCollisionManager.h"
#include "yaCollider.h"


// ToolScene에서 하던 작업을 각 씬에서 불러와주면 됨
// 절대경로 사용

namespace ya
{


	ToolScene::ToolScene()
	{

	}
	ToolScene::~ToolScene()
	{
	}
	void ToolScene::Initialize()
	{
		Scene::Initialize();
	}

	void ToolScene::Update()
	{
		Scene::Update();


		// GetFocus : 윈도우가 활성될 때만 할 수 있게 해주는 함수
		if (Input::GetKeyDown(eKeyCode::LBTN) && GetFocus() /*&& Input::GetKeyDown(eKeyCode::B)*/)
		{
			Vector3 mousePos = Input::GetCoordinationMousePosition();

			// 마우스 커서의 위치를 타일의 인덱스로 바꿔주는 작업
			int idxX = (mousePos.x - LEFT_TOP_X) / (TILE_WIDTH);
			int idxY = (mousePos.y - LEFT_TOP_Y) / (TILE_HEIGHT);

			// 타일의 중앙을 중심으로 오프셋 설정
			Vector3 offset = Vector3((TILE_WIDTH) / 2.0f, (TILE_HEIGHT) / 2.0f, 1);

			offset.x += LEFT_TOP_X;
			offset.y += LEFT_TOP_Y;

			Tile* tile = new Tile();
			tile->GetComponent<Transform>()->SetPosition(Vector3((idxX * (TILE_WIDTH)+offset.x
				), (idxY * (TILE_HEIGHT)+offset.y), 1));

			//tile->GetComponent<Transform>()->SetPosition(Vector3(0,0,1));

			tile->SetCircle(tile);

			tile->SetTile(Tile::mSelectedX, Tile::mSelectedY);
			//tile->SetSourceTileIdx(Tile::mSelectedX, Tile::mSelectedY);
			tile->SetTileIdx(idxX, idxY);

			AddGameObject(tile, LAYER::TILE);

			mTiles.push_back(tile);
		}

		// GetFocus : 윈도우가 활성될 때만 할 수 있게 해주는 함수
		//if (Input::GetKeyDown(eKeyCode::LBTN) && GetFocus() && Input::GetKeyDown(eKeyCode::N))
		//{

		//	Vector2 mousePos = Input::GetMousePosition();

		//	// 마우스 커서의 위치를 타일의 인덱스로 바꿔주는 작업
		//	int idxX = (mousePos.x - LEFT_TOP_X) / (TILE_WIDTH);
		//	int idxY = (mousePos.y - LEFT_TOP_Y) / (TILE_HEIGHT);

		//	// 타일의 중앙을 중심으로 오프셋 설정
		//	Vector3 offset = Vector3((TILE_WIDTH) / 2.0f, (TILE_HEIGHT) / 2.0f, 1);

		//	offset.x += LEFT_TOP_X;
		//	offset.y += LEFT_TOP_Y;

		//	Tile* tile = new Tile();
		//	tile->GetComponent<Transform>()->SetPosition(Vector3(idxX * (TILE_WIDTH)+offset.x
		//		, idxY * (TILE_HEIGHT)+offset.y, 1));

		//	tile->SetTile(Tile::mSelectedX, Tile::mSelectedY);
		//	//tile->SetSourceTileIdx(Tile::mSelectedX, Tile::mSelectedY);
		//	tile->SetTileIdx(idxX, idxY);

		//	mTiles.push_back(tile);
		//}

		//// GetFocus : 윈도우가 활성될 때만 할 수 있게 해주는 함수
		//if (Input::GetKeyDown(eKeyCode::LBTN) && GetFocus() && Input::GetKeyDown(eKeyCode::M))
		//{

		//	Vector2 mousePos = Input::GetMousePosition();

		//	// 마우스 커서의 위치를 타일의 인덱스로 바꿔주는 작업
		//	int idxX = (mousePos.x - LEFT_TOP_X) / (TILE_WIDTH);
		//	int idxY = (mousePos.y - LEFT_TOP_Y) / (TILE_HEIGHT);

		//	// 타일의 중앙을 중심으로 오프셋 설정
		//	Vector3 offset = Vector3((TILE_WIDTH) / 2.0f, (TILE_HEIGHT) / 2.0f, 1);

		//	offset.x += LEFT_TOP_X;
		//	offset.y += LEFT_TOP_Y;

		//	Tile* tile = new Tile();
		//	tile->GetComponent<Transform>()->SetPosition(Vector3(idxX * (TILE_WIDTH)+offset.x
		//		, idxY * (TILE_HEIGHT)+offset.y, 1));


		//	tile->SetTile(Tile::mSelectedX, Tile::mSelectedY);
		//	//tile->SetSourceTileIdx(Tile::mSelectedX, Tile::mSelectedY);
		//	tile->SetTileIdx(idxX, idxY);

		//	mTiles.push_back(tile);
		//}

		// 타일을 깔고 어딘가에 저장을 해야 함 
		// 파일 입출력(램에 있는 데이터를 SSD에 옮기는 작업)
		if (Input::GetKeyDown(eKeyCode::S))
		{
			Save();
		}
		if (Input::GetKeyDown(eKeyCode::L))
		{
			Load();
		}

	}
	void ToolScene::Render()
	{
		Scene::Render();
	}
	// 파일 입출력
	void ToolScene::Save()
	{
		// open a file name
		OPENFILENAME ofn = {};

		//szFilePath - 경로
		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;

		// 파일을 여는 함수
		// wb : 파일을 이진수로 저장할 것인지
		// wt : 텍스트로 저장할 것인지
		_wfopen_s(&pFile, szFilePath, L"wb");
		if (pFile == nullptr)
			return;

		for (Tile* tile : mTiles)
		{
			Vector3 sourIdx = tile->GetSourceTileIdx();
			Vector3 idx = tile->GetTileIdx();

			int sourceX = sourIdx.x;
			int sourceY = sourIdx.y;

			int	myX = idx.x;
			int myY = idx.y;

			// 열어놓은 파일에 원하는 크기만큼 파일에 기록
			// sourceX, sourceY - 우측의 타일의 소스 인덱스
			// myX, myY - 좌측의 타일 인덱스
			fwrite(&sourceX, sizeof(int), 1, pFile);
			fwrite(&sourceY, sizeof(int), 1, pFile);
			fwrite(&myX, sizeof(int), 1, pFile);
			fwrite(&myY, sizeof(int), 1, pFile);
		}

		// 메모리 할당된 것을 삭제해주는 함수
		fclose(pFile);
	}

	void ToolScene::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"All\0*.*\0Text\0*.TXT\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetOpenFileName(&ofn))
			return;

		// rb : 이진수로 파일을 읽음
		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"rb");

		if (pFile == nullptr)
			return;

		while (true)
		{
			int sourceX = -1;
			int sourceY = -1;

			int	myX = -1;
			int myY = -1;

			if (fread(&sourceX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&sourceY, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&myX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&myY, sizeof(int), 1, pFile) == NULL)
				break;

			Vector3 offset = Vector3((TILE_WIDTH) / 2.0f, (TILE_HEIGHT) / 2.0f, 1);
			Tile* tile = new Tile();

			tile->GetComponent<Transform>()->SetPosition(myX * (TILE_WIDTH)+offset.x + LEFT_TOP_X
				, myY * (TILE_HEIGHT)+offset.y + LEFT_TOP_Y, 1);

			tile->SetTile(sourceX, sourceY);
			tile->SetSourceTileIdx(sourceX, sourceY);
			tile->SetTileIdx(myX, myY);

			AddGameObject(tile, LAYER::TILE);

			mTiles.push_back(tile);
		}

		// 메모리 할당된 것을 삭제해주는 함수
		fclose(pFile);
	}
	void ToolScene::Enter()
	{
	}
	void ToolScene::Exit()
	{
	}
}
