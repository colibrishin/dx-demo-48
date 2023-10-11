#pragma once
#include "yaGameObject.h"
#include "yaTransform.h"

namespace ya
{
	class Light;

	class Lighting : public GameObject
	{
	public:
		Lighting(Light* origin);
		~Lighting() override = default;

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		Light* GetOrigin() const { return m_origin_; }

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

	private:
		Light* m_origin_;
	};
}
