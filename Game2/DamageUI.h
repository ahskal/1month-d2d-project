#pragma once
class DamageUI 
{
private:
	struct Damage {
		wstring text;
		Vector2 Pos;
		Vector2 uiPos;
		Vector2 RenderPos;
		int		size;
		float	timer;
		Color	color;
		int idx;
		float Offset_Y;
	};

public:
	vector<Damage*> damage;
	DamageUI();

	void Create(wstring text, Vector2 pos, int size = 20);
	void Update();
	void Render();


};

