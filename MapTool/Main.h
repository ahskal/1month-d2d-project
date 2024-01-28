#pragma once

#define MAXLAYER 4

class Main : public Scene
{
private:
	ObTileMap* map[MAXLAYER];
	int LayerIdx;
	int SelectLayerIdx;

	Int2		tileSize;
	ObRect*		LineX, *LineY;

	int			brushImgIdx;
	Int2		brushFrame;
	int			brushState;
	Color		brushColor;

	bool isApiScreen;



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
