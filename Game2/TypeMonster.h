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
	//���
	vector<class Tile*> way;
	// �÷��̾� ��ǥ
	Vector2 AttackPos;
	// ��
	ObTileMap* Map;

	// ������ ���� ��ǥ
	Vector2 lastPos;

	// �浹ü 
	vector<Bullet*> bullet;

	Vector2 target;

	ProgressBar* hp;

	ObCircle* col;

	ObCircle* buildingCol;
	bool isAttack_obj = false;

	float Atk;

	int DropExp;

	// ���� �Ÿ�
	float Current_Length;
	// ã�����ִ� �ִ� �Ÿ�
	float Find_Length;

	float	weight;

	// �Ŵ������� �÷��̾� ��ǥ�� �޾ƿ� �ڵ�
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
				// #���� �Լ�
				[&](Bullet* bullet) {
					// ���� ü���� 0 ������ ��� �ش� ���͸� �����Ϸ��� true�� ��ȯ
					// �׷��� ���� ��� �����Ϸ��� false�� ��ȯ

					bool shouldRemove = !bullet->GetIsFire();
					if (shouldRemove) {
						delete bullet;
					}
					return shouldRemove;
				}
			),
			bullet.end() // remove_if�� ���� �ڷ� �Ű��� ���ҵ��� ���� ����
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

