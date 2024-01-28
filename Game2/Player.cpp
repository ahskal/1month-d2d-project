#include "stdafx.h"
#include "ProgressBar.h"
#include "PlayerUI.h"
#include "Player.h"

extern bool DEBUGMODE;

Player::Player()
{

	//================================================================================================
	// 기본 offset, 프레임1, 2 , 각도
	{
		Offset.y = 24;

		Frame[0] = 5;
		Frame[1] = 6;
		Frame[2] = 7;
		Frame[3] = 0;
		Frame[4] = 1;
		Frame[5] = 2;
		Frame[6] = 3;
		Frame[7] = 4;

		Frame2[0] = 6;
		Frame2[1] = 5;
		Frame2[2] = 4;
		Frame2[3] = 3;
		Frame2[4] = 2;
		Frame2[5] = 1;
		Frame2[6] = 0;
		Frame2[7] = 7;

		angle[6] = 45 * 0 * ToRadian;
		angle[7] = 45 * 1 * ToRadian;
		angle[0] = 45 * 2 * ToRadian;
		angle[1] = 45 * 3 * ToRadian;
		angle[2] = 45 * 4 * ToRadian;
		angle[3] = 45 * 5 * ToRadian;
		angle[4] = 45 * 6 * ToRadian;
		angle[5] = 45 * 7 * ToRadian;
	}

	//================================================================================================
	// 플레이어 기본 정보
	{
		player = new Unit();

		player->Idle = new ObImage(L"CrossCode_Idle.png");
		player->set(player->Idle, Int2(1, 8), IMAGESIZE, -Offset, OFFSET_B);
		player->setPT(player->Idle, this);

		player->Run = new ObImage(L"CrossCode_Run_Loop.png");
		player->set(player->Run, Int2(6, 8), IMAGESIZE, -Offset, OFFSET_B);
		player->setPT(player->Run, this);

		player->Run_E = new ObImage(L"CrossCode_Run_End.png");
		player->set(player->Run_E, Int2(3, 8), IMAGESIZE, -Offset, OFFSET_B);
		player->setPT(player->Run_E, this);

		player->Attack_Roll1 = new ObImage(L"CrossCode_Attack_Roll.png");
		player->set(player->Attack_Roll1, Int2(8, 4), IMAGESIZE, -Offset, OFFSET_B);
		player->setPT(player->Attack_Roll1, this);

		player->Attack_Roll2 = new ObImage(L"CrossCode_Attack_Roll2.png");
		player->set(player->Attack_Roll2, Int2(8, 4), IMAGESIZE, -Offset, OFFSET_B);
		player->setPT(player->Attack_Roll2, this);

		player->Short_Attack_Roll1 = new ObImage(L"CrossCode_ShortAttack_Roll.png");
		player->set(player->Short_Attack_Roll1, Int2(8, 5), IMAGESIZE, -Offset, OFFSET_B);
		player->setPT(player->Short_Attack_Roll1, this);

		player->Short_Attack_Roll2 = new ObImage(L"CrossCode_ShortAttack_Roll2.png");
		player->set(player->Short_Attack_Roll2, Int2(8, 5), IMAGESIZE, -Offset, OFFSET_B);
		player->setPT(player->Short_Attack_Roll2, this);

		player->Attack = new ObImage(L"CrossCode_Attack.png");
		player->set(player->Attack, Int2(8, 3), IMAGESIZE, -Offset, OFFSET_B);
		player->setPT(player->Attack, this);

		player->Dash = new ObImage(L"CrossCode_Attack_Rolling.png");
		player->set(player->Dash, Int2(8, 1), IMAGESIZE, -Offset, OFFSET_B);
		player->setPT(player->Dash, this);

		player->Die = new ObImage(L"Player_Die.png");
		player->set(player->Die, Int2(3, 1), IMAGESIZE, Vector2(0, 0), OFFSET_B);
		player->setPT(player->Die, this);
	}
	//================================================================================================

	Effect = new ObImage(L"Effect_1.png");
	Effect->maxFrame.x = 8;
	Effect->maxFrame.y = 5;
	Effect->scale.x = Effect->imageSize.x / Effect->maxFrame.x * 4.0f;
	Effect->scale.y = Effect->imageSize.y / Effect->maxFrame.y * 4.0f;

	Effect2 = new ObImage(L"Effect_2.png");
	Effect2->maxFrame.x = 8;
	Effect2->maxFrame.y = 5;
	Effect2->scale.x = Effect2->imageSize.x / Effect2->maxFrame.x * 4.0f;
	Effect2->scale.y = Effect2->imageSize.y / Effect2->maxFrame.y * 4.0f;

	Effect->SetParentRT(*this);
	Effect2->SetParentRT(*this);

	//================================================================================================
	Short_Attack_Length = 150;

	Cir = new ObCircle();
	Cir->scale.x = Short_Attack_Length * 2;
	Cir->scale.y = Short_Attack_Length * 2;
	Cir->isFilled = false;

	col = new ObRect();
	col->scale = Vector2();
	col->isFilled = false;
	col->SetWorldPosY(50);

	col->SetParentRT(*this);
	Cir->SetParentRT(*this);
	//================================================================================================

	scale.x = player->Idle->scale.x * 0.6f;
	scale.y = player->Idle->scale.y * 0.6f - 20;;
	color = Color(0.1f, 0.1f, 0.1f, 0.15f);
	pivot = OFFSET_T;

	player->Idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
	deathTime = 0.0f;

	A_count = true;

	//================================================================================================
	// 
	// 
	// 
	// 
	// 
	// 
	//================================================================================================

	//이펙트3 deque이용

	//effect_rotaion = true;
	//Effect3->SetWorldPosY(0);
	//Effect3->color = Color(0.5f, 0.5f, 0.5f, 1.f);;
	//
	//
	//trailTimer = 0.02f;
	//trailNum = 10;
	//trialTime = 0.0f;
	//
	//EffectTrail.resize(trailNum);
	//for (auto it = EffectTrail.begin(); it != EffectTrail.end(); it++)
	//{
	//	(*it) = new ObImage(L"Effect_3.png");
	//	(*it)->scale = Effect3->scale;
	//	(*it)->maxFrame = Effect3->maxFrame;
	//	(*it)->frame = Effect3->frame;
	//	(*it)->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
	//}
	//
	//isBattel = false;
	//if (effect_rotaion) {
	//	Effect3->rotation2.z += 1 * ToRadian;
	//	if (Effect3->rotation2.z > PI * 4) {
	//		Effect3->rotation2.z = 0;
	//		effect_rotaion = false;
	//
	//	}
	//	for (auto it = EffectTrail.begin(); it != EffectTrail.end(); it++)
	//	{
	//		(*it)->isVisible = true;
	//	}
	//}
	//else {
	//	for (auto it = EffectTrail.begin(); it != EffectTrail.end(); it++)
	//	{
	//		(*it)->isVisible = false;
	//	}
	//}
	//
	//	if (INPUT->KeyDown('F')) {
	//	
	//	}
	//
	//	if (TIMER->GetTick(trialTime, trailTimer))
	//	{
	//		EffectTrail[9]->frame.x = 0;
	//		EffectTrail[8]->frame.x = 0;
	//		EffectTrail[7]->frame.x = 0;
	//		EffectTrail[6]->frame.x = 1;
	//		EffectTrail[5]->frame.x = 1;
	//		EffectTrail[4]->frame.x = 1;
	//		EffectTrail[3]->frame.x = 2;
	//		EffectTrail[2]->frame.x = 2;
	//		EffectTrail[1]->frame.x = 3;
	//		EffectTrail[0]->frame.x = 0;
	//	
	//		EffectTrail.front()->pivot = OFFSET_B;
	//		EffectTrail.front()->SetWorldPos(Effect3->GetWorldPos());
	//		EffectTrail.front()->rotation = Effect3->rotation2;
	//	
	//		EffectTrail.push_back(EffectTrail.front());
	//		EffectTrail.pop_front();
	//	}
	//	
	//	for (auto it = EffectTrail.begin(); it != EffectTrail.end(); it++)
	//	{
	//		(*it)->Update();
	//	}
	//for (auto it = EffectTrail.begin(); it != EffectTrail.end(); it++)
	//{
	//	(*it)->Render();
	//}
}

Player::~Player()
{

}
void Player::Init(Vector2 spawn)
{
	SetWorldPosX(spawn.x);
	SetWorldPosY(spawn.y);

	state = PlayerState::IDLE;
}

void Player::Control()
{
	dir = Vector2();
	//계속 누를때
	if (INPUT->KeyPress('W'))
	{
		dir.y = 1.0f;
	}
	else if (INPUT->KeyPress('S'))
	{
		dir.y = -1.0f;
	}
	if (INPUT->KeyPress('A'))
	{
		dir.x = -1.0f;
	}
	else if (INPUT->KeyPress('D'))
	{
		dir.x = 1.0f;
	}
	dir2 = dir;
	dir.Normalize();

	MoveWorldPos(dir * DELTA * status.MoveSpeed);
}

void Player::Update()
{
	lastPos = GetWorldPos();
	ObCircle::Update();
	MouseDir = INPUT->GetWorldMousePos() - col->GetWorldPos();
	MouseDir.Normalize();

	bullet.erase(
		std::remove_if(
			bullet.begin(),
			bullet.end(),
			[&](Bullet* bullet) {
				// 현재 체력이 0 이하인 경우 해당 몬스터를 제거하려면 true를 반환
				// 그렇지 않은 경우 유지하려면 false를 반환

				bool shouldRemove = !bullet->GetIsFire();
				if (shouldRemove) {
					delete bullet;
				}
				return shouldRemove;
			}
		),
		bullet.end() // remove_if를 통해 뒤로 옮겨진 원소들의 시작 지점
				);

	if (state == PlayerState::IDLE)
	{
		LookTarget(dir);

		if (INPUT->KeyPress('W') or INPUT->KeyPress('A')
			or INPUT->KeyPress('S') or INPUT->KeyPress('D'))
		{
			state = PlayerState::RUN;
			player->Run->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
		if (INPUT->KeyPress(VK_LBUTTON)) {
			Distans = (GetWorldPos() - INPUT->GetWorldMousePos()).Length();
			A_count = !A_count;
			state = PlayerState::ATTACK;
			if (Distans < Short_Attack_Length) {
				Short_Attack = true;
				Long_Attack = false;

				//col->scale.x = 150;
				//col->scale.y = 100;
				if (A_count) {
					player->Short_Attack_Roll1->ChangeAnim(ANIMSTATE::ONCE, status.AttackSpeed / 10, false);
					Effect2->isVisible = true;
					Effect2->ChangeAnim(ANIMSTATE::ONCE, 0.06f);
				}
				else {
					player->Short_Attack_Roll2->ChangeAnim(ANIMSTATE::ONCE, status.AttackSpeed / 10, false);
					Effect->isVisible = true;
					Effect->ChangeAnim(ANIMSTATE::ONCE, 0.06f);
				}
				Bullet* B = new Bullet();
				Vector2 dir = Vector2(cosf(col->rotation2.z), sinf(col->rotation2.z));
				dir.Normalize();
				B->Fire(GetWorldPos(), dir2, Vector2(150, 150), 300, 10);
				bullet.push_back(B);
			}
			else {
				Short_Attack = false;
				Long_Attack = true;

				if (A_count) {
					LookTarget(MouseDir);
					player->Attack_Roll1->ChangeAnim(ANIMSTATE::ONCE, status.AttackSpeed / 10, false);
				}

				else {
					LookTarget(MouseDir);
					player->Attack_Roll2->ChangeAnim(ANIMSTATE::ONCE, status.AttackSpeed / 10, false);
				}

				Bullet* B = new Bullet();
				Vector2 dir = Vector2(INPUT->GetWorldMousePos() - GetWorldPos());
				dir.Normalize();
				B->Fire(GetWorldPos(), dir, 300, status.Range);
				bullet.push_back(B);
			}
		}
	}
	else if (state == PlayerState::RUN)
	{
		LookTarget(dir);
		Control();
		//walk->idle
		if (not(INPUT->KeyPress('W') or INPUT->KeyPress('A')
			or INPUT->KeyPress('S') or INPUT->KeyPress('D')))
		{
			state = PlayerState::RUN_E;
			player->Run_E->ChangeAnim(ANIMSTATE::ONCE, 0.1f);
		}
		//Attack
		if (INPUT->KeyPress(VK_LBUTTON)) {
			Distans = (GetWorldPos() - INPUT->GetWorldMousePos()).Length();
			A_count = !A_count;
			state = PlayerState::ATTACK;
			if (Distans < Short_Attack_Length) {
				Short_Attack = true;
				Long_Attack = false;

				col->scale.x = 150;
				col->scale.y = 150;
				if (A_count) {
					player->Short_Attack_Roll1->ChangeAnim(ANIMSTATE::ONCE, status.AttackSpeed / 10, false);
					Effect2->isVisible = true;
					Effect2->ChangeAnim(ANIMSTATE::ONCE, 0.06f);
				}
				else {
					player->Short_Attack_Roll2->ChangeAnim(ANIMSTATE::ONCE, status.AttackSpeed / 10, false);
					Effect->isVisible = true;
					Effect->ChangeAnim(ANIMSTATE::ONCE, 0.06f);
				}
				Bullet* B = new Bullet();
				Vector2 dir = Vector2(cosf(col->rotation2.z), sinf(col->rotation2.z));
				dir.Normalize();
				B->Fire(GetWorldPos(), dir2, Vector2(150, 150), 300, 10);
				bullet.push_back(B);
			}
			else {
				Short_Attack = false;
				Long_Attack = true;

				if (A_count) {
					LookTarget(MouseDir);
					player->Attack_Roll1->ChangeAnim(ANIMSTATE::ONCE, status.AttackSpeed / 10, false);
				}

				else {
					LookTarget(MouseDir);
					player->Attack_Roll2->ChangeAnim(ANIMSTATE::ONCE, status.AttackSpeed / 10, false);
				}

				Bullet* B = new Bullet();
				Vector2 dir = Vector2(INPUT->GetWorldMousePos() - GetWorldPos());
				dir.Normalize();
				B->Fire(GetWorldPos(), dir, 300, status.Range);
				bullet.push_back(B);
			}
		}

		//walk->DASH
		if (INPUT->KeyDown(VK_SPACE)) {
			state = PlayerState::DASH;
			player->Dash->ChangeAnim(ANIMSTATE::LOOP, 0.05f);
			DashTime = 0.0f;
		}
	}
	else if (state == PlayerState::RUN_E)
	{
		if (player->Run_E->isAniStop()) {
			state = PlayerState::IDLE;
			player->Idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
	}
	else if (state == PlayerState::ATTACK) {

		if (A_count) {
			if (Short_Attack) {
				if (player->Short_Attack_Roll1->isAniStop()) {
					state = PlayerState::IDLE;
					player->Idle->ChangeAnim(ANIMSTATE::LOOP, status.AttackSpeed / 10);

					col->scale.x = 0;
					col->scale.y = 0;
				}
			}
			if (Long_Attack) {
				if (player->Attack_Roll1->isAniStop()) {
					state = PlayerState::ATTACK2;
					player->Attack->ChangeAnim(ANIMSTATE::ONCE, status.AttackSpeed / 10, false);
				}
			}
		}
		else {
			if (Short_Attack) {
				if (player->Short_Attack_Roll2->isAniStop()) {
					state = PlayerState::IDLE;
					player->Idle->ChangeAnim(ANIMSTATE::LOOP, status.AttackSpeed / 10);
					col->scale.x = 0;
					col->scale.y = 0;
				}
			}
			if (Long_Attack) {
				if (player->Attack_Roll2->isAniStop()) {
					state = PlayerState::ATTACK2;
					player->Attack->ChangeAnim(ANIMSTATE::ONCE, status.AttackSpeed / 10, false);
				}
			}
		}
	}
	else if (state == PlayerState::ATTACK2) {
		if (player->Attack->isAniStop()) {
			state = PlayerState::IDLE;
			player->Idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
	}
	else if (state == PlayerState::DASH) {
		DashTime += DELTA;

		//0 ~ 1 * 180
		status.MoveSpeed = (250.0f * DashTime / 0.4f * PI + 100.0f);

		MoveWorldPos(dir * DELTA * status.MoveSpeed);
		LookTarget(dir);
		//roll->idle
		if (DashTime > 0.5f)
		{
			status.MoveSpeed = 200.0f;
			state = PlayerState::IDLE;
			player->Idle->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		}
	}
	else if (state == PlayerState::DIE) {
	}



	if (Effect->frame.x + 1 == Effect->maxFrame.x)
		Effect->isVisible = false;

	if (Effect2->frame.x + 1 == Effect2->maxFrame.x)
		Effect2->isVisible = false;

	player->Update();
	Effect->Update();
	Effect2->Update();
	Cir->Update();
	col->Update();
	status.Update();


	for (auto bulletPtr : bullet) {
		bulletPtr->Update();
	}






}

void Player::LateUpdate()
{
}



void Player::Render()
{
	ObCircle::Render();

	if (DEBUGMODE) {
		Cir->Render();
		col->Render();
	}

	switch (state) {
	case PlayerState::IDLE:
		player->Idle->Render();
		break;
	case PlayerState::DASH:
		player->Dash->Render();
		break;
	case PlayerState::RUN:
		player->Run->Render();
		break;
	case PlayerState::RUN_E:
		player->Run_E->Render();
		break;
	case PlayerState::ATTACK:
		if (A_count) {
			if (Short_Attack) {
				player->Short_Attack_Roll1->Render();
			}
			if (Long_Attack) {
				player->Attack_Roll1->Render();
			}
		}
		else {
			if (Short_Attack) {
				player->Short_Attack_Roll2->Render();
			}
			if (Long_Attack) {
				player->Attack_Roll2->Render();
			}
		}
		break;
	case PlayerState::ATTACK2:
		player->Attack->Render();
		break;
	case PlayerState::DIE:
		player->Die->Render();
		break;
	}


}

void Player::EffectRender()
{
	if (A_count) {
		if (Short_Attack) {
			Effect2->Render();
		}
	}
	else {
		if (Short_Attack) {
			Effect->Render();
		}
	}
	for (auto bulletPtr : bullet) {
		bulletPtr->Render();
	}

}

void Player::LookTarget(Vector2 target)
{
	if (target == Vector2()) return;
	int index =
		round((Utility::DirToRadian(target) + PI) / (45.f * ToRadian));

	if (index == 8)index = 0;

	player->Idle->frame.y = index;
	player->Run->frame.y = index;
	player->Run_E->frame.y = index;
	player->Attack->frame.x = Frame2[index];
	player->Attack_Roll1->frame.x = Frame2[index];
	player->Attack_Roll1->frame.x = Frame2[index];
	player->Attack_Roll2->frame.x = Frame2[index];
	player->Short_Attack_Roll1->frame.x = Frame2[index];
	player->Short_Attack_Roll2->frame.x = Frame2[index];

	Effect->rotation.z = 45.f + 45.f * index * ToRadian;
	Effect2->rotation.z = 45.f * ToRadian + angle[index];
	col->rotation2.z = 90.0f * ToRadian + 45.f * index * ToRadian;
}

Vector2 Player::GetFoot()
{

	return GetWorldPos() + dir2 * Vector2(scale.x / 2, scale.y / 2) + Vector2(0, -10);

}

void Player::GoBack()
{
	SetWorldPos(lastPos);
	Update();
}
