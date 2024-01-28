#pragma once
class AttackTower : public Build
{
private:
	ObCircle* interactionRect;
	int Damage;
	Vector2 Target;

	float base_as;
	
	float range;
	float base_range;

public:
	float bonus_range;
	float bonus_as;
	float as;

	vector<class Bullet*> bullet;

	float timer = 0;
	AttackTower(int size, int hp, int length, int Damage);
	AttackTower(int size, int hp, int length, int Damage,Int2 maxFream);

	void Update() override;
	void Render() override;

	vector<class Bullet*> GetBulletVector() { return bullet; };
	ObCircle * GetInteractionRect() const { return interactionRect; }
	void GetTargetPos(Vector2 pos) { Target = pos; }
	void SetImageFreamY(int idx) { img->frame.y = idx; }
};