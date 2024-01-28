#include "stdafx.h"
#include "DamageUI.h"
#include "ProgressBar.h"


ProgressBar::ProgressBar()
{
	Hp_Scale.x = 1.f;
	Hp_Scale.y = 0.2f;

	size = 100;

	CurrentHp_img = make_unique<ObImage>(L"CurHP_2.png");
	CurrentHp_img->pivot = OFFSET_L;

	MaxHp_img = make_unique<ObImage>(L"MaxHP_2.png");
	MaxHp_img->pivot = OFFSET_L;

	damageUI = new DamageUI();

	CurrentHp_img->SetParentRT(*this);
	MaxHp_img->SetParentRT(*this);

	MaxHp = CurHp = 100;
}

ProgressBar::ProgressBar(wstring fileName, Vector2 pivot)
{
	Hp_Scale.x = 1.f;
	Hp_Scale.y = 1.f;

	size = 200;

	CurrentHp_img = make_unique<ObImage>(fileName);
	CurrentHp_img->pivot = pivot;

	MaxHp_img = make_unique<ObImage>(L"Tile_NONE.png");
	MaxHp_img->pivot = pivot;

	damageUI = new DamageUI();

	CurrentHp_img->SetParentRT(*this);
	MaxHp_img->SetParentRT(*this);

	MaxHp = CurHp = 100;
	isVisible = false;
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::Update()
{
	ObRect::Update();

	for (int i = 0; i < damageUI->damage.size(); i++) {
		damageUI->damage[i]->Pos = this->GetWorldPos() + Vector2(size / 2, size / 2);
	}
	MaxHp_img->scale.x = size * Hp_Scale.x;
	MaxHp_img->scale.y = size * Hp_Scale.y;
	CurrentHp_img->scale.y = size * Hp_Scale.y;

	// 현재 체력에 대한 전체 체력에 대한 비율 계산
	float hpRatio = static_cast<float>(CurHp) / static_cast<float>(MaxHp);

	// 비율에 맞게 CurrentHp 이미지의 UV값 조정
	CurrentHp_img->uv.z = hpRatio;

	// 이미지의 크기 조정 (전체 이미지 크기에 비례해서 남은 체력 부분만 보이도록)
	CurrentHp_img->scale.x = size * Hp_Scale.x * hpRatio;

	// CurHp가 0 이하로 내려가지 않도록 보정
	if (CurHp < 0) CurHp = 0;
	// CurHp가 MaxHp를 넘지 않도록 보정
	if (CurHp > MaxHp) CurHp = MaxHp;
	// 이미지 업데이트

	if (hitCooltime > 0.0f)
	{
		hitCooltime -= DELTA;
	}
	else {
		hit = false;
	}

	if (rePairCooltime > 0.0f)
	{
		rePairCooltime -= DELTA;
	}
	else {
		rePair = false;
	}

	MaxHp_img->Update();
	CurrentHp_img->Update();
	damageUI->Update();
}

void ProgressBar::Render()
{
	ObRect::Render();
	MaxHp_img->Render();
	CurrentHp_img->Render();
	damageUI->Render();

}

void ProgressBar::Damage(int damage, int color) {
	if (hitCooltime <= 0.0f)
	{
		CurHp -= damage;
		hitCooltime = 0.01f;
		//cout << this->GetWorldPos().x<< this->GetWorldPos().y << endl;
		DAMAGE->AddText(this->GetWorldPos() + Vector2(50, 50), damage, color);
		hit = true;
	}
}

void ProgressBar::Repair(int damage, int color) {
	if (rePairCooltime <= 0.0f)
	{
		CurHp += damage;
		rePairCooltime = 0.01f;
		//cout << this->GetWorldPos().x<< this->GetWorldPos().y << endl;
		DAMAGE->AddText(this->GetWorldPos() + Vector2(50, 50), damage, color);
		rePair = true;
	}
}