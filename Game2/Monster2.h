#pragma once

class Monster2 : public TypeMonster
{
private:

	int dir[6];
	int index;


	bool is_atk;

	float timer;

	Vector2 AttackSize;

public:
	Monster2(wstring file, Int2 maxFream, wstring file2, Int2 maxFream2,
		float length, int Hp, int attackSize, float aniSpeed = 0.7f, int atk = 10, int dropExp = 0);
	~Monster2() override;

	void Move(Vector2 TargetPos);

	void Init(Vector2 spawn);

	void Update();
	void LateUpdate();
	void Render();

	void Attack();
};

