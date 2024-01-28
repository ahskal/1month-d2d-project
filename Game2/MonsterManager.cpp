#include "stdafx.h"
#include "TypeMonster.h"
#include "Monster1.h"
#include "Monster2.h"
#include "MonsterManager.h"

MonsterManager::MonsterManager()
{
	Map = nullptr;
	giveExp = 0;
}

MonsterManager::~MonsterManager()
{
}

void MonsterManager::Init()
{
}

void MonsterManager::Update()
{
	collisionsBetweenUnits();

	for (TypeMonster* monPtr : monster) {
		if (monPtr->GetPos().x > CAM->position.x - (app.GetWidth() / CAM->scale.x) - monPtr->col->scale.x &&
			monPtr->GetPos().x < CAM->position.x + (app.GetWidth() / CAM->scale.x) + monPtr->col->scale.x &&
			monPtr->GetPos().y > CAM->position.y - (app.GetHeight() / CAM->scale.y) - monPtr->col->scale.y &&
			monPtr->GetPos().y < CAM->position.y + (app.GetHeight() / CAM->scale.y) + monPtr->col->scale.y)
			monPtr->isScreen = true;
		else {
			monPtr->isScreen = false;
		}
	}


	for (TypeMonster* monPtr : monster) {
		if (!monPtr->isAttack_obj) {

		}

		monPtr->Update();
	}



	monster.erase(
		std::remove_if(
			monster.begin(),
			monster.end(),
			[&](TypeMonster* tm) {
				// 현재 체력이 0 이하인 경우 해당 몬스터를 제거하려면 true를 반환
				// 그렇지 않은 경우 유지하려면 false를 반환

				bool shouldRemove = tm->hp->CurHp <= 0;
				if (shouldRemove) {
					if (!tm->sound_Death.empty()) {
						SOUND->Stop(tm->sound_Death[RANDOM->Int(0, tm->sound_Death.size() - 1)]);
						SOUND->Play(tm->sound_Death[RANDOM->Int(0, tm->sound_Death.size() - 1)]);
					}
					GiveExp(tm);
					delete tm;
				}
				return shouldRemove;
			}
		),
		monster.end() // remove_if를 통해 뒤로 옮겨진 원소들의 시작 지점
				);

}

void MonsterManager::LateUpdate()
{
	for (auto monPtr : monster) {
		monPtr->LateUpdate();
	}

}

void MonsterManager::Render()
{
	for (TypeMonster* monPtr : monster) {
		if (monPtr->isScreen)
			monPtr->Render();
	}
}

void MonsterManager::HpRender()
{
	for (TypeMonster* monPtr : monster) {
		if (monPtr->isScreen)
			monPtr->hp->Render();
	}
}

void MonsterManager::Create(Vector2 Pos, unsigned int Num)
{
	for (TypeMonster* monPtr : monster) {
		if (monPtr) {
			if (Pos.x <= monPtr->GetCol()->GetWorldPos().x + monPtr->GetCol()->scale.x
				&& Pos.x >= monPtr->GetCol()->GetWorldPos().x - monPtr->GetCol()->scale.x
				&& Pos.y <= monPtr->GetCol()->GetWorldPos().y + monPtr->GetCol()->scale.y
				&& Pos.y >= monPtr->GetCol()->GetWorldPos().y - monPtr->GetCol()->scale.y) {
				// 이미 해당 좌표에 몬스터가 존재하므로 생성하지 않음
				return;
			}
		}
	}
	if (Num == 1) {
		Monster1* m = new Monster1(L"Monster_1.png", Int2(6, 3), L"Monster_Attack_1.png", Int2(2, 3), 400,
			200 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			0.5f,
			30 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			50 * ((int)(TIMER->GetWorldTime() / 150) + 1));
		m->sound_Death.push_back("Bugsprayer_Death1");
		m->sound_Death.push_back("Bugsprayer_Death2");
		m->sound_Death.push_back("Bugsprayer_Death3");
		m->sound_Move.push_back("BugDuo1");
		m->sound_Move.push_back("BugDuo2");
		m->sound_Move.push_back("BugDuo3");
		m->sound_Move.push_back("BugDuo4");
		m->Init(Pos);
		m->Map = Map;
		monster.push_back(m);
	}
	if (Num == 2) {
		Monster1* m = new Monster1(L"Monster_2.png", Int2(6, 3), L"Monster_Attack_2.png", Int2(2, 3), 400,
			200 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			0.5f * ((int)(TIMER->GetWorldTime() / 150) + 1),
			30 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			50 * ((int)(TIMER->GetWorldTime() / 150) + 1));
		m->sound_Death.push_back("Bugsprayer_Death1");
		m->sound_Death.push_back("Bugsprayer_Death2");
		m->sound_Death.push_back("Bugsprayer_Death3");
		m->sound_Move.push_back("BugDuo1");
		m->sound_Move.push_back("BugDuo2");
		m->sound_Move.push_back("BugDuo3");
		m->sound_Move.push_back("BugDuo4");
		m->Init(Pos);
		m->Map = Map;
		monster.push_back(m);
	}
	if (Num == 3) {
		Monster1* m = new Monster1(L"Monster_3.png", Int2(4, 3), L"Monster_Attack_3.png", Int2(2, 3), 500,\
			300 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			0.5f,
			50 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			75 * ((int)(TIMER->GetWorldTime() / 150) + 1));
		m->sound_Move.push_back("fish1");
		m->sound_Move.push_back("fish2");
		m->sound_Move.push_back("fish3");
		m->sound_Move.push_back("fish4");
		m->sound_Move.push_back("fish5");
		m->sound_Move.push_back("fish6");
		m->sound_Move.push_back("fish7");
		m->sound_Move.push_back("fish8");
		m->sound_Move.push_back("fish9");
		m->sound_Move.push_back("fish10");
		m->sound_Move.push_back("fish11");
		m->Init(Pos);
		m->Map = Map;
		monster.push_back(m);
	}
	if (Num == 4) {
		Monster1* m = new Monster1(L"Monster_4.png", Int2(4, 3), L"Monster_Attack_4.png", Int2(2, 3), 500,
			300 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			0.5f * ((int)(TIMER->GetWorldTime() / 150) + 1),
			50 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			75 * ((int)(TIMER->GetWorldTime() / 150) + 1));
		m->sound_Move.push_back("fish1");
		m->sound_Move.push_back("fish2");
		m->sound_Move.push_back("fish3");
		m->sound_Move.push_back("fish4");
		m->sound_Move.push_back("fish5");
		m->sound_Move.push_back("fish6");
		m->sound_Move.push_back("fish7");
		m->sound_Move.push_back("fish8");
		m->sound_Move.push_back("fish9");
		m->sound_Move.push_back("fish10");
		m->sound_Move.push_back("fish11");
		m->Init(Pos);
		m->Map = Map;
		monster.push_back(m);
	}
	if (Num == 5) {
		Monster1* m = new Monster1(L"Monster_5.png", Int2(6, 3), L"Monster_Attack_5.png", Int2(4, 3), 600,
			500 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			0.4f,
			75 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			100 * ((int)(TIMER->GetWorldTime() / 150) + 1));
		m->sound_Move.push_back("WingFlap1");
		m->sound_Move.push_back("WingFlap2");
		m->sound_Move.push_back("WingFlap3");
		m->sound_Move.push_back("WingFlap4");
		m->sound_Move.push_back("WingFlap5");
		m->sound_Move.push_back("WingFlap6");

		m->Init(Pos);
		m->Map = Map;
		monster.push_back(m);
	}
	if (Num == 6) {
		Monster1* m = new Monster1(L"Monster_6.png", Int2(6, 3), L"Monster_Attack_6.png", Int2(4, 3), 600,
			500 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			0.4f,
			75 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			100 * ((int)(TIMER->GetWorldTime() / 150) + 1));
		m->sound_Move.push_back("WingFlap1");
		m->sound_Move.push_back("WingFlap2");
		m->sound_Move.push_back("WingFlap3");
		m->sound_Move.push_back("WingFlap4");
		m->sound_Move.push_back("WingFlap5");
		m->sound_Move.push_back("WingFlap6");


		m->Init(Pos);
		m->Map = Map;
		monster.push_back(m);
	}
	if (Num == 7) {
		Monster2* m = new Monster2(L"Monster_7.png", Int2(8, 3), L"Monster_Attack_7.png", Int2(4, 3), 200,
			1500 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			250, 0.4f,
			150 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			300 * ((int)(TIMER->GetWorldTime() / 150) + 1));
		m->sound_Move.push_back("Heavy_Short1");
		m->sound_Move.push_back("Heavy_Short2");
		m->sound_Move.push_back("Heavy_Short3");
		m->sound_Move.push_back("Heavy_Short4");
		m->sound_Death.push_back("Heavy_Death");

		m->Init(Pos);
		m->Map = Map;
		monster.push_back(m);
	}
	if (Num == 8) {
		Monster2* m = new Monster2(L"Monster_8.png", Int2(8, 3), L"Monster_Attack_8.png", Int2(3, 3), 150, 750,
			150 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			0.4f,
			50 * ((int)(TIMER->GetWorldTime() / 150) + 1),
			125 * ((int)(TIMER->GetWorldTime() / 150) + 1));
		m->Init(Pos);
		m->Map = Map;
		monster.push_back(m);
	}

}

void MonsterManager::SelectTarget(Vector2 Pos)
{
	AttatkPos = Pos;

	for (auto monPtr : monster) {
		if (!monPtr->isAttack_obj)
			monPtr->SetTagetPos(AttatkPos);
	}
}

void MonsterManager::collisionsBetweenUnits()
{
	const int numMonsters = static_cast<int>(this->monster.size());
	for (int i = 0; i < numMonsters - 1; i++)
	{
		for (int j = i + 1; j < numMonsters; j++)
		{
			// 몬스터가 다른 몬스터와 충돌하면 밀어냄
			if (monster[i]->col->Intersect(monster[j]->col))
			{
				Vector2 enemyDir = monster[i]->col->GetWorldPos() - monster[j]->col->GetWorldPos();
				Vector2 OtherEnemyDir = monster[j]->col->GetWorldPos() - monster[i]->col->GetWorldPos();

				enemyDir.Normalize();
				OtherEnemyDir.Normalize();

				monster[i]->col->MoveWorldPos(enemyDir * 50 * DELTA);
				monster[j]->col->MoveWorldPos(OtherEnemyDir * 50 * DELTA);
			}
		}
	}
}

void MonsterManager::GiveExp(TypeMonster* tm)
{
	giveExp += tm->DropExp;
}

void MonsterManager::ReFindPath()
{
	for (TypeMonster* monPtr : monster) {
		Map->PathFinding(monPtr->GetPos(), AttatkPos, monPtr->way);
	}


}
