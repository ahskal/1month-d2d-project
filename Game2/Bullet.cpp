#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet()
{
	scale.x = 20.0f;
	scale.y = 20.0f;
	isFire = false;
	pivot = OFFSET_L;
	isGravity = false;
}
Bullet::Bullet(wstring file, Vector2 pivct, Int2 maxFream)
{
	img = make_unique<ObImage>(file);
	img->maxFrame = maxFream;
	pivot = pivct;
	hasImage = true;
	isFire = false;
	isFilled = false;
	hasAxis = false;
	isGravity = false;
	startPos = Vector2();
}
Bullet::~Bullet(){}

//void Bullet::Fire(GameObject* StartObj, Vector2 scale, float Power, float lifeTime)
//{
//	if (lifeTime == 0.0f) {
//		isLifeTime = false;
//	}
//	else {
//		isLifeTime = true;
//	}
//	hasLength = false;
//
//	SetWorldPos(StartObj->GetWorldPos());
//	startPos = StartObj->GetWorldPos();
//	this->scale = scale;
//	this->lifeTime = lifeTime;
//	this->pressPower = Power;
//
//	isFire = true;
//
//	fireDir = StartObj->GetRight();
//
//	if (hasImage) {
//		img->SetParentRT(*this);
//		this->scale.x = img->imageSize.x * 1.5f + 10;
//		this->scale.y = img->imageSize.y * 1.5f + 10;
//		img->scale.x = img->imageSize.x * 1.5f;
//		img->scale.y = img->imageSize.y * 1.5f;
//	}
//}
//
//void Bullet::Fire(GameObject* StartObj, Vector2 dir, Vector2 scale, float Power, float lifeTime)
//{
//	if (lifeTime == 0.0f) {
//		isLifeTime = false;
//	}
//	else {
//		isLifeTime = true;
//	}
//	hasLength = false;
//
//	SetWorldPos(StartObj->GetWorldPos());
//	startPos = StartObj->GetWorldPos();
//	this->scale = scale;
//	this->lifeTime = lifeTime;
//	this->pressPower = Power;
//
//	isFire = true;
//
//	fireDir = StartObj->GetRight();
//
//	rotation.z = atan2f(dir.y, dir.x);
//
//	if (hasImage) {
//		img->SetParentRT(*this);
//		this->scale.x = img->imageSize.x * 1.5f + 10;
//		this->scale.y = img->imageSize.y * 1.5f + 10;
//		img->scale.x = img->imageSize.x * 1.5f;
//		img->scale.y = img->imageSize.y * 1.5f;
//		img->ChangeAnim(ANIMSTATE::LOOP, 1.0);
//	}
//}
//
//void Bullet::Fire(Vector2 pos, Vector2 dir, Vector2 scale, float Power, float Length)
//{
//	SetWorldPos(pos);
//	startPos = pos;
//	this->scale = scale;
//	this->pressPower = Power;
//
//	isFire = true;
//	length = Length;
//}
//
//void Bullet::Fire(GameObject* shooter, float pressPower)
//{
//	lifeTime = 10.0f;
//	scale.x = pressPower * 0.1f;
//	scale.y = scale.x * 0.2f;
//	isFire = true;
//	SetWorldPos(shooter->GetWorldPos());
//
//	this->pressPower = pressPower;
//	fireDir = shooter->GetRight();
//
//	gravityDir = DOWN;
//	gravityForce = 0.0f;
//
//
//	//fireDir = shooter->GetRight();
//	//rotation.z = atan2f(shooter->GetRight().y, shooter->GetRight().x);
//}

void Bullet::Fire(Vector2 pos, Vector2 dir, float pressPower)
{
	lifeTime = 2.0f;
	if (lifeTime == 0.0f) {
		isLifeTime = false;
	}
	else {
		isLifeTime = true;
	}

	scale.x = 20;
	scale.y = 5;
	this->pressPower = pressPower;
	isFire = true;
	SetWorldPos(pos);
	//fireDir = shooter->GetRight();
	rotation.z = atan2f(dir.y, dir.x);

	if (hasImage) {
		img->SetParentRT(*this);
		this->scale.x = img->imageSize.x * 1.5f + 10;
		this->scale.y = img->imageSize.y * 1.5f + 10;
		img->scale.x = img->imageSize.x * 1.5f;
		img->scale.y = img->imageSize.y * 1.5f;

		//img->rotation.z = atan2f(dir.y, dir.x);
		//img->SetWorldPos(pos);

	}

}

