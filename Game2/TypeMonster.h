#include "ProgressBar.h"
#include "Bullet.h"
#include "Build.h"
#include "stdafx.h"

#define MaxBullet 5
extern bool DEBUGMODE;

#pragma once
enum class State
{
	IDLE,
	MOVE,
	ATTACK,
	CRUSH
};

class TypeMonster
{
protected:
	State   M_State;

	Vector2 moveDir;
	Vector2 source;

	ObImage* img;
	ObImage* attack;
	float speed = 200;

	float FindTimer;
	float FindingTimer = DELTA * 100;

	float AniSpeed;

public:
	//경로
	vector<class Tile*> way;
	// 플레이어 좌표
	Vector2 AttackPos;
	// 맵
	ObTileMap* Map;

	// 본인의 이전 좌표
	Vector2 lastPos;

	// 충돌체 
	vector<Bullet*> bullet;

	Vector2 target;

	ProgressBar* hp;

	ObCircle* col;

	ObCircle* buildingCol;
	bool isAttack_obj = false;

	float Atk;

	int DropExp;

	// 현재 거리
	float Current_Length;
	// 찾을수있는 최대 거리
	float Find_Length;

	float	weight;

	// 매니저에서 플레이어 좌표를 받아올 코드
	void SetTagetPos(Vector2 pos) { AttackPos = pos; };

	virtual void Move(Vector2 TargetPos) {
		weight = 0.0f;
		target = TargetPos;
		moveDir = target - col->GetWorldPos();

		moveDir.Normalize();
	};

public:
	TypeMonster() {}
	virtual ~TypeMonster() {}

	virtual void Update() {
		lastPos = col->GetWorldPos();


		bullet.erase(
			std::remove_if(
				bullet.begin(),
				bullet.end(),
				// #람다 함수
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

		for (auto bulletPtr : bullet) {
			bulletPtr->Update();
		}
		hp->Update();
		col->Update();
		img->Update();
		attack->Update();



	};
	virtual void LateUpdate() {};
	virtual void Render() {
		if (DEBUGMODE)
			col->Render();
		switch (M_State) {
		case State::IDLE:
			img->Render();
			break;
		case State::ATTACK:
			attack->Render();
			break;
		}
		hp->Render();
		for (auto bulletPtr : bullet) {
			bulletPtr->Render();
		}
	};

	void GoBack()
	{
		col->SetWorldPos(lastPos);
		Update();
	}

	//TypeMonster* CreateClone() { return new TypeMonster(*this); }
	ObCircle* GetCol() const& { return col; };
	Vector2 GetPos() const& { return col->GetWorldPos(); };

	void SetImage(ObImage* img, Int2 MaxFream, int imgsize) {
		img->maxFrame = MaxFream;
		img->scale.x = img->imageSize.x * imgsize / img->maxFrame.x;
		img->scale.y = img->imageSize.y * imgsize / img->maxFrame.y;
	}

	void SetCol(ObCircle* obj, bool isfilled = false) {
		obj->scale.x = img->scale.x * 0.5f;
		obj->scale.y = img->scale.y * 0.5f;
		obj->isFilled = isfilled;
	}

	void SetPT(GameObject* parent, GameObject* child) {
		child->SetParentRT(*parent);
	}

	void SetHp(ProgressBar* hp, Vector2 Pos, int setHp) {
		hp->SetLocalPosX(Pos.x);
		hp->SetLocalPosY(Pos.y);
		hp->MaxHp = hp->CurHp = setHp;
	}

	vector<string>sound_Attack;
	vector<string>sound_Death;
	vector<string>sound_Move;

	float sounddelay1 = 0;

	bool isScreen = false;

};

