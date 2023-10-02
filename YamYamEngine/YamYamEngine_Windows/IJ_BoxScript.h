#pragma once
#include "..\\YamYamEngine_SOURCE\\yaScript.h"


namespace IJ
{
	class BoxScript : public ya::Script
	{
	public:
		BoxScript();
		virtual ~BoxScript();

		void Initialize() override;
		void Update() override;
		void LateUpdate() override;
		void Render() override;

		void Idle();
		void Grabbed();
	};
}
