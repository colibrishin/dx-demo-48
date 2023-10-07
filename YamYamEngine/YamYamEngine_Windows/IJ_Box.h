#pragma once
#include "yaGameObject.h"


namespace IJ
{
	class GO_Box : public ya::GameObject
	{
	public:
		// 지금 보니 그냥 bool 값으로 처리할 수 있을 것 같다
		enum eBoxState
		{
			IDLE,
			GRABBED,
			END,
		};

		GO_Box();
		virtual ~GO_Box();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class ya::Collider* other);
		virtual void OnCollisionStay(class ya::Collider* other);
		virtual void OnCollisionExit(class ya::Collider* other);

		void Idle();
		void Grabbed();

		eBoxState GetBoxState() { return e_Current_Box_State; }
		void SetBoxState(eBoxState box_state) { e_Current_Box_State = box_state; }
		GameObject* GetGrabber() { return m_Grabber; }
		void SetGrabber(GameObject* grabber) { m_Grabber = grabber; }

	private:
		eBoxState e_Current_Box_State;
		GameObject* m_Grabber;
	};
}
