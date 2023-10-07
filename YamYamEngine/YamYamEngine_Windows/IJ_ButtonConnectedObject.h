#pragma once
#include "yaGameObject.h"


namespace IJ
{
	class ButtonConnectedObject : public ya::GameObject
	{
	public:
		enum eBCOState
		{
			Activated,
			Disabled,
			END,
		};

		ButtonConnectedObject();
		virtual ~ButtonConnectedObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class ya::Collider* other);
		virtual void OnCollisionStay(class ya::Collider* other);
		virtual void OnCollisionExit(class ya::Collider* other);

		eBCOState GetBCOState() { return m_Current_BCO_State; }
		void SetBCOState(eBCOState state) { m_Current_BCO_State = state; }

	private:
		eBCOState m_Current_BCO_State;
	};
}
