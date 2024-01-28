#pragma once
class BuildManager : public Singleton<BuildManager>
{
private:

	vector<class Build*> build;




	float RepairTimer;

public:
	int repairHealing;

	BuildManager();
	~BuildManager();

	void Init();
	void Update();
	void LateUpdate();
	void Render();

	void UpdateStatus(float hp, float as, float range,float healing);


	void Create(Vector2 Pos, int Type);

	vector<class Build*>& GetBuildVector() { return build; };

};

