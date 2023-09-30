#include "yaInput.h"
#include "yaApplication.h"

extern ya::Application application;

namespace ya
{
	std::vector<Input::Key> Input::mKeys;
	Vector2 Input::mMousPosition;

	int ASCII[(UINT)eKeyCode::END] =
	{
		//Alphabet
		'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
		'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
		'Z', 'X', 'C', 'V', 'B', 'N', 'M',

		//Special Key
		VK_RETURN, VK_ESCAPE, VK_LSHIFT, VK_LMENU, VK_LCONTROL,
		VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_LBUTTON, VK_RBUTTON,

		//Num Pad
		VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2,
		VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5,
		VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8,
		VK_NUMPAD9,

		//Num Line
		'0', '1', '2', '3', '4', '5',
		'6', '7', '8', '9',
	};


	void Input::Initialize()
	{
		for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
		{
			Key key;
			key.Code = (eKeyCode)i;
			key.State = eKeyState::None;
			key.bPressed = false;

			mKeys.push_back(key);
		}
	}

	void Input::Update()
	{
        HWND hwnd = application.GetHwnd();
        HWND Nowhwnd = GetFocus();

        POINT MousePos = {};

        // 현재 마우스 Pos 를 받아온다
        GetCursorPos(&MousePos);

        // 마우스 Pos 를 스크린 좌표에서 특정 클라이언트 좌표로 바꿔준다
        ScreenToClient(hwnd, &MousePos);
        mMousPosition.x = (float)MousePos.x;
        mMousPosition.y = (float)MousePos.y;

        if (hwnd == Nowhwnd)
        {
            for (int i = 0; i < (int)eKeyCode::END; i++)
            {
                //이전에 누른 적이 없고 호출 시점에서 눌린 상태 (0x8000)
                if (GetAsyncKeyState(ASCII[i]) & 0x8000)
                {
                    //이전 눌려져 있던 상태 (pressed)
                    if (mKeys[i].bPressed == true) //true
                    {
                        mKeys[i].State = eKeyState::Pressed;
                    }
                    else
                    {
                        mKeys[i].State = eKeyState::Down;
                    }

                    mKeys[i].bPressed = true;
                }
                //else if (GetAsyncKeyState(ASCII[i]) & 0)
                else //이전에 누른 적이 없고 호출 시점에서 입력이 안된 상태 (0x0000)
                {
                    //이전에 눌려져 있던 상태
                    if (mKeys[i].bPressed == true)
                    {
                        mKeys[i].State = eKeyState::Up;
                    }
                    else
                    {
                        mKeys[i].State = eKeyState::None;
                    }

                    mKeys[i].bPressed = false;
                }
            }

        }
        else // 현재 포커스중이 아니다 
        {
            for (UINT i = 0; i < (UINT)eKeyCode::END; i++)
            {
                mKeys[i].bPressed = false;

                if (mKeys[i].State == eKeyState::Down or mKeys[i].State == eKeyState::Pressed)
                {
                    mKeys[i].State = eKeyState::Up;
                }
                else if (mKeys[i].State == eKeyState::Up)
                {
                    mKeys[i].State = eKeyState::None;
                }
            }
        }
	}
}