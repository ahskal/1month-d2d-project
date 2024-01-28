#pragma once
class ProgressBar : public ObRect
{
private:
	unique_ptr<ObImage> CurrentHp_img;
	unique_ptr<ObImage> MaxHp_img;

	class DamageUI* damageUI;


	Vector2 Hp_Scale;
	Vector2 Hp_Pos;

	float size;

	float hitCooltime;
	bool hit;

	float rePairCooltime;
	float rePair;

public:

	float CurHp;
	float MaxHp;

	ProgressBar();;
	ProgressBar(wstring fileName, Vector2 pivot);
	~ProgressBar();

	void Update();
	void Render();

	void SetSize(float size) { this->size = size; };

	bool isHit() {
		return hit;
	}

	bool isAlive()
	{
		return CurHp > 0;
	}

	void Damage(int damage, int color);

	void Repair(int damage, int color);

};

