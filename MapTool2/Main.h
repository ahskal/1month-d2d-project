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
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
