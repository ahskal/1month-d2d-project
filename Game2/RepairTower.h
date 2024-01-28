#pragma once
class RepairTower : public Build
{
private:
	ObRect* interactionRect;
	vector<class Bullet*> bullet;

	int Heal;;
	int Base_Heal;;

	float range;
	float base_range;
public:

	RepairTower(int size, int hp, int length, int HealAmount);
	int bonus_Heal;;
	float bonus_range;

	void Update() override;
	void Render() override;

	vector<class Bullet*>& GetBulletVector() { return bullet; };
	int GetHeal() const { return Heal; };
	ObRect* GetInteractionRect() const { return interactionRect; }

};