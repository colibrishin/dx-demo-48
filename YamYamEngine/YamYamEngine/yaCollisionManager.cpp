#include "yaCollisionManager.h"
#include "yaScene.h"			// 해당 씬 안에 있는 레이어들을 가져와야 함
#include "yaSceneManager.h"
#include <DirectXCollision.h>
#include <SimpleMath.h>

namespace ya
{
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};
	std::bitset<LAYER_MAX> CollisionManager::mLayerMasks[LAYER_MAX] = {};

	void CollisionManager::Initialize()
	{
		// 레이어간 충돌을 표시하는데 사용할 배열 초기화
		for (size_t row = 0; row < LAYER_MAX; row++)
		{
			for (size_t col = 0; col < LAYER_MAX; col++)
			{
				mLayerMasks[row][col] = false;
				if (row == col)
				{
					mLayerMasks[row][col] = true;
				}
			}
		}

	}

	void CollisionManager::Update()
	{
		Scene* activeScene = SceneManager::GetActiveScene();		// 씬을 가져옴
		for (size_t row = 0; row < LAYER_MAX; row++)
		{
			for (size_t col = 0; col < LAYER_MAX; col++)
			{
				if (mLayerMasks[row][col] == true)					// 충돌되었을 때	
				{
					LayerCollision(activeScene, (LAYER)row, (LAYER)col);
				}
			}
		}
	}

	void CollisionManager::Render(HDC hdc)
	{
	}

	void CollisionManager::Release()
	{
	}

	void CollisionManager::Clear()
	{
		// 씬이 넘어갔을 때 기존 충돌 정보 초기화
		// mLayerMasks->reset() for문 돌려야함
		mLayerMasks->reset();
		mCollisionMap.clear();
	}

	void CollisionManager::CollisionLayerCheck(LAYER left, LAYER right, bool enable)
	{
		// 배열을 사용하여 레이어간 충돌을 표시하는데 
		// 2차원 배열의 반만 사용하기 위한 코드

		int row = -1;
		int col = -1;

		if (left > right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			col = (UINT)left;
			row = (UINT)right;
		}
		mLayerMasks[row][col] = enable;
	}

	// 충돌 체크하는 함수
	void CollisionManager::LayerCollision(Scene* scene, LAYER left, LAYER right)
	{
		// finds left layer objects
		Layer& leftLayer = scene->GetLayer(left);
		std::vector<GameObject*>& lefts = leftLayer.GetGameObjects();

		Layer& rightLayer = scene->GetLayer(right);
		std::vector<GameObject*>& rights = rightLayer.GetGameObjects();

		// finds right layer Objects
		// 충돌 체크
		for (GameObject* left : lefts)
		{
			// 충돌체가 없다면 continue
			Collider* leftCol = left->GetComponent<Collider>();
			if (leftCol == nullptr)
				continue;

			for (GameObject* right : rights)
			{
				Collider* rightCol = right->GetComponent<Collider>();

				// 충돌체가 없다면 continue
				if (rightCol == nullptr)
					continue;

				// 자기 자신과 같은 경우 continue
				if (left == right)
					continue;

				// 충돌연산
				ColliderCollision(leftCol, rightCol);
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		// 두 충돌체의 ID를 확인
		ColliderID ID;
		ID.left = (UINT)left->GetID();
		ID.right = (UINT)right->GetID();

		// 이전 충돌체의 정보를 가져와서 확인한다.
		std::map<UINT64, bool>::iterator iter
			= mCollisionMap.find(ID.id);

		// 충돌정보가 없다면 생성
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(ID.id, false));
			iter = mCollisionMap.find(ID.id);
		}

		// 충돌함수 호출
		// 충돌했다면 
		if (Intersect(left, right))
		{
			// 처음 충돌하는 상태
			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);

				iter->second = true;

			}
			else // 충돌 중인상태
			{
				left->OnCollisionStay(right);
				right->OnCollisionStay(left);
			}
		}
		else
		{
			// 충돌을 빠져나간상태
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);

				iter->second = false;
			}
		}
	}

	bool CollisionManager::Intersect(Collider* left, Collider* right)	// 충돌 상태 여부
	{
		const auto left_position = left->GetPosition();
		const auto right_position = right->GetPosition();
		const auto left_size = left->GetSize();
		const auto right_size = right->GetSize();

		DirectX::SimpleMath::Rectangle leftRect{
			static_cast<long>(left_position.x), static_cast<long>(left_position.y), static_cast<long>(left_size.x),
			static_cast<long>(left_size.y)
		};
		DirectX::SimpleMath::Rectangle RightRect{
			static_cast<long>(left_position.x), static_cast<long>(left_position.y), static_cast<long>(left_size.x),
			static_cast<long>(left_size.y)
		};

		return leftRect.Intersects(RightRect);
	}

}