#include "stdafx.h"
#include "Scene2.h"
#include "Scene3.h"


bool DEBUGMODE;

Scene3::Scene3()
{
	DEBUGMODE = true;
}

Scene3::~Scene3() {
}

void Scene3::Init() {

	app.background = Color();

	Opening_1 = make_unique<ObImage>(L"Opening/Opening_1.png");
	Opening_2 = make_unique<ObImage>(L"Opening/Opening_2_2.png");
	Opening_3 = make_unique<ObImage>(L"Opening/Opening_2_2.png");
	Opening_4 = make_unique<ObImage>(L"Opening/Opening_3.png");
	Opening_5 = make_unique<ObImage>(L"Opening/Opening_4.png");
	Opening_6 = make_unique<ObImage>(L"Opening/Opening_5.png");

	Opening_img_1 = make_unique<ObImage>(L"Opening/background_1.png");
	Opening_img_2 = make_unique<ObImage>(L"Opening/background_2.png");

	Opening_img_1->scale.x = app.GetWidth();
	Opening_img_1->scale.y = app.GetHeight() + 400;
	Opening_img_1->SetWorldPosY(-100);

	Opening_img_2->maxFrame.x = 6;
	Opening_img_2->scale.x = Opening_img_2->imageSize.x / Opening_img_2->maxFrame.x * 3;
	Opening_img_2->scale.y = Opening_img_2->imageSize.y * 3;
	Opening_img_2->ChangeAnim(ANIMSTATE::LOOP, 0.2f);

	Opening_img_2->SetWorldPosX(app.GetHalfWidth() - Opening_img_2->imageSize.x / 4);
	Opening_img_2->SetWorldPosY(-app.GetHalfHeight());

	Opening_img_1->color.w = 0.0f;
	Opening_img_2->color.w = 0.0f;

	Opening_1->scale.x = app.GetWidth();
	Opening_1->scale.y;

	Opening_2->SetWorldPosX(-100);
	Opening_3->SetWorldPosX(100);

	Opening_5->scale.x = Opening_5->imageSize.x * 2.5;
	Opening_5->scale.y = Opening_5->imageSize.y * 2.5;
	Opening_6->scale.x = Opening_6->imageSize.x * 2.5;
	Opening_6->scale.y = Opening_6->imageSize.y * 2.5;

	button_1 = new Button;
	button_1->col = new ObRect();
	button_1->button = new ObImage(L"Opening/button_1.png");;
	button_1->OnButton = new ObImage(L"Opening/button_2.png");;

	ImageUtils::setScale(button_1->col, Vector2(button_1->button->imageSize.x, button_1->button->imageSize.y) * 3);
	ImageUtils::setScale(button_1->button, Vector2(3));
	ImageUtils::setScale(button_1->OnButton, Vector2(3));
	ImageUtils::setPT(button_1->button, button_1->col);
	ImageUtils::setPT(button_1->OnButton, button_1->col);
	button_1->wstr = L"시작하기";

	button_2 = new Button;
	button_2->col = new ObRect();
	button_2->button = new ObImage(L"Opening/button_1.png");;
	button_2->OnButton = new ObImage(L"Opening/button_2.png");;
	ImageUtils::setScale(button_2->col, Vector2(button_2->button->imageSize.x, button_2->button->imageSize.y) * 3);
	ImageUtils::setScale(button_2->button, Vector2(3));
	ImageUtils::setScale(button_2->OnButton, Vector2(3));
	ImageUtils::setPT(button_2->button, button_2->col);
	ImageUtils::setPT(button_2->OnButton, button_2->col);
	button_2->wstr = L"설정";

	button_3 = new Button;
	button_3->col = new ObRect();
	button_3->button = new ObImage(L"Opening/button_1.png");;
	button_3->OnButton = new ObImage(L"Opening/button_2.png");;
	ImageUtils::setScale(button_3->col, Vector2(button_3->button->imageSize.x, button_3->button->imageSize.y) * 3);
	ImageUtils::setScale(button_3->button, Vector2(3));
	ImageUtils::setScale(button_3->OnButton, Vector2(3));
	ImageUtils::setPT(button_3->button, button_3->col);
	ImageUtils::setPT(button_3->OnButton, button_3->col);
	button_3->wstr = L"종료";

	button_1->col->SetWorldPosX(-500);
	button_1->col->SetWorldPosY(-400);
	button_1->col->isFilled = false;

	button_2->col->SetWorldPosX(-500);
	button_2->col->SetWorldPosY(-500);
	button_2->col->isFilled = false;

	button_3->col->SetWorldPosX(-500);
	button_3->col->SetWorldPosY(-600);
	button_3->col->isFilled = false;

	animation_Event_1 = true;
	animation_Event_2 = false;
	animation_Event_3 = false;
	animation_Event_4 = false;
	animation_Event_5 = false;
	animation_Event_6 = false;
	animation_Event_7 = false;
	SceneChange = false;

	isExit = false;

	FadeOut = new ObImage(L"TileMap_2.png");
	ImageUtils::setScale(FadeOut, Vector2(100));
	FadeOut->color = Color(0, 0, 0, 0);

	SettingUI = new ObImage(L"Player_UI_6.png");
	
	SettingUI->scale.x = app.GetHalfWidth();
	SettingUI->scale.y = app.GetHeight();

	SettingUI->SetWorldPosX(app.GetWidth() + app.GetHalfWidth()/2);
	SettingUI->SetWorldPosY(-250);
	SettingUI->color.w = 0.35;
	SettingUI_PopUp = false;

	button_4 = new Button();
	button_4->col = new ObRect();
	button_4->button = new ObImage(L"Opening/button_1.png");;
	button_4->OnButton = new ObImage(L"Opening/button_2.png");;
	ImageUtils::setScale(button_4->col, Vector2(button_4->button->imageSize.x, button_4->button->imageSize.y) * 3);
	ImageUtils::setScale(button_4->button, Vector2(3));
	ImageUtils::setScale(button_4->OnButton, Vector2(3));
	ImageUtils::setPT(button_4->button, button_4->col);
	ImageUtils::setPT(button_4->OnButton, button_4->col);
	ImageUtils::setPT(button_4->col, SettingUI);
	button_4->wstr = L"DEBUG_MODE";
	button_4->OnMouse = false;
	button_4->col->SetLocalPosX(0);
	button_4->col->SetLocalPosY(app.GetHalfHeight()/2);
	button_4->col->isFilled = false;

}

