#pragma once
#include "CommonInclude.h"
#include "YamYamEngine.h"

using namespace ya::math;

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

	private:
		Input() = delete;
		~Input() = delete;

	private:
		static std::vector<Key> mKeys;
		static Vector2 mMousPosition;
	};
}

