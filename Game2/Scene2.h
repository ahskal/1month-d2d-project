#pragma once
class Scene2 : public Scene
{
private:
	ObImage* Loading;
	ObTileMap* map;
	Int2	   tileSize;

	int FindWallCount = 0;
	int FindNoneCount = 0;

	thread* test1;
public:
	Scene2();
	~Scene2();

	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

