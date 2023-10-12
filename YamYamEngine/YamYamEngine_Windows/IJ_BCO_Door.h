#pragma once
#include "IJ_ButtonConnectedObject.h"


namespace IJ
{
	class BCO_Door : public ButtonConnectedObject
	{
	public:
		BCO_Door();
		virtual ~BCO_Door();

		virtual void OnCollisionEnter(class ya::Collider* other);
		virtual void OnCollisionStay(class ya::Collider* other);
		virtual void OnCollisionExit(class ya::Collider* other);

	private:

	};
}
