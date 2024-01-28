#include "stdafx.h"
#include "Build.h"
#include "RepairTower.h"
extern bool DEBUGMODE;

RepairTower::RepairTower(int size, int hp, int length, int HealAmount)
{
	Hpbar = new ProgressBar(L"TowerProgressBar_1.png", OFFSET_LB);
	Hpbar->SetSize(size);
	base_hp = hp;
	Hpbar->CurHp = base_hp;
	Hpbar->MaxHp = base_hp;

	img = new ObImage(L"DefenceTower.png");
	img->pivot = OFFSET_LB;
	img->scale.x = size;
	img->scale.y = size;

	col = new ObRect();
	col->pivot = OFFSET_LB;
	col->scale.x = size;
	col->scale.y = size;

	img->SetParentRT(*col);
	Hpbar->SetParentRT(*col);

	interactionRect = new ObRect();
	interactionRect->isFilled = false;
	interactionRect->pivot = OFFSET_N;
	interactionRect->SetLocalPosX(size / 2);
	interactionRect->SetLocalPosY(size / 2);
	interactionRect->SetParentRT(*col);

	Base_Heal = HealAmount;

	base_range = length;
}

void RepairTower::Update()
{
	Build::Update();
	interactionRect->Update();

	Heal = Base_Heal + bonus_Heal;
	range = base_range + bonus_range;

	interactionRect->scale.x = range;
	interactionRect->scale.y = range;
}

void RepairTower::Render()
{
	Build::Render();
	if(DEBUGMODE)
	interactionRect->Render();
}
