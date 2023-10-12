#pragma once
#include "IJ_ButtonConnectedObject.h"
#include "yaTransform.h"


namespace IJ
{
	class BCO_Light;

	class BCO_Lighting : public ButtonConnectedObject
	{
	public:
		BCO_Lighting(BCO_Light* origin);
		~BCO_Lighting() override = default;

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		BCO_Light* GetOrigin() const { return m_origin_; }

		void OnCollisionEnter(ya::Collider* other) override;
		void OnCollisionStay(ya::Collider* other) override;
		void OnCollisionExit(ya::Collider* other) override;

	private:
		BCO_Light* m_origin_;
	};
}
