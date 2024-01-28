#include "stdafx.h"
#include "TypeMonster.h"
#include "DamageUI.h"

DamageUI::DamageUI()
{

}

void DamageUI::Create(wstring text, Vector2 pos, int size)
{

	Vector2 Pos = GetAdjustedPosition(pos);
	Damage* Dmg = new Damage();
	Dmg->text = text;
	Dmg->Pos = Pos;
	Dmg->size = size;
	Dmg->timer = 0;
	Dmg->color = Color(1, 1, 1, 1);


	damage.push_back(Dmg);


}

void DamageUI::Update()
{
	damage.erase(
		std::remove_if(
			damage.begin(),
			damage.end(),
			[&](Damage* dmg) {
				bool isTimeOver = dmg->timer >= 3.0f;
				if (isTimeOver) {
					//delete dmg;
				}
				return isTimeOver;
			}
		),
		damage.end()
				);
	for (int i = 0; i < damage.size(); i++) {
		damage[i]->timer += DELTA;
		damage[i]->Offset_Y += DELTA * 70;
		//damage[i]->RenderPos = GetAdjustedPosition(damage[i]->Pos, damage[i]->Offset_Y);
		damage[i]->color.w = 1.0f - (damage[i]->timer/2);
	}
}

void DamageUI::Render()
{
	for (auto DamagePtr : damage) {
		DWRITE->PosRenderText(DamagePtr->text, DamagePtr->RenderPos, DamagePtr->color, DamagePtr->size);
	}
}
