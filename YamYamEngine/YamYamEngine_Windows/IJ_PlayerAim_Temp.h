#pragma once
#include "yaPlayer.h"
#include "yaCollider.h"
#include "IJ_Box.h"


namespace IJ
{
	class PlayerAim_Temp : public ya::GameObject
	{
	public:
		PlayerAim_Temp();
		virtual ~PlayerAim_Temp();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void OnCollisionEnter(class ya::Collider* other);
		virtual void OnCollisionStay(class ya::Collider* other);
		virtual void OnCollisionExit(class ya::Collider* other);

	private:
		ya::Player* m_Owner_Player;
		std::vector<GO_Box*> Boxes_In_Collision;
		GO_Box* m_Box_Grabbing;
	};
}
