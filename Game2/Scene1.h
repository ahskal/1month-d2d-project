#pragma once



class Scene1 : public Scene
{
private:

	class ObTileMap* map;
	class Camera* cam;
	class Player* pl;
	class PlayerUI* UI;

	float timer = 0;

	Vector2 Position;

	float timer2;

	int SelectLength;

	bool isCreate = false;

	

	int buildType = 0;


	thread* test1;
public:

	float scale = 5;


	Scene1();
	~Scene1();

	void randomPos();

	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

