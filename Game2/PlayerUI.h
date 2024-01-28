#pragma once

#define Padding 10
#define ButtonCount 6

extern bool DEBUGMODE;

class PlayerUI
{
private:
	friend class Player;

private:
	struct ElementUI {
		ObImage* UI;
		ObImage* Type;
		Vector2 Pos;

		void Update()
		{
			UI->Update();
			Type->Update();
		}
		void Render()
		{
			UI->Render();
			Type->Render();
		}
		void Render(Camera* cam)
		{
			UI->Render(cam);
			Type->Render(cam);
		}
	};
	ElementUI* Element;

	struct GameHpUI {
		ObImage* UI;
		ObImage* HpBar1;
		ObImage* HpBar2;
		ObImage* HpBar3;
		ObImage* ExpBar;

		Vector2 Pos;
		//HpUI
		//HpBar
		//HpText

		void Update()
		{
			UI->Update();
			HpBar1->Update();
			HpBar2->Update();
			HpBar3->Update();
			ExpBar->Update();
		}
		void Render()
		{
			UI->Render();
			HpBar1->Render();
			HpBar2->Render();
			HpBar3->Render();
			ExpBar->Render();
		}
		void Render(Camera* cam)
		{
			UI->Render(cam);
			HpBar1->Render(cam);
			HpBar2->Render(cam);
			HpBar3->Render(cam);
			ExpBar->Render(cam);
		}
	};
	GameHpUI* Hp;

	struct GameEXPUI {
		ObImage* ExperienceGain_img1;
		ObImage* ExperienceGain_img2;
		ObImage* ExperienceGain_img3;
		int Exp;

		void Update()
		{
			ExperienceGain_img1->Update();
			ExperienceGain_img2->Update();
			ExperienceGain_img3->Update();
		}
		void Render()
		{
			ExperienceGain_img1->Render();
			ExperienceGain_img2->Render();
			ExperienceGain_img3->Render();
		}
		void Render(Camera* cam)
		{
			ExperienceGain_img1->Render(cam);
			ExperienceGain_img2->Render(cam);
			ExperienceGain_img3->Render(cam);
		}
	};
	GameEXPUI* ExpUI;

	struct GamePlayUI {

		ObImage* img_Level;
		//ObImage* img_MaxHp;
		ObImage* img_ATK;
		ObImage* img_DEF;
		Vector2 Scale;
		int Level;
		int Atk;
		int Def;
		void Update()
		{
			img_Level->Update();
			//img_MaxHp->Update();
			img_ATK->Update();
			img_DEF->Update();
		}
		void Render()
		{
			img_Level->Render();
			//img_MaxHp->Render();
			img_ATK->Render();
			img_DEF->Render();
		}
		void Render(Camera* cam)
		{
			img_Level->Render(cam);
			//img_MaxHp->Render(cam);
			img_ATK->Render(cam);
			img_DEF->Render(cam);


			//Vector2 Pos;
			//Pos.x = Hp->UI->GetWorldPivot().x + app.GetHalfWidth() + Scale.x * (15) - ((to_string((int)CurHp).size() * (6) * Scale.x));
			//Pos.y = app.GetHalfHeight() - Hp->UI->GetWorldPivot().y - Scale.y * (8);
			//DWRITE->PosRenderText(to_wstring((int)CurHp), Pos, (Scale.x * 7));
			Vector2 Pos;
			Pos.x = img_Level->GetWorldPos().x + app.GetHalfWidth() + Scale.x * 4;
			Pos.y = app.GetHalfHeight() - img_Level->GetWorldPivot().y;
			DWRITE->PosRenderText(L"Lv", Pos, (Scale.x * 5));

			Pos.x += Scale.x * 8;
			Pos.y += -Scale.x * 3;
			DWRITE->PosRenderText(to_wstring((int)Level), Pos, (Scale.x * 9));

			Pos.x = img_ATK->GetWorldPos().x + app.GetHalfWidth() + Scale.x * 9;
			Pos.y = app.GetHalfHeight() - img_ATK->GetWorldPivot().y - Scale.x * 5;
			DWRITE->PosRenderText(L"Atk", Pos, (Scale.x * 4));

			Pos.x = img_ATK->GetWorldPos().x + app.GetHalfWidth() + Scale.x * 17 - ((to_string((int)Atk).size() * (2) * Scale.x));
			Pos.y = app.GetHalfHeight() - img_ATK->GetWorldPivot().y - Scale.y / 2;
			DWRITE->PosRenderText(to_wstring((int)Atk), Pos, (Scale.x * 5));

			Pos.x = img_DEF->GetWorldPos().x + app.GetHalfWidth() + Scale.x * 9;
			Pos.y = app.GetHalfHeight() - img_DEF->GetWorldPivot().y - Scale.x * 5;
			DWRITE->PosRenderText(L"Def", Pos, (Scale.x * 4));

			Pos.x = img_DEF->GetWorldPos().x + app.GetHalfWidth() + Scale.x * 17 - ((to_string((int)Def).size() * (2) * Scale.x));
			Pos.y = app.GetHalfHeight() - img_DEF->GetWorldPivot().y - Scale.y / 2;
			DWRITE->PosRenderText(to_wstring((int)Def), Pos, (Scale.x * 5));

		}

	};

