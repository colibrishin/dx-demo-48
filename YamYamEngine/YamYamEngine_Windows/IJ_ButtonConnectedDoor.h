#pragma once
#include "IJ_ButtonConnectedObject.h"


namespace IJ
{
	class ButtonConnectedDoor : public ButtonConnectedObject
	{
	public:
		ButtonConnectedDoor();
		virtual ~ButtonConnectedDoor();

		virtual void OnCollisionEnter(class ya::Collider* other);
		virtual void OnCollisionStay(class ya::Collider* other);
		virtual void OnCollisionExit(class ya::Collider* other);

	private:

	};
}
