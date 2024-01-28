#include "stdafx.h"
#include "Build.h"
#include "ProgressBar.h"
#include "DefenceTower.h"

DefenceTower::DefenceTower(int size, int hp)
{
	Hpbar = new ProgressBar(L"TowerProgressBar_0.png", OFFSET_LB);
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
}
