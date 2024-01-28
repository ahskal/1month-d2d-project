#pragma once

extern bool DEBUGMODE;

class Scene3 : public Scene
{
private:

	struct Button {
		ObImage* button;
		ObImage* OnButton;
		ObRect* col;
		wstring wstr;
		bool OnMouse = false;
		bool isFadingInOut = true;
		Color color = Color(1, 1, 1, 1);

		

		void Update() {
			col->Update();
			button->Update();
			OnButton->Update();

			if (col->Intersect(INPUT->GetWorldMousePos())) {
				OnMouse = true;
				if (isFadingInOut) {
					OnButton->color.w -= DELTA;
					if (OnButton->color.w < 0.0) isFadingInOut = false;
				}
				else {
					OnButton->color.w += DELTA;
					if (OnButton->color.w > 0.5) isFadingInOut = true;
				}
				if (INPUT->KeyDown(VK_LBUTTON)) {

				}
			}
			else {
				OnMouse = false;
			}



		};
		void Render() {
			if (DEBUGMODE);
				col->Render();
			button->Render();
			if (OnMouse)
				OnButton->Render();
			DWRITE->PosRenderText(wstr, GetAdjustedPositionXY(col->GetWorldPos(), Vector2(wstr.size() * 15, +15)), color, 30);
		};

		void Update2() {
			col->Update();
			button->Update();
			if (OnMouse);
			OnButton->Update();
		}
	};
	Button* button_1;
	Button* button_2;
	Button* button_3;

	unique_ptr<ObImage> Opening_1;
	unique_ptr<ObImage> Opening_2;
	unique_ptr<ObImage> Opening_3;
	unique_ptr<ObImage> Opening_4;
	unique_ptr<ObImage> Opening_5;
	unique_ptr<ObImage> Opening_6;

	float LevelScale;
	float Animation_Scale1;
	float Animation_Scale2;
	float Animation_Scale3;

	bool animation_Event_1;
	bool animation_Event_2;
	bool animation_Event_3;
	bool animation_Event_4;
	bool animation_Event_5;
	bool animation_Event_6;
	bool animation_Event_7;

	bool SceneChange;

	unique_ptr<ObImage> Opening_img_1;
	unique_ptr<ObImage> Opening_img_2;

	bool isExit;

	ObImage* FadeOut;

	ObImage* SettingUI;
	bool SettingUI_PopUp;

	Button* button_4;



public:
	Scene3();
	~Scene3();

	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};

