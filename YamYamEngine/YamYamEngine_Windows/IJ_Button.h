#pragma once
#include "yaGameObject.h"


namespace IJ
{
	class GO_Button : public ya::GameObject
	{
	public:
		enum eButtonType
		{
			Hold,
			Toggle,
			Once,
			END_BT,
		};
		enum eButtonState // <- 굳이 필요한가?
		{
			Idle,
			Pressing,
			END_BS,
		};

		GO_Button();
		virtual ~GO_Button();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class ya::Collider* other);
		virtual void OnCollisionStay(class ya::Collider* other);
		virtual void OnCollisionExit(class ya::Collider* other);

		eButtonType GetButtonType() { return m_Button_Type; }
		void SetButtonType(eButtonType type) { m_Button_Type = type; }
		eButtonState GetButtonState() { return m_Current_Button_State; }
		void SetButtonState(eButtonState state) { m_Current_Button_State = state; }

		void ConnectGameObject(ya::GameObject* gameobject) { Connected_GameObjects.push_back(gameobject); }

	private:
		eButtonType m_Button_Type;
		eButtonState m_Current_Button_State;
		std::vector<ya::GameObject*> Connected_GameObjects;
	};
}
