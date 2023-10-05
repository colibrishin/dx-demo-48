#pragma once
#include "..\\YamYamEngine_SOURCE\\yaScript.h"
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

	private:
		static float mTime;
	};
}
