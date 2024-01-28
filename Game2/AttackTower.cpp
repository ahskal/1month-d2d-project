#include "stdafx.h"
#include "Build.h"
#include "Bullet.h"
#include "AttackTower.h"
extern bool DEBUGMODE;

AttackTower::AttackTower(int size, int hp, int length, int Damage, Int2 maxFream)
{
	Hpbar = new ProgressBar();
	Hpbar->pivot = OFFSET_LB;
	Hpbar->SetSize(size);
	base_hp = hp;
	Hpbar->CurHp = base_hp;
	Hpbar->MaxHp = base_hp;

	img = new ObImage(L"AttackTower.png");
	img->pivot = OFFSET_LB;
	img->scale.x = size;
	img->scale.y = size;
	img->maxFrame = maxFream;


	col = new ObRect();
	col->pivot = OFFSET_LB;
	col->scale.x = size;
	col->scale.y = size;

	base_as = 1.0f;
	base_range = length;

	img->SetParentRT(*col);
	Hpbar->SetParentRT(*col);

	interactionRect = new ObCircle();
	interactionRect->isFilled = false;
	interactionRect->pivot = OFFSET_N;
	interactionRect->SetLocalPosX(size / 2);
	interactionRect->SetLocalPosY(size / 2);
	interactionRect->SetParentRT(*col);

	this->Damage = Damage;
}

void AttackTower::Update()
{

	as = base_as - bonus_as;
	range = base_range + bonus_range;

	interactionRect->scale.x = range;
	interactionRect->scale.y = range;


	Build::Update();
	interactionRect->Update();
	bullet.erase(
		std::remove_if(
			bullet.begin(),
			bullet.end(),
			[&](Bullet* bullet) {
				// 현재 체력이 0 이하인 경우 해당 몬스터를 제거하려면 true를 반환
				// 그렇지 않은 경우 유지하려면 false를 반환

				bool shouldRemove = !bullet->GetIsFire();
				if (shouldRemove) {
					delete bullet;
				}
				return shouldRemove;
			}
		),
		bullet.end() // remove_if를 통해 뒤로 옮겨진 원소들의 시작 지점
				);

	for (auto bulletPtr : bullet) {

		bulletPtr->Update();

	}

}

void AttackTower::Render()
{
	Build::Render();
	if (DEBUGMODE);
	interactionRect->Render();

	for (auto bulletPtr : bullet) {
		bulletPtr->Render();
	}
}
