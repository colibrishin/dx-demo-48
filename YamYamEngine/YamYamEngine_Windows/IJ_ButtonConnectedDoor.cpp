#include "IJ_ButtonConnectedDoor.h"


namespace IJ
{
	ButtonConnectedDoor::ButtonConnectedDoor()
	{
	}

	ButtonConnectedDoor::~ButtonConnectedDoor()
	{
	}

	// 비활성화(기본) 상태에서는 길을 막습니다
	// 활성화 상태일 때에 충돌 판정이 없어집니다 (보이기는 계속 보입니다)
	void ButtonConnectedDoor::OnCollisionEnter(ya::Collider* other)
	{
		if (GetBCOState() == ButtonConnectedObject::eBCOState::Disabled)
			ButtonConnectedObject::OnCollisionEnter(other);
	}

	void ButtonConnectedDoor::OnCollisionStay(ya::Collider* other)
	{
		if (GetBCOState() == ButtonConnectedObject::eBCOState::Disabled)
			ButtonConnectedObject::OnCollisionStay(other);
	}

	void ButtonConnectedDoor::OnCollisionExit(ya::Collider* other)
	{
		if (GetBCOState() == ButtonConnectedObject::eBCOState::Disabled)
			ButtonConnectedObject::OnCollisionExit(other);
	}
}