#pragma once

class Main : public Scene
{
private:
	ObTileMap* map;
	Int2		tileSize;

	bool isApiScreen;

	int FindWallCount = 0;
	int FindNoneCount = 0;

	thread* test1;
	bool step[41];
	int StepCount;
	float TotalTime;

public:
	Main();
	~Main();
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
