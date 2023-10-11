#pragma once
#include "yaGameObject.h"
#include "yaLighting.h"

namespace ya
{
	class Light : public GameObject
	{
	public:
		Light(float light_range);
		~Light() override = default;

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void OnCollisionEnter(Collider* other) override;
		void OnCollisionStay(Collider* other) override;
		void OnCollisionExit(Collider* other) override;

		float GetLightRange() const { return m_light_range_; }

		const std::vector<Lighting*>& GetLightings() const { return m_lightings_; }

	private:
		friend class Lighting;

		std::vector<Lighting*> m_lightings_;
		float m_light_range_;
	};
}