	//	struct GamePlayerElementUI{
	//	ChangeAttributeUI
	//	AttributeOption1
	//	AttributeOption2
	//	AttributeOption3
	//	AttributeOption4
	//	AttributeOption5
	//	AttributeOption6
	//
	//	AttackAttributeUI
	//	AttackAttributeIcon
	//	AttackAttributeName
	//	AttackAttributeValue
	//}
	struct UI {
		struct Button {
			ObImage* img;
			ObImage* img2;
			ObImage* icon;
			ObRect* col;
			wstring wstr;

			bool OnMouse = false;
			bool isFadingInOut = true;


			void Update() {
				img->Update();
				img2->Update();
				col->Update();
				if (icon != nullptr)
					icon->Update();
			}
			void LateUpdate(int& status, int& state) {
				Vector2 ScreenPos = INPUT->GetScreenMousePos();
				ScreenPos -= Vector2(app.GetHalfWidth(), app.GetHalfHeight());
				ScreenPos.y = -ScreenPos.y;
				if (col->Intersect(ScreenPos)) {
					OnMouse = true;
					Fading();
					if (INPUT->KeyDown(VK_LBUTTON) && status > 0) {
						SOUND->Stop("Enter");
						SOUND->Play("Enter");
						status--;
						state++;

					}
				}
				else {
					img2->color.w = 0;
					OnMouse = false;
				}
			}
			void Fading() {
				if (isFadingInOut) {
					img2->color.w -= DELTA;
					if (img2->color.w < 0.0) isFadingInOut = false;
				}
				else {
					img2->color.w += DELTA;
					if (img2->color.w > 0.5) isFadingInOut = true;
				}
			}
			void Render(Camera* cam) {
				if (DEBUGMODE);
					col->Render(cam);
				img->Render(cam);
				img2->Render(cam);
				if (icon != nullptr) {
					icon->Render(cam);

					Vector2 Pos;
					Pos.x = icon->GetWorldPos().x + app.GetHalfWidth() - 15;
					Pos.y = app.GetHalfHeight() - icon->GetWorldPivot().y - 50;
					DWRITE->PosRenderText(wstr, Pos, 30);
				}
			}
		};

		Button* B;
		ObImage* UI;
		ObRect* UIcol;
		Button* UI_B[ButtonCount];

		bool isPopUp;

