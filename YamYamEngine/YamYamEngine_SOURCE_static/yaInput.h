#pragma once
#include "CommonInclude.h"
#include "yaApplication.h"
#include "YamYamEngine.h"
#include "yaCamera.h"

using namespace ya::math;

extern ya::Application application;

namespace ya
{
	enum class eKeyCode
	{
		//Alphabet
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		//Special Key
		ENTER, ESC, LSHIFT, LALT, LCTRL,
		SPACE, LEFT, RIGHT, UP, DOWN,
		LBTN, RBTN,

		//Num Pad
		NUM_0, NUM_1, NUM_2,
		NUM_3, NUM_4, NUM_5,
		NUM_6, NUM_7, NUM_8,
		NUM_9,

		//Num Line
		N_0, N_1, N_2, N_3, N_4, N_5,
		N_6, N_7, N_8, N_9,

		END,
	};
	enum class eKeyState
	{
		Down,
		Up,
		Pressed,
		None
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode Code;
			eKeyState State;
			bool bPressed;
		};

		static void Initialize();
		static void Update();

		__forceinline static bool GetKeyDown(eKeyCode code)
		{
			return mKeys[(int)code].State == eKeyState::Down;
		}
		__forceinline static bool GetKeyUp(eKeyCode code)
		{
			return mKeys[(int)code].State == eKeyState::Up;
		}
		__forceinline static bool GetKey(eKeyCode code)
		{
			return mKeys[(int)code].State == eKeyState::Pressed;
		}
		__forceinline static bool GetKeyNone(eKeyCode code)
		{
			return mKeys[(int)code].State == eKeyState::None;
		}

		static __forceinline Vector2 GetMousPosition()
		{
			return mMousPosition;
		}

		static __forceinline Vector3 GetNormalizedMousePosition()
		{
			// 마우스의 위치를 -1 ~ 1 사이의 값으로 변환. 화면은 (0,0,0) 기준으로 4분면으로 나눌 수 있기 때문.
			// 유의사항 : z 값에 따라 x, y 값이 크게 뛸 수 있는데, 이는 3차원 좌표계이기 때문.
			// 여기서는 2차원 좌표계만을 가정하고 설계하기 때문에 z 값을 0으로 고정.
			// https://gamedev.stackexchange.com/questions/116172/screen-point-to-world-space-conversion
			return {
				(float)((2.0 * ((float)mMousPosition.x) / (float)application.GetWidth()) - 1.0f),
				(float)((2.0 * (((float)mMousPosition.y) / (float)application.GetHeight()) - 1.0f) * -1.0f),
				0.0f};
		}

		static __forceinline Vector3 GetCoordinationMousePosition()
		{
			// TODO: PerspectiveLH인 Projection일때 의도하는대로 작동 안하는 듯함.

			const auto normalized_mouse = GetNormalizedMousePosition();

			// 현재 화면의 중심을 기준으로 좌표를 변환하기 위해 MVP 행렬의 역을 구해야 함. 여기서 행렬식은 역행렬이 존재하는지 확인하는 용도로 사용.
			// (화면에 렌더링 할때 좌표에 MVP 행렬을 곱한 걸 생각하면, 현재 마우스의 위치를 역으로 ~MVP를 곱해서 좌표로 변환할 수 있는 걸로 추측.)
			XMVECTOR det = DirectX::XMMatrixDeterminant(Camera::GetViewMatrix() *  Camera::GetProjectionMatrix());

			// 역행렬을 구하고, 정규화된 마우스 좌표에 역행렬을 이용해 좌표를 변환.
			const auto inverse = DirectX::XMMatrixInverse(
				&det, Camera::GetViewMatrix() * Camera::GetProjectionMatrix());

			// 주의사항: 물체에 z값을 대입할 때, 물체의 원래 z값을 사용하는 것이 보통 의도한 대로 작동할 것.
			return XMVector3TransformCoord(normalized_mouse, inverse);
		}

	private:
		Input() = delete;
		~Input() = delete;

	private:
		static std::vector<Key> mKeys;
		static Vector2 mMousPosition;
	};
}

