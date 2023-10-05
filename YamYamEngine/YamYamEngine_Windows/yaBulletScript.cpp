#include "yaBulletScript.h"
#include "yaMeshRenderer.h"
#include "yaTransform.h"
#include "yaTime.h"
#include "yaBullet.h"

namespace ya
{
	BulletScript::BulletScript()
	{
	}
	BulletScript::~BulletScript()
	{
	}
	void BulletScript::Initialize()
	{
	}
	void BulletScript::Update()
	{
		GameObject* obj = GetOwner();
		Bullet* bullet = dynamic_cast<Bullet*>(obj);

		Transform* tr = obj->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.x -= 2.0f * Time::DeltaTime();

		tr->SetPosition(pos);
	}
	void BulletScript::LateUpdate()
	{
	}
	void BulletScript::Render()
	{
	}
}