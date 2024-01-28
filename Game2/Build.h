#include "stdafx.h"
#include "ProgressBar.h"

#pragma once
class Build
{
private:

protected:
	ProgressBar* Hpbar;
	ObImage* img;
	ObRect* col;

	float base_hp;

public:
	float bonus_hp;
	Build() = default;
	virtual ~Build() {};
	virtual void Update()
	{
		Hpbar->MaxHp = base_hp + bonus_hp;

		col->Update();
		img->Update();
		Hpbar->Update();
	};
	virtual void Render()
	{
		//col->Render();
		img->Render();
		Hpbar->Render();
	};
	Vector2 GetWorldPos() const { return col->GetWorldPos(); }
	Vector2 GetWorldPivot() const { return col->GetWorldPivot(); }

	ObRect* GetCollision() const { return col; }
	void SetPos(Vector2 pos) { col->SetWorldPos(pos); }

	bool IsDeadOrAlive() const { return Hpbar->CurHp < 0; }
	ProgressBar* GetHpbar() const { return Hpbar; }

};