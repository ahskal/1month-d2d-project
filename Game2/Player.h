#pragma once
#include "Bullet.h"

#define maxBullet 10
#define IMAGESIZE 3

extern bool DEBUGMODE;


enum class PlayerState
{
	IDLE,
	RUN,
	RUN_E,
	ATTACK,
	ATTACK2,
	ATTACK_ROLL,
	DASH,
	DIE,
};


class Player : public ObCircle
{
private:
	friend class PlayerUI;


private:
	struct PlayerStatus {
		int Level;
		int MaxLevel;


		float MoveSpeed;

		float Hp;
		float AttackSpeed;
		float Attack;
		float Defense;
		float Range;

		float const_Hp;
		float const_Atk;
		float const_Def;
		float const_AS;
		float const_Range;

		float Base_Hp;
		float Base_Atk;
		float Base_Def;
		
		float bonus_Hp;
		float bonus_Atk;
		float bonus_Def;
		float bonus_AS;
		float bonus_Range;


		int Base_Elemental;

		// @brief 기본스탯을 정하는 함수
		// @param Level, MaxLevel, Hp, MaxHp, Exp, MaxExp,Attack, AttackSpeed,Defense를 설정해주는 값 
		//
		PlayerStatus() = default;

		void Init() {
			const_Hp = 200;
			const_Atk = 15;
			const_Def = 10;
			const_AS = 1.0f;
			const_Range = 300;
			MoveSpeed = 150;
			LevelUp();
		}

		void Update() {
			Hp = bonus_Hp + Base_Hp;
			Attack =  bonus_Atk+ Base_Atk;
			Defense = bonus_Def+ Base_Def;
			AttackSpeed = 1.0f - bonus_AS;
			Range = const_Range + bonus_Range;
		};

		void LevelUp() {
			Base_Hp = const_Hp + Level * 20;
			Base_Atk = const_Atk + Level * 3;
			Base_Def = const_Def + Level * 2;
		}
	};

	struct Unit {
		ObImage* Idle;
		ObImage* Run;
		ObImage* Run_E;
		ObImage* Attack_Roll1;
		ObImage* Attack_Roll2;
		ObImage* Short_Attack_Roll1;
		ObImage* Short_Attack_Roll2;
		ObImage* Attack;
		ObImage* Dash;
		ObImage* Die;

		//@brief 이미지를 설정하는 함수
		//@param img 이미지의  포인터
		//@param maxF 이미지의 최대 프레임
		//@param scale 이미지의 크기를 조절하는 비율
		//@param Offset 이미지를 움직일 좌표(오프셋)
		//@param pivot 이미지가 그려질 기준점(회전 중심점)
		//w
		void set(ObImage* img, Int2 maxF, float scale, Vector2 Offset = Vector2(), Vector2 pivot = OFFSET_N) {
			// 1. 이미지의 최대 프레임 설정
			img->maxFrame = maxF;

			// 2. 이미지의 x 스케일 설정
			img->scale.x = img->imageSize.x / img->maxFrame.x * scale;

			// 3. 이미지의 y 스케일 설정
			img->scale.y = img->imageSize.y / img->maxFrame.y * scale;

			// 4. 이미지의 x 위치 오프셋 설정
			img->SetLocalPosY(Offset.x);

			// 5. 이미지의 y 위치 오프셋 설정
			img->SetLocalPosY(Offset.y);

			// 6. 이미지의 회전 중심점 설정
			img->pivot = pivot;
		}

		void setPT(ObImage* img, GameObject* P) {
			img->SetParentRT(*P);
		}

		void Update() {
			Idle->Update();
			Run->Update();
			Run_E->Update();
			Attack_Roll1->Update();
			Attack_Roll2->Update();
			Short_Attack_Roll1->Update();
			Short_Attack_Roll2->Update();
			Attack->Update();
			Dash->Update();
			Die->Update();
		}
	};

	Unit* player;
	PlayerStatus status;
	PlayerState  state;

	
	
	
	vector<Bullet*> bullet;

	Vector2 Offset;

	Vector2 lastPos;

	Vector2		dir;
	Vector2		dir2;
	Vector2     MouseDir;
	float		speed;

	int index;
	int Frame[8];
	int Frame2[8];
	float angle[8];

	ObImage* Effect;
	ObImage* Effect2;

	ObCircle* Cir;
	ObRect* col;

	bool effect_rotaion;

	bool Short_Attack;
	bool Long_Attack;
	bool  A_count;

	int Short_Attack_Length;

	int count;

	float Distans;

	float DashTime;

	float deathTime;

	float repairTimer = 0;


public:
	//class Bullet* bullet[maxBullet];
	bool isBattel;


	Player();
	virtual ~Player();
	void Init(Vector2 spawn);
	void Control();
	void Update() override;
	void LateUpdate();
	void Render() override;
	void EffectRender();
	void LookTarget(Vector2 target);
	Vector2 GetFoot();
	void GoBack();


	//Bullet* GetBulletCollision() const { return bullet; }

	PlayerStatus& GetStatus() { return status; }

	ObRect* GetAttackCollision() const { return col; }
	vector<class Bullet*>& GetBulletVector() { return bullet; };
	



	void ChangeEffect(int idx) {
		Effect->frame.y = idx;
		Effect2->frame.y = idx;
	}
};