void Scene3::Release() {
}

void Scene3::Update() {


	if (animation_Event_1) {
		Animation_Scale1 += DELTA * 500;
		Opening_1->scale.y = min(Opening_1->imageSize.y * 5, Animation_Scale1);
		Opening_1->scale.y = min(Opening_1->imageSize.y * 5, Animation_Scale1);
		if (Opening_1->imageSize.y * 4 < Animation_Scale1) {
			animation_Event_1 = false;
			animation_Event_2 = true;
		}
	}
	if (animation_Event_2) {
		Animation_Scale2 += DELTA * 900;
		Opening_2->scale.x = min(Opening_2->imageSize.x * 4, Animation_Scale2);
		Opening_2->scale.y = min(Opening_2->imageSize.y * 4, Animation_Scale2);
		Opening_3->scale.x = min(Opening_3->imageSize.x * 4, Animation_Scale2);
		Opening_3->scale.y = min(Opening_3->imageSize.y * 4, Animation_Scale2);
		if (Opening_3->imageSize.y * 3 < Animation_Scale2) {
			animation_Event_2 = false;
			animation_Event_3 = true;
		}
	}

	if (animation_Event_3) {
		Opening_2->SetWorldPos(Vector2::Lerp(Opening_2->GetWorldPos(), Vector2(), 0.08f));
		Opening_2->SetWorldPos(Vector2::Lerp(Opening_2->GetWorldPos(), Vector2(), 0.08f));
		Opening_3->SetWorldPos(Vector2::Lerp(Opening_3->GetWorldPos(), Vector2(), 0.08f));
		Opening_3->SetWorldPos(Vector2::Lerp(Opening_3->GetWorldPos(), Vector2(), 0.08f));
		if (Opening_3->GetWorldPos().x <= 0.9f) {
			animation_Event_3 = false;
			animation_Event_4 = true;
		}
	}


	if (animation_Event_4) {
		Animation_Scale3 += DELTA * 900;
		Opening_4->scale.x = min(Opening_4->imageSize.x * 5.5, Animation_Scale3);
		Opening_4->scale.y = min(Opening_4->imageSize.y * 5.5, Animation_Scale3);
		if (Opening_4->imageSize.y * 4.5 < Animation_Scale3) {
			animation_Event_4 = false;
			animation_Event_5 = true;
			animation_Event_6 = true;
			Opening_2->SetWorldPos(Vector2());
			Opening_3->SetWorldPos(Vector2());
		}
	}


	if (animation_Event_5) {
		Animation_Scale1 -= DELTA * 500;
		Animation_Scale2 -= DELTA * 900;
		Opening_2->scale.x = min(Opening_2->imageSize.x * 3, Animation_Scale2);
		Opening_2->scale.y = min(Opening_2->imageSize.x * 3, Animation_Scale2);
		Opening_3->scale.x = min(Opening_3->imageSize.x * 3, Animation_Scale2);
		Opening_3->scale.y = min(Opening_3->imageSize.x * 3, Animation_Scale2);
		Opening_1->scale.y = min(Opening_1->imageSize.y * 4, Animation_Scale1);

		Opening_2->color.w -= DELTA * 2;
		Opening_3->color.w -= DELTA * 2;
		Opening_1->color.w -= DELTA * 2;

		if (Animation_Scale1 < 0) Animation_Scale1 = 0;

		if (Opening_3->imageSize.y * 3 < Animation_Scale2) {
			animation_Event_5 = false;
		}
	}

	if (animation_Event_6) {
		Animation_Scale3 += DELTA * 900;
		Opening_4->scale.x = min(Opening_4->imageSize.x * 8, Animation_Scale3);
		Opening_4->scale.y = min(Opening_4->imageSize.y * 8, Animation_Scale3);
		Opening_4->color.w -= DELTA;
		if (Opening_4->color.w <= 0.5f) {
			animation_Event_7 = true;
		}
	}
	if (animation_Event_7) {
		CAM->position.y = Vector2::Lerp(CAM->position, Vector2(0, -250), 0.15f).y;
		Opening_6->color.w -= DELTA;
		if (Opening_img_1->color.w <= 0.5f) {
			Opening_img_1->color.w += DELTA;
			Opening_img_2->color.w += DELTA;
		}
		SOUND->Play("Title");
		if (SettingUI_PopUp) {
			SettingUI->SetWorldPos(Vector2::Lerp(SettingUI->GetWorldPos(), Vector2(app.GetHalfWidth() / 2, -250), 0.1f));
		}
		else {
			SettingUI->SetWorldPos(Vector2::Lerp(SettingUI->GetWorldPos(), Vector2(app.GetHalfWidth() + app.GetHalfWidth() / 2, -250), 0.1f));
		}
	}
	if (!SceneChange) {
		// 객체와 UI 요소 업데이트
		Opening_1->Update();
		Opening_2->Update();
		Opening_3->Update();
		Opening_4->Update();
		Opening_5->Update();
		Opening_6->Update();
		Opening_img_1->Update();
		Opening_img_2->Update();
		button_1->Update();
		button_2->Update();
		button_3->Update();
	}

	if (isExit) {
		if (SOUND->isPlay("Exit")) {
			ExitProcess(0);
		}
		else {
			FadeOut->color.w += DELTA / 8;
			button_1->color.w -= DELTA / 4;
			button_2->color.w -= DELTA / 4;
			button_3->color.w -= DELTA / 4;
			SOUND->Stop("Title");
		}
	}

	

	button_4->Update2();
	SettingUI->Update();
	FadeOut->Update();
}
void Scene3::LateUpdate() {

	if (button_1->col->Intersect(INPUT->GetWorldMousePos())) {
		if (INPUT->KeyDown(VK_LBUTTON)) {
			SOUND->Stop("Enter");
			SOUND->Play("Enter");

			SOUND->Stop("Title");

			CAM->position = Vector2();
			Scene2* sc2 = new Scene2();
			SCENE->AddScene("SC2", sc2);
			SCENE->ChangeScene("SC2");
		}
	}

	if (button_2->col->Intersect(INPUT->GetWorldMousePos())) {
		if (INPUT->KeyDown(VK_LBUTTON)) {
			SOUND->Stop("Enter");
			SOUND->Play("Enter");
			SOUND->Stop("MenuOpen");
			SOUND->Play("MenuOpen");

			SettingUI_PopUp = !SettingUI_PopUp;
		}
	}

	if (button_3->col->Intersect(INPUT->GetWorldMousePos())) {
		if (INPUT->KeyDown(VK_LBUTTON)) {
			SOUND->Stop("Enter");
			SOUND->Play("Enter");

			SOUND->Play("Exit");
			isExit = true;
		}
	}
	if (button_4->col->Intersect(INPUT->GetWorldMousePos())) {
		if (INPUT->KeyDown(VK_LBUTTON)) {
			SOUND->Stop("Enter");
			SOUND->Play("Enter");

			button_4->OnMouse = !button_4->OnMouse;
			DEBUGMODE = !DEBUGMODE;
		}
	}


}
void Scene3::Render() {
	if (!SceneChange) {
		// 객체, 이미지 및 UI 요소 렌더링
		Opening_img_1->Render();
		Opening_img_2->Render();

		if (Opening_img_2->color.w > 0.5f) {
			button_1->Render();
			button_2->Render();
			button_3->Render();
		}

		Opening_1->Render();

		if (animation_Event_6) {
			Opening_6->Render();
			Opening_5->Render();
		}

		Opening_4->Render();

		if (Animation_Scale2 > Opening_1->imageSize.y) {
			Opening_2->Render();
			Opening_3->Render();
		}
	}

	SettingUI->Render();
	button_4->Render();
	FadeOut->Render();
}

void Scene3::ResizeScreen()
{
	Opening_img_1->scale.x = app.GetWidth();
	Opening_img_1->scale.y = app.GetHeight() + 400;

	Opening_img_2->SetWorldPosX(app.GetHalfWidth() - Opening_img_2->imageSize.x / 4);
	Opening_img_2->SetWorldPosY(-app.GetHalfHeight());

	CAM->ResizeScreen();
}


