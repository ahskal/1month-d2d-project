#include "stdafx.h"
#include "Player.h"
#include "PlayerUI.h"

extern bool DEBUGMODE;

PlayerUI::PlayerUI()
{
	{
		//================================================================================================

		Element = new ElementUI();

		Element->UI = new ObImage(L"Player_UI_2.png");
		ImageUtils::set(Element->UI);

		Element->Type = new ObImage(L"Player_UI_Element_5.png");
		ImageUtils::set(Element->Type, Int2(5, 1));

		ImageUtils::setPT(Element->Type, Element->UI);

		//================================================================================================

		Hp = new GameHpUI();

		Hp->UI = new ObImage(L"Player_UI_1.png");
		ImageUtils::set(Hp->UI);

		Hp->HpBar1 = new ObImage(L"WhiteBar_1.png");
		ImageUtils::set(Hp->HpBar1, Int2(), OFFSET_L);

		Hp->HpBar2 = new ObImage(L"WhiteBar_1.png");
		ImageUtils::set(Hp->HpBar2, Int2(), OFFSET_L);

		Hp->HpBar3 = new ObImage(L"WhiteBar_1.png");
		ImageUtils::set(Hp->HpBar3, Int2(), OFFSET_L);

		Hp->ExpBar = new ObImage(L"WhiteBar_1.png");
		ImageUtils::set(Hp->ExpBar, Int2(), OFFSET_L);
		Hp->ExpBar->color = Color(
			221 / 255.f * 0.5f,
			153 / 255.f * 0.5f,
			255 / 255.f * 0.5f, 1);

		ImageUtils::setPT(Hp->UI, Element->UI);
		ImageUtils::setPT(Hp->HpBar1, Hp->UI);
		ImageUtils::setPT(Hp->HpBar2, Hp->UI);
		ImageUtils::setPT(Hp->HpBar3, Hp->UI);
		ImageUtils::setPT(Hp->ExpBar, Hp->UI);

		//================================================================================================
		status = new GamePlayUI();

		status->img_ATK = new ObImage(L"Player_UI_5.png");
		status->img_DEF = new ObImage(L"Player_UI_5.png");
		status->img_Level = new ObImage(L"Player_UI_5.png");

		ImageUtils::set(status->img_Level, Int2(), OFFSET_L);
		ImageUtils::set(status->img_ATK, Int2(), OFFSET_L);
		ImageUtils::set(status->img_DEF, Int2(), OFFSET_L);

		ImageUtils::setPT(status->img_Level, Hp->UI);
		ImageUtils::setPT(status->img_ATK, status->img_Level);
		ImageUtils::setPT(status->img_DEF, status->img_ATK);

		//================================================================================================

		ExpUI = new GameEXPUI();

		ExpUI->ExperienceGain_img1 = new ObImage(L"Exp_1.png");
		ImageUtils::set(ExpUI->ExperienceGain_img1, Int2(), OFFSET_L);
		ExpUI->ExperienceGain_img2 = new ObImage(L"Exp_3.png");
		ImageUtils::set(ExpUI->ExperienceGain_img2, Int2(), OFFSET_L);
		ExpUI->ExperienceGain_img3 = new ObImage(L"Exp_4.png");
		ImageUtils::set(ExpUI->ExperienceGain_img3, Int2(), OFFSET_L);

		ImageUtils::setPT(ExpUI->ExperienceGain_img1, Hp->UI);
		ImageUtils::setPT(ExpUI->ExperienceGain_img2, ExpUI->ExperienceGain_img1);
		ImageUtils::setPT(ExpUI->ExperienceGain_img3, ExpUI->ExperienceGain_img2);
		ExpUI->Exp = 0;

		//================================================================================================

		LevelUp = new GameLevelUI();

		LevelUp->UI1 = new ObImage(L"LevelUp_UI3.png");
		ImageUtils::set(LevelUp->UI1);
		LevelUp->UI2 = new ObImage(L"LevelUp_UI.png");
		ImageUtils::set(LevelUp->UI2);
		LevelUp->UI3 = new ObImage(L"LevelUp_UI2.png");
		ImageUtils::set(LevelUp->UI3);
		LevelUp->Line = new ObRect();
		LevelUp->Line->color = Color(0.0f, 0.0f, 0.0f, 0.5f);

		ImageUtils::setPT(LevelUp->UI2, LevelUp->UI1);
		ImageUtils::setPT(LevelUp->UI3, LevelUp->UI1);
		ImageUtils::setPT(LevelUp->Line, LevelUp->UI1);

		//================================================================================================
		// 
		// Element_Change_UI
		Element_Change_UI = new ObImage(L"Player_UI_3.png");
		Element_Change_UI_img1 = new ObImage(L"Player_UI_4.png");
		Element_Change_UI_img1->maxFrame = Int2(5, 1);
		Element_Change_UI_img1->frame.x = 2;

		Element_Change_UI_img2 = new ObImage(L"Player_UI_4.png");
		Element_Change_UI_img2->maxFrame = Int2(5, 1);
		Element_Change_UI_img2->frame.x = 1;

		Element_Change_UI_img3 = new ObImage(L"Player_UI_4.png");
		Element_Change_UI_img3->maxFrame = Int2(5, 1);
		Element_Change_UI_img3->frame.x = 0;

		Element_Change_UI_img4 = new ObImage(L"Player_UI_4.png");
		Element_Change_UI_img4->maxFrame = Int2(5, 1);
		Element_Change_UI_img4->frame.x = 3;

		Element_Change_UI_img5 = new ObImage(L"Player_UI_4.png");
		Element_Change_UI_img5->maxFrame = Int2(5, 1);
		Element_Change_UI_img5->frame.x = 4;

		Element_Change_UI_img1->SetParentRT(*Element_Change_UI);
		Element_Change_UI_img2->SetParentRT(*Element_Change_UI);
		Element_Change_UI_img3->SetParentRT(*Element_Change_UI);
		Element_Change_UI_img4->SetParentRT(*Element_Change_UI);
		Element_Change_UI_img5->SetParentRT(*Element_Change_UI);

		//================================================================================================
		Upgradebtn = new UI();
		Upgradebtn->B = new UI::Button();
		for (int i = 0; i < ButtonCount; i++) {
			Upgradebtn->UI_B[i] = new UI::Button();
		}

		Upgradebtn->B->img = new ObImage(L"Player_UI_7.png");
		Upgradebtn->B->img2 = new ObImage(L"Player_UI_8.png");
		Upgradebtn->B->col = new ObRect();
		Upgradebtn->B->col->isFilled = false;

		Upgradebtn->B->col->SetLocalPosY(-150);
		ImageUtils::setPT(Upgradebtn->B->img, Upgradebtn->B->col);
		ImageUtils::setPT(Upgradebtn->B->img2, Upgradebtn->B->col);
		ImageUtils::setPT(Upgradebtn->B->col, Element->UI);

		ImageUtils::setScale(Upgradebtn->B->col, Vector2(Upgradebtn->B->img->imageSize.x, Upgradebtn->B->img->imageSize.y) * 1.5);
		ImageUtils::setScale(Upgradebtn->B->img, Vector2(2));
		ImageUtils::setScale(Upgradebtn->B->img2, Vector2(2));
		Upgradebtn->B->img2->color.w = 0;

		Upgradebtn->UI = new ObImage(L"Player_UI_6.png");
		Upgradebtn->UIcol = new ObRect();
		Upgradebtn->UIcol->isFilled = false;

		ImageUtils::setScale(Upgradebtn->UIcol, Vector2(Upgradebtn->UI->imageSize.x, Upgradebtn->UI->imageSize.y));
		ImageUtils::setScale(Upgradebtn->UI, Vector2(1));

		ImageUtils::setPT(Upgradebtn->UI, Upgradebtn->UIcol);
		ImageUtils::setPT(Upgradebtn->UIcol, Upgradebtn->B->col);

		Upgradebtn->UIcol->SetLocalPosX(Upgradebtn->UI->imageSize.x / 2);
		Upgradebtn->UIcol->SetLocalPosY(-Upgradebtn->UI->imageSize.y / 3);

		Upgradebtn->UI_B[0]->icon = new ObImage(L"Player_UI_2.png");
		Upgradebtn->UI_B[1]->icon = new ObImage(L"Player_UI_2.png");
		Upgradebtn->UI_B[2]->icon = new ObImage(L"Player_UI_2.png");
		Upgradebtn->UI_B[3]->icon = new ObImage(L"Player_UI_2.png");
		Upgradebtn->UI_B[4]->icon = new ObImage(L"Player_UI_2.png");
		Upgradebtn->UI_B[5]->icon = new ObImage(L"Player_UI_2.png");
		for (int i = 0; i < ButtonCount; i++) {
			Upgradebtn->UI_B[i]->img = new ObImage(L"Player_UI_7.png");
			Upgradebtn->UI_B[i]->img2 = new ObImage(L"Player_UI_8.png");
			Upgradebtn->UI_B[i]->col = new ObRect();
			Upgradebtn->UI_B[i]->col->isFilled = false;

			ImageUtils::setPT(Upgradebtn->UI_B[i]->img, Upgradebtn->UI_B[i]->col);
			ImageUtils::setPT(Upgradebtn->UI_B[i]->img2, Upgradebtn->UI_B[i]->col);
			ImageUtils::setPT(Upgradebtn->UI_B[i]->col, Upgradebtn->UI_B[i]->icon);
			ImageUtils::setPT(Upgradebtn->UI_B[i]->icon, Upgradebtn->UIcol);

			Upgradebtn->UI_B[i]->col->scale.x = Upgradebtn->UI_B[i]->img->imageSize.x;
			Upgradebtn->UI_B[i]->col->scale.y = Upgradebtn->UI_B[i]->img->imageSize.y;
			Upgradebtn->UI_B[i]->img->scale.x = Upgradebtn->UI_B[i]->img->imageSize.x;
			Upgradebtn->UI_B[i]->img->scale.y = Upgradebtn->UI_B[i]->img->imageSize.y;
			Upgradebtn->UI_B[i]->img2->scale.x = Upgradebtn->UI_B[i]->img2->imageSize.x;
			Upgradebtn->UI_B[i]->img2->scale.y = Upgradebtn->UI_B[i]->img2->imageSize.y;
			Upgradebtn->UI_B[i]->icon->scale.x = Upgradebtn->UI_B[i]->icon->imageSize.x;
			Upgradebtn->UI_B[i]->icon->scale.y = Upgradebtn->UI_B[i]->icon->imageSize.y;

			Upgradebtn->UI_B[i]->icon->SetLocalPosX(-75);
			Upgradebtn->UI_B[i]->icon->SetLocalPosY(170 - i * 65);
			Upgradebtn->UI_B[i]->col->SetLocalPosX(200);
		}
		Upgradebtn->UI_B[0]->wstr = L"Attack Power";
		Upgradebtn->UI_B[1]->wstr = L"Attack Speed";
		Upgradebtn->UI_B[2]->wstr = L"Attack Range";
		Upgradebtn->UI_B[3]->wstr = L"Defence Power";
		Upgradebtn->UI_B[4]->wstr = L"Extra Health";	
		Upgradebtn->UI_B[5]->wstr = L"Healing Amount";
	}

	Scale = Vector2();
	MaxHp = CurHp = 1;
	Level = 1;
	MaxExp = 50;
	CurExp = 0;
	Timer = 0;
	Event = false;
	Element_idx = 0;
	state = 5;
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::Init(Vector2 scale)
{
	this->Scale = scale;
	{

		ImageUtils::setScale(Element->UI, Scale);
		ImageUtils::setScale(Element->Type, Scale);

		Element->UI->SetWorldPosX(-app.GetHalfWidth() + Element->UI->scale.x / 2 + (Scale.x * 2));
		Element->UI->SetWorldPosY(app.GetHalfHeight() - Element->UI->scale.y / 2 - (Scale.y * 2));
		Element->Type->frame.x = Element_idx;

		ImageUtils::setScale(Hp->UI, scale);
		ImageUtils::setScale(Hp->HpBar1, scale);
		ImageUtils::setScale(Hp->HpBar2, scale);
		ImageUtils::setScale(Hp->HpBar3, scale);
		ImageUtils::setScale(Hp->ExpBar, scale);

		Hp->UI->SetLocalPosX(Hp->UI->scale.x / 2 + (Scale.x * 4) + Scale.x / 2);
		Hp->UI->SetLocalPosY(Hp->UI->scale.y / 2 + (Scale.y * 2) + Scale.y / 2);

		Hp->HpBar1->SetLocalPosX(-Hp->HpBar1->scale.x / 2 + Scale.x / 2 + Scale.x * 2);
		Hp->HpBar1->SetLocalPosY(-(Scale.y * 2));

		Hp->HpBar2->SetLocalPosX(-Hp->HpBar2->scale.x / 2 + Scale.x / 2 + Scale.x * 3);
		Hp->HpBar2->SetLocalPosY(-(Scale.y * 3));

		Hp->HpBar3->SetLocalPosX(-Hp->HpBar3->scale.x / 2 + Scale.x / 2 + Scale.x * 4);
		Hp->HpBar3->SetLocalPosY(-(Scale.y * 4));

		Hp->ExpBar->SetLocalPosX(-Hp->ExpBar->scale.x / 2 + Scale.x / 2 + Scale.x * 6);
		Hp->ExpBar->SetLocalPosY(-(Scale.y * 6));

		ImageUtils::setScale(ExpUI->ExperienceGain_img1, Scale);
		ImageUtils::setScale(ExpUI->ExperienceGain_img2, Scale);
		ImageUtils::setScale(ExpUI->ExperienceGain_img3, Scale);

		ExpUI->ExperienceGain_img1->SetLocalPosX(ExpUI->ExperienceGain_img1->scale.x - Scale.x * 5);
		ExpUI->ExperienceGain_img1->SetLocalPosY(-ExpUI->ExperienceGain_img1->scale.y / 2 - Scale.y + Scale.y / 2);

		ImageUtils::setScale(LevelUp->UI1, Scale);
		ImageUtils::setScale(LevelUp->UI2, Scale);
		ImageUtils::setScale(LevelUp->UI3, Scale);
		ImageUtils::setScale(LevelUp->Line, Vector2(0, Scale.y));

		LevelUp->UI1->SetLocalPosY(app.GetHalfHeight() / 2);

		LevelUp->UI2->SetLocalPosX(-13.0f * Scale.x);
		LevelUp->UI3->SetLocalPosX(+56.0f * Scale.x);

		// Element_UI
		Element_Change_UI->scale.x = Element_Change_UI->imageSize.x / Element_Change_UI->maxFrame.x * Scale.x;
		Element_Change_UI_img1->scale.x = Element_Change_UI_img1->imageSize.x / Element_Change_UI_img1->maxFrame.x * Scale.x;
		Element_Change_UI_img2->scale.x = Element_Change_UI_img2->imageSize.x / Element_Change_UI_img2->maxFrame.x * Scale.x;
		Element_Change_UI_img3->scale.x = Element_Change_UI_img3->imageSize.x / Element_Change_UI_img3->maxFrame.x * Scale.x;
		Element_Change_UI_img4->scale.x = Element_Change_UI_img4->imageSize.x / Element_Change_UI_img4->maxFrame.x * Scale.x;
		Element_Change_UI_img5->scale.x = Element_Change_UI_img5->imageSize.x / Element_Change_UI_img5->maxFrame.x * Scale.x;

		Element_Change_UI->scale.y = Element_Change_UI->imageSize.y * Scale.y;
		Element_Change_UI_img1->scale.y = Element_Change_UI_img1->imageSize.y * Scale.y;
		Element_Change_UI_img2->scale.y = Element_Change_UI_img2->imageSize.y * Scale.y;
		Element_Change_UI_img3->scale.y = Element_Change_UI_img3->imageSize.y * Scale.y;
		Element_Change_UI_img4->scale.y = Element_Change_UI_img4->imageSize.y * Scale.y;
		Element_Change_UI_img5->scale.y = Element_Change_UI_img5->imageSize.y * Scale.y;

		OffSet_Pos.x = 22 * Scale.x;
		OffSet_Pos.y = 22 * Scale.y;

		Element_Change_UI_img2->SetLocalPosX(-OffSet_Pos.x); // 왼쪽
		Element_Change_UI_img4->SetLocalPosX(OffSet_Pos.x); // 오른쪽
		Element_Change_UI_img1->SetLocalPosY(OffSet_Pos.y); // 위
		Element_Change_UI_img3->SetLocalPosY(-OffSet_Pos.y); // 아래

		// status


		ImageUtils::setScale(status->img_ATK, Scale);
		ImageUtils::setScale(status->img_DEF, Scale);
		ImageUtils::setScale(status->img_Level, Scale);

		status->Scale = Scale;
		status->img_Level->SetLocalPosX(-status->img_Level->scale.x + Scale.x);
		status->img_Level->SetLocalPosY(-status->img_Level->scale.y * 2 + (Scale.y * 2) + Scale.y / 2);
		status->img_ATK->SetLocalPosX(status->img_ATK->scale.x - Scale.x * 6);
		status->img_DEF->SetLocalPosX(status->img_DEF->scale.x - Scale.x * 6);
	}


	//status->img_ATK->SetLocalPosY(-status->img_ATK->scale.y /2 + (Scale.y * 2) + Scale.y / 2);
	//status->img_ATK->SetLocalPosY(-status->img_ATK->scale.y * Scale.y);

}

void PlayerUI::Update()
{
	if (INPUT->KeyPress(VK_TAB)) {
		float dir = (Utility::DirToRadian(INPUT->GetWorldMousePos() - CAM->position) + PI) / HALFPI;
		if ((CAM->position - INPUT->GetWorldMousePos()).Length() < Element_Change_UI_img5->scale.x) {
			Element_idx = 0;
			Element_Change_UI_img5->color = Color(0.6, 0.6, 0.6, 0.5);

			Element_Change_UI_img2->SetLocalPosX(-OffSet_Pos.x); // 왼쪽
			Element_Change_UI_img4->SetLocalPosX(OffSet_Pos.x); // 오른쪽
			Element_Change_UI_img1->SetLocalPosY(OffSet_Pos.y); // 위
			Element_Change_UI_img3->SetLocalPosY(-OffSet_Pos.y); // 아래
		}
		else if (dir) {
			// ================================================================  6시방향
			if (dir >= 0.5 && dir < 1.5f) {
				Element_idx = 2;
				// 시작 값
				Vector2 startY = Element_Change_UI_img3->GetLocalPos();
				// 끝 값
				Vector2 endY = Vector2(0, -35 * Scale.y);
				Vector2 a = Vector2::Lerp(startY, endY, DELTA * 3.5);
				Element_Change_UI_img3->SetLocalPos(a);
				Element_Change_UI_img2->SetLocalPosX(-OffSet_Pos.x); // 왼쪽
				Element_Change_UI_img4->SetLocalPosX(OffSet_Pos.x); // 오른쪽
				Element_Change_UI_img1->SetLocalPosY(OffSet_Pos.y); // 위
				Element_Change_UI_img5->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
			}
			// ================================================================  3시방향
			else if (dir >= 1.5 && dir < 2.5f) {
				Element_idx = 4;
				// 시작 값
				Vector2 startY = Element_Change_UI_img4->GetLocalPos();
				// 끝 값
				Vector2 endY = Vector2(35 * Scale.x, 0);
				Vector2 a = Vector2::Lerp(startY, endY, DELTA * 3.5);
				Element_Change_UI_img4->SetLocalPos(a);

				Element_Change_UI_img2->SetLocalPosX(-OffSet_Pos.x); // 왼쪽
				Element_Change_UI_img1->SetLocalPosY(OffSet_Pos.y); // 위
				Element_Change_UI_img3->SetLocalPosY(-OffSet_Pos.y); // 아래
			}
			// ================================================================ 12시방향
			else if (dir >= 2.5f && dir < 3.5f) {
				Element_idx = 1;
				Vector2 startY = Element_Change_UI_img1->GetLocalPos();
				// 끝 값
				Vector2 endY = Vector2(0, 35 * Scale.y);
				Vector2 a = Vector2::Lerp(startY, endY, DELTA * 3.5);
				Element_Change_UI_img1->SetLocalPos(a);

				Element_Change_UI_img2->SetLocalPosX(-OffSet_Pos.x); // 왼쪽
				Element_Change_UI_img4->SetLocalPosX(OffSet_Pos.x); // 오른쪽
				Element_Change_UI_img3->SetLocalPosY(-OffSet_Pos.y); // 아래
				Element_Change_UI_img5->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
			}
			// ================================================================  9시방향
			else {
				Element_idx = 3;
				// 시작 값
				Vector2 startY = Element_Change_UI_img2->GetLocalPos();
				// 끝 값
				Vector2 endY = Vector2(-35 * Scale.x, 0);
				Vector2 a = Vector2::Lerp(startY, endY, DELTA * 3.5);
				Element_Change_UI_img2->SetLocalPos(a);

				Element_Change_UI_img4->SetLocalPosX(OffSet_Pos.x); // 오른쪽
				Element_Change_UI_img1->SetLocalPosY(OffSet_Pos.y); // 위
				Element_Change_UI_img3->SetLocalPosY(-OffSet_Pos.y); // 아래
				Element_Change_UI_img5->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
			}
		}
	}
	else {
		if (INPUT->KeyPress(VK_F5)) {
			state++;
		}
		if (INPUT->KeyPress(VK_F6)) {
			Event = true;
			CurExp += MaxExp * DELTA * 10;
		}
		if (INPUT->KeyDown(VK_F7)) {
			Event = false;
		}
	}

	Element->Type->frame.x = Element_idx;

	//스텟 업데이트
	MaxExp = 100 * Level;
	status->Level = Level;
	status->Atk = Atk;
	status->Def = Def;


	ImageUtils::setScale(ExpUI->ExperienceGain_img2, Scale * Vector2(to_string(ExpUI->Exp).size(), 1));
	ExpUI->ExperienceGain_img2->SetLocalPosX(ExpUI->ExperienceGain_img1->scale.x);
	ExpUI->ExperienceGain_img3->SetLocalPosX(ExpUI->ExperienceGain_img2->scale.x);

	// 현재 체력에 대한 전체 체력에 대한 비율 계산
	float hpRatio = static_cast<float>(CurHp) / static_cast<float>(MaxHp);
	float ExpRatio = static_cast<float>(CurExp) / static_cast<float>(MaxExp);

	// 이미지의 크기 조정 (전체 이미지 크기에 비례해서 남은 체력 부분만 보이도록)
	Hp->HpBar1->scale.x = Hp->HpBar1->imageSize.x * Scale.x * hpRatio;
	Hp->HpBar2->scale.x = Hp->HpBar2->imageSize.x * Scale.x * hpRatio;
	Hp->HpBar3->scale.x = Hp->HpBar3->imageSize.x * Scale.x * hpRatio;
	Hp->ExpBar->scale.x = Hp->ExpBar->imageSize.x * Scale.x * ExpRatio;

	// CurHp가 0 이하로 내려가지 않도록 보정
	if (CurHp < 0) CurHp = 0;
	// CurHp가 MaxHp를 넘지 않도록 보정
	if (CurHp > MaxHp) CurHp = MaxHp;
	// 이미지 업데이트

	if (hitCooltime > 0.0f)
	{
		hitCooltime -= DELTA;
	}

	if (CurExp >= MaxExp) {
		CurExp = 0;
		Level++;
		state++;
		Event = true;
	}
	if (Event) {
		LevelUp_Event();
	}
	else {
		//if (CAM->scale.x > 0.7f) {
		//	CAM->scale.x -= DELTA;
		//	CAM->scale.y -= DELTA;
		//}
		LevelScaleY = 0;
		LevelUp->Line->scale.x = 0;
	}
	ExpUI->Exp = MONSTER->giveExp;

	float ratio = CurHp / MaxHp;

	if (ratio < 0.2f) {
		Color color = Color(
			177 / 255.f * 0.5f,
			037 / 255.f * 0.5f,
			000 / 255.f * 0.5f, 1.0f);
		Hp->HpBar1->color = color;
		Hp->HpBar2->color = color;
		Hp->HpBar3->color = color;
	}
	else if (ratio < 0.6f) {
		Color color = Color(
			176 / 255.f * 0.5f,
			176 / 255.f * 0.5f,
			000 / 255.f * 0.5f, 1.0f);
		Hp->HpBar1->color = color;
		Hp->HpBar2->color = color;
		Hp->HpBar3->color = color;
	}
	else {
		Color color = Color(
			037 / 255.f * 0.5f,
			176 / 255.f * 0.5f,
			000 / 255.f * 0.5f, 1.0f);
		Hp->HpBar1->color = color;
		Hp->HpBar2->color = color;
		Hp->HpBar3->color = color;
	}

	Element->Update();
	Hp->Update();
	ExpUI->Update();
	LevelUp->Update();
	status->Update();

	Element_Change_UI->Update();
	Element_Change_UI_img1->Update();
	Element_Change_UI_img2->Update();
	Element_Change_UI_img3->Update();
	Element_Change_UI_img4->Update();
	Element_Change_UI_img5->Update();

	Upgradebtn->Update();
	if (state > 0 && !Upgradebtn->B->OnMouse) {
		Upgradebtn->B->Fading();
	}
	Upgradebtn->UI_B[0]->LateUpdate(state, bonus_Atk);
	Upgradebtn->UI_B[1]->LateUpdate(state, bonus_AS);
	Upgradebtn->UI_B[2]->LateUpdate(state, bonus_Range);
	Upgradebtn->UI_B[3]->LateUpdate(state, bonus_Def);
	Upgradebtn->UI_B[4]->LateUpdate(state, bonus_Hp);
	Upgradebtn->UI_B[5]->LateUpdate(state, bonus_Healing);
	




}

void PlayerUI::Render()
{
	Element->Render();
	Hp->Render();
	ExpUI->Render();
	LevelUp->Render();
	status->Render();

}

void PlayerUI::Render(class Camera* cam)
{
	Element->Render(cam);
	Hp->Render(cam);
	{
		Vector2 Pos;
		Pos.x = Hp->UI->GetWorldPivot().x + app.GetHalfWidth() + Scale.x * (15) - ((to_string((int)CurHp).size() * (6) * Scale.x));
		Pos.y = app.GetHalfHeight() - Hp->UI->GetWorldPivot().y - Scale.y * (8);
		DWRITE->PosRenderText(to_wstring((int)CurHp), Pos, (Scale.x * 7));
	}

	status->Render(cam);


	{
		if (ExpUI->Exp > 0) {
			ExpUI->Render(cam);
			Vector2 Pos;
			Pos.x = ExpUI->ExperienceGain_img1->GetWorldPivot().x + app.GetHalfWidth() + Scale.x * (18);
			Pos.y = app.GetHalfHeight() - ExpUI->ExperienceGain_img1->GetWorldPivot().y - Scale.y * (4);
			DWRITE->PosRenderText(to_wstring(ExpUI->Exp), Pos, (Scale.x * 7));
		}
	}
	{
		if (LevelScaleY > 0) {
			LevelUp->Render(cam);
		}
	}

	if (ExpUI->Exp > 0) {
		{
			Vector2 Pos;
			Pos.x = ExpUI->ExperienceGain_img1->GetWorldPivot().x + app.GetHalfWidth() + Scale.x * (18);
			Pos.y = app.GetHalfHeight() - ExpUI->ExperienceGain_img1->GetWorldPivot().y - Scale.y * (4);
			DWRITE->PosRenderText(to_wstring(ExpUI->Exp), Pos, (Scale.x * 7));
		}
	}
	if (INPUT->KeyPress(VK_TAB)) {

		Element_Change_UI->Render(cam);
		Element_Change_UI_img1->Render(cam);
		Element_Change_UI_img2->Render(cam);
		Element_Change_UI_img3->Render(cam);
		Element_Change_UI_img4->Render(cam);
		Element_Change_UI_img5->Render(cam);
	}

	Upgradebtn->Render(cam);
	if (Upgradebtn->isPopUp) {
		Upgradebtn->stateRender(state);
		
		int bonusState[ButtonCount];

		bonusState[0] = bonus_Atk;
		bonusState[1] = bonus_AS;
		bonusState[2] = bonus_Range;
		bonusState[3] = bonus_Def;
		bonusState[4] = bonus_Hp;
		bonusState[5] = bonus_Healing;

		for (int i = 0; i < ButtonCount; i++) {
			Vector2 pos;
			Pos.x = Upgradebtn->UI_B[i]->icon->GetWorldPos().x + app.GetHalfWidth() + Upgradebtn->UI_B[i]->icon->imageSize.x / 2 ;
			Pos.y = app.GetHalfHeight() - Upgradebtn->UI_B[i]->icon->GetWorldPivot().y - Upgradebtn->UI_B[i]->icon->imageSize.y / 2;
			DWRITE->PosRenderText(to_wstring(bonusState[i]), Pos, 30);
		}


	}



}

void PlayerUI::LevelUp_Event()
{
	SOUND->Play("LevelUp");
	float scrollSpeed = 5;

	scrollSpeed -= Timer;

	CurHp = MaxHp;

	if (Event) {


		// 카메라 스케일 조정
		//if (CAM->scale.x < 1.2f) {
		//	CAM->scale.x += DELTA;
		//	CAM->scale.y += DELTA;
		//}
		// Line 스케일 조정
		if (LevelUp->Line->scale.x < app.GetWidth()) {
			LevelUp->Line->scale.x += DELTA * Scale.x * 500;
		}
		// UI 스케일 조정
		LevelScaleY += DELTA * 250;
		LevelUp->UI1->scale.y = min(LevelUp->UI1->imageSize.y * Scale.y, LevelScaleY);
		LevelUp->UI2->scale.y = min(LevelUp->UI2->imageSize.y * Scale.y, LevelScaleY);
		LevelUp->UI3->scale.y = min(LevelUp->UI3->imageSize.y * Scale.y, LevelScaleY);
		// UV 스크롤
		if (Timer >= 2.0f) {
			LevelUp->SetColorFadeOut(DELTA);
		}
		else {
			LevelUp->SetColorFadeIn(DELTA * 2);
		}
		LevelUp->UI3->uv.y += DELTA * scrollSpeed * 2;
		LevelUp->UI3->uv.w += DELTA * scrollSpeed * 2;
	}
	// 이벤트 타이머 체크
	if (TIMER->GetTick(Timer, 3.f)) {
		LevelScaleY = 0;
		Event = false;
	}
}