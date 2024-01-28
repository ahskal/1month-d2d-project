#include "stdafx.h"
#include "TypeMonster.h"
#include "Build.h"
#include "Monster1.h"
extern bool DEBUGMODE;

Monster1::Monster1(wstring file, Int2 maxFream, wstring file2, Int2 maxFream2,
	float length, int Hp, float aniSpeed, int atk, int dropExp)
{
	AniSpeed = aniSpeed;
	Atk = atk;

	img = new ObImage(file);
	SetImage(img, maxFream, 3);
	attack = new ObImage(file2);
	SetImage(attack, maxFream2, 3);

	hp = new ProgressBar();
	SetHp(hp, Vector2(-50, -50), Hp);

	col = new ObCircle();
	col->scale.x = img->scale.x * 0.5f;
	col->scale.y = img->scale.y * 0.5f;
	col->isFilled = false;

	buildingCol = new ObCircle();
	buildingCol->scale.x = img->scale.x + length;
	buildingCol->scale.y = img->scale.y + length;
	buildingCol->isFilled = false;

	img->SetParentRT(*col);
	attack->SetParentRT(*col);
	hp->SetParentRT(*col);
	buildingCol->SetParentRT(*col);

	Find_Length = length;

	dir[0] = 1;
	dir[1] = 2;
	dir[2] = 2;
	dir[3] = 1;
	dir[4] = 0;
	dir[5] = 0;

	is_atk = false;
	timer = 0;

	DropExp = dropExp;
	FindTimer = 0;;
}

Monster1::~Monster1() {}

void Monster1::Move(Vector2 TargetPos)
{
	TypeMonster::Move(TargetPos);
	index =
		round((Utility::DirToRadian(moveDir) + PI) / (60 * ToRadian));
	if (index == 6) index = 0;
	if (index == 0 || index == 1 || index == 5) {
		col->rotation.y = PI;
	}
	else {
		col->rotation.y = 0.0f;
	}
}

void Monster1::Init(Vector2 spawn)
{
	col->SetWorldPos(spawn);
	source = spawn;
	target = spawn;
	weight = 0.0f;

	M_State = State::IDLE;
}

void Monster1::Update()
{
	TypeMonster::Update();

	img->frame.y = dir[index];
	attack->frame.y = dir[index];

	for (auto buildPtr : BUILD->GetBuildVector()) {
		if (buildingCol->Intersect(buildPtr->GetCollision())) {
			AttackPos = buildPtr->GetCollision()->GetWorldPivot();
			break;
		}
		else {
			AttackPos = MONSTER->AttatkPos;
		}
	}

	buildingCol->Update();
}

void Monster1::LateUpdate()
{
	switch (M_State) {
	case State::IDLE:
		if (!sound_Move.empty() && isScreen && TIMER->GetTick(sounddelay1, 1.0f)) {
			SOUND->Stop(sound_Move[RANDOM->Int(0, sound_Move.size() - 1)]);
			SOUND->Play(sound_Move[RANDOM->Int(0, sound_Move.size() - 1)]);
		}
		img->ChangeAnim(ANIMSTATE::LOOP, 0.1f);
		Current_Length = (col->GetWorldPos() - AttackPos).Length();
		if (Current_Length < Find_Length) {
			M_State = State::ATTACK;
			attack->ChangeAnim(ANIMSTATE::ONCE, AniSpeed);

			is_atk = true;
			way.clear();
			return;
		}
		else {
			if (TIMER->GetTick(FindTimer, FindingTimer))
				Map->PathFinding(col->GetWorldPos(), AttackPos, way);
		}

		if (!way.empty() && weight < 1.0f && !is_atk)
		{
			float distance = (target - source).Length();
			float timeToTarget = distance / speed;
			weight += DELTA / timeToTarget;
			col->SetWorldPos(Vector2::Lerp(source, target, weight));

			if (weight >= 1.0f)
			{
				way.pop_back();
				if (!way.empty())
				{
					weight = 0.0f;
					source = col->GetWorldPos();
					target = way.back()->Pos;
					Move(target);
				}
				else
				{
					weight = 0.0f;
					source = target;
				}
			}
		}
		break;
	case State::ATTACK:
		Attack();
		break;
	}
}

void Monster1::Render()
{
	TypeMonster::Render();
	if (DEBUGMODE)
		buildingCol->Render();
}

void Monster1::Attack()
{
	if (M_State == State::ATTACK && is_atk) {
		if (attack->isAniStop() && TIMER->GetTick(timer, AniSpeed)) {
			Bullet* B = new Bullet();
			Vector2 dir = Vector2(AttackPos - col->GetWorldPos());
			dir.Normalize();
			B->Fire(col->GetWorldPivot(), dir, 300);
			if (!sound_Attack.empty()) {
				SOUND->Stop(sound_Attack[RANDOM->Int(0, sound_Attack.size() - 1)]);
				SOUND->Play(sound_Attack[RANDOM->Int(0, sound_Attack.size() - 1)]);
			}
			is_atk = false;
			bullet.push_back(B);
			M_State = State::IDLE;
		}
	}
}