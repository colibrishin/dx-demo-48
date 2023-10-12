#pragma once
#include "yaScript.h"
#include "yaTransform.h"

namespace ya
{
	class TurretScript : public Script
	{
	public:
		TurretScript();
		virtual ~TurretScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		Vector3 GetPosition()
		{
			return mTurretPos;
		}

	private:
		float mTime;
		static Vector3 mTurretPos;
	};
}
