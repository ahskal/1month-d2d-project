#pragma once
class Scene4 : public Scene
{
private:

public:
	Scene4();
	~Scene4();

	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