void Bullet::Fire(Vector2 pos, Vector2 dir, float Power, float Length)
{
	if (lifeTime == 0.0f) {
		isLifeTime = false;
	}
	else {
		isLifeTime = true;
	}
	if (Length == 0) {
		hasLength = false;
	}
	else {
		hasLength = true;
		length = Length;
	}
	SetWorldPos(pos);
	startPos = pos;
	scale.x = 20;
	scale.y = 5;
	this->lifeTime = lifeTime;
	this->pressPower = Power;

	isFire = true;

	fireDir = dir;

	rotation.z = atan2f(dir.y, dir.x);

	if (hasImage) {
		img->SetParentRT(*this);
		this->scale.x = img->imageSize.x * 1.5f + 10;
		this->scale.y = img->imageSize.y * 1.5f + 10;
		img->scale.x = img->imageSize.x * 1.5f;
		img->scale.y = img->imageSize.y * 1.5f;
	}
}

void Bullet::Fire(Vector2 pos, Vector2 dir, Vector2 scale, float Power, float Length)
{
	if (lifeTime == 0.0f) {
		isLifeTime = false;
	}
	else {
		isLifeTime = true;
	}
	if (Length == 0) {
		hasLength = false;
	}
	else {
		hasLength = true;
		length = Length;
	}

	SetWorldPos(pos);
	startPos = pos;
	this->scale = scale;
	this->lifeTime = lifeTime;
	this->pressPower = Power;

	isFire = true;

	fireDir = dir;

	rotation.z = atan2f(dir.y, dir.x);

	if (hasImage) {
		img->SetParentRT(*this);
		this->scale.x = img->imageSize.x * 1.5f + 10;
		this->scale.y = img->imageSize.y * 1.5f + 10;
		img->scale.x = img->imageSize.x * 1.5f;
		img->scale.y = img->imageSize.y * 1.5f;
		img->ChangeAnim(ANIMSTATE::LOOP, 1.0);
	}
	isFilled = false;
}

void Bullet::Drop(Vector2 pos)
{
	lifeTime = 30.0f;
	scale.x = 20;
	scale.y = 5;
	isFire = true;
	SetWorldPos(pos);

	//½î´ÂÈû ³ª¾Æ°¥¹æÇâ
	this->pressPower = 0.0f;
	fireDir = Vector2(0, 0);

	gravityDir = DOWN;
	gravityForce = 0.0f;
	//rotation.z = atan2f(DOWN.y, DOWN.x);
}

void Bullet::Update()
{
	if (not isFire) return;

	ObRect::Update();

	if (isGravity) {
		Vector2 velocity = (fireDir * pressPower * gravityDir*gravityForce);
		MoveWorldPos(GetRight() * DELTA * pressPower);
	}
	else {
		Vector2 velocity = (fireDir * pressPower);
		MoveWorldPos(GetRight() * DELTA * pressPower);
	}

	if (isLifeTime) {
		lifeTime -= DELTA;
		if (lifeTime <= 0.0f)
		{
			isFire = false;
		}
	}
	if (hasLength) {
		if ((startPos - GetWorldPos()).Length() >= length)
		{
			isFire = false;
		}
	}
	if (hasImage)
		img->Update();
	

	

	
}

void Bullet::Render()
{
	if (not isFire) return;

	ObRect::Render();
	if (hasImage)
		img->Render();
}

bool Bullet::Touch(GameObject* target)
{
	if ((GetWorldPos() - target->GetWorldPos()).Length() <
		7 + target->scale.x * 0.5f)
	{
		return true;
	}

	return false;
}
