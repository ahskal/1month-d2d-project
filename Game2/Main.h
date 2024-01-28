#pragma once

#define SoundSize 10

class Main : public Scene
{
private:

	float Sound[SoundSize];





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
