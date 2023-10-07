#pragma once
#include "yaScript.h"

namespace ya
{
	class BulletScript : public Script
	{
	public:
		BulletScript();
		virtual ~BulletScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

	private:

	};
}