		void Update() {
			B->Update();

			if (isPopUp) {
				UIcol->Update();
				UI->Update();
				for (int i = 0; i < ButtonCount; i++) {
					UI_B[i]->Update();
				}
			}
			Vector2 ScreenPos = INPUT->GetScreenMousePos();
			ScreenPos -= Vector2(app.GetHalfWidth(), app.GetHalfHeight());
			ScreenPos.y = -ScreenPos.y;

			if (B->col->Intersect(ScreenPos)) {
				//cout << "충돌 1 " << endl;
				isPopUp = true;
			}
			else if (UIcol->Intersect(ScreenPos) && isPopUp) {
				//cout << "충돌 팝업 1 " << endl;
				isPopUp = true;
			}
			else {
				isPopUp = false;
			}
		};
		void Render(Camera* cam) {
			B->Render(cam);

			if (isPopUp) {
				UI->Render(cam);
				if (DEBUGMODE);
					UIcol->Render(cam);
				for (int i = 0; i < ButtonCount; i++) {
					UI_B[i]->Render(cam);
				}

			}
		};
		void stateRender(int state) {
			Vector2 Pos;
			Pos.x = UIcol->GetWorldPos().x + app.GetHalfWidth() - UI->imageSize.x / 2 + 80;
			Pos.y = app.GetHalfHeight() - UIcol->GetWorldPivot().y - UI->imageSize.y / 2 + 10;
			DWRITE->PosRenderText(L"StatusPoint", Pos, 20);

			Pos.x = UIcol->GetWorldPos().x + app.GetHalfWidth() + UI->imageSize.x / 2 - 35 - (to_wstring(state).size() * 15);
			Pos.y = app.GetHalfHeight() - UIcol->GetWorldPivot().y - UI->imageSize.y / 2 + 20;
			DWRITE->PosRenderText(to_wstring(state), Pos, 30);
		}




	};
	UI* Upgradebtn;

	struct GameLevelUI {
		//LevelUpUI
		//LevelUpText
		//NewAbilityUnlockedText
		//AbilityUpgradeUI
		//UpgradeButton

		ObImage* UI1;
		ObImage* UI2;
		ObImage* UI3;
		ObRect* Line;

		void SetColorFadeIn(float C) {
			if (UI1->color.w <= 0.5) {
				UI1->color.w += C;
				UI2->color.w += C;
				UI3->color.w += C;
				Line->color.w += C;
			}
		}
		void SetColorFadeOut(float C) {
			UI1->color.w -= C;
			UI2->color.w -= C;
			UI3->color.w -= C;
			Line->color.w -= C;
		}

		void Update()
		{
			UI1->Update();
			UI2->Update();
			UI3->Update();
			Line->Update();
		}
		void Render()
		{
			UI1->Render();
			UI2->Render();
			UI3->Render();
			Line->Render();
		}
		void Render(Camera* cam)
		{
			Line->Render(cam);
			UI1->Render(cam);
			UI2->Render(cam);
			UI3->Render(cam);
		}
	};
	GameLevelUI* LevelUp;
	GamePlayUI* status;
	unique_ptr<GameObject> LeftTopBar;


	ObImage* Element_Change_UI;
	ObImage* Element_Change_UI_img1;
	ObImage* Element_Change_UI_img2;
	ObImage* Element_Change_UI_img3;
	ObImage* Element_Change_UI_img4;
	ObImage* Element_Change_UI_img5;
	Vector2 OffSet_Pos;





public:
	int Element_idx;
	float LevelScaleY;




	Vector2 Scale;
	Vector2 Pos;
	float size;

	float CurHp;
	float MaxHp;

	float CurExp;
	float MaxExp;

	int Level;
	int Atk;
	int Def;
	int state;

	int bonus_Atk;
	int bonus_Def;
	int bonus_AS;
	int bonus_Hp;
	int bonus_Range;
	int bonus_Healing;

	float hitCooltime;

	float Timer;
	bool Event;

	PlayerUI();
	~PlayerUI();

	void Init(Vector2 scale);
	void Update();
	void Render();
	void Render(class Camera* cam);

	void SetScale(Vector2 scale) { this->Scale = scale; };

	void LevelUp_Event();

	//void SetPos(Vector2 pos) { hp_ui->SetWorldPos(pos); };


	bool isAlive()
	{
		return CurHp > 0;
	}
	void Damage(int damage, Vector2 Pos, int color) {
		if (hitCooltime <= 0.0f)
		{
			CurHp -= damage;
			DAMAGE->AddText(Pos, damage, color);
			hitCooltime = 0.5f;
		}
	}


};
