#include "stdafx.h"

#include "Build.h"

#include "DefenceTower.h"
#include "AttackTower.h"
#include "RepairTower.h"

#include "BuildManager.h"

BuildManager::BuildManager() {}
BuildManager::~BuildManager() {}
void BuildManager::Init() {

}
void BuildManager::Update() {
	build.erase(
		std::remove_if(
			build.begin(),
			build.end(),
			[&](Build* build) {
				// 현재 체력이 0 이하인 경우 해당 몬스터를 제거하려면 true를 반환
				// 그렇지 않은 경우 유지하려면 false를 반환
				if (build->IsDeadOrAlive()) {
					switch (RANDOM->Int(1, 3)) {
					case 1:SOUND->Stop("break1"); SOUND->Play("break1"); break;
					case 2:SOUND->Stop("break2"); SOUND->Play("break2"); break;
					case 3:SOUND->Stop("break3"); SOUND->Play("break3"); break;
					}
					delete build;
					return true;
				}
				return false;
			}
		),
		build.end() // remove_if를 통해 뒤로 옮겨진 원소들의 시작 지점
				);

	//Update
	for (auto buildPtr : build) {
		buildPtr->Update();
	}
}

void BuildManager::UpdateStatus(float hp, float as, float range, float healing)
{
	for (auto buildPtr : build) {
		buildPtr->bonus_hp = hp;
	}

	for (auto buildPtr : build) {
		AttackTower* AttackPtr = dynamic_cast<AttackTower*>(buildPtr);
		if (AttackPtr == nullptr) continue;
		AttackPtr->bonus_as = as;
		AttackPtr->bonus_range = range;
	}

	for (auto buildPtr : build) {
		RepairTower* RePairPtr = dynamic_cast<RepairTower*>(buildPtr);
		if (RePairPtr == nullptr) continue;
		RePairPtr->bonus_Heal = healing;
		RePairPtr->bonus_range = range;
	}
}

void BuildManager::LateUpdate()
{
	for (auto buildPtr : build) {
		// 수리타워 인지 판별
		RepairTower* RepairPtr = dynamic_cast<RepairTower*>(buildPtr);
		if (RepairPtr == nullptr) continue;
		for (auto buildPtr2 : build) {
			// 본인인지 판별
			if (RepairPtr == buildPtr2) continue;
			if (RepairPtr->GetInteractionRect()->Intersect(buildPtr2->GetCollision()->GetWorldPivot())) {
				if (TIMER->GetTick(RepairTimer, 1.0f) && (buildPtr2->GetHpbar()->CurHp < buildPtr2->GetHpbar()->MaxHp))
				{
					int soundNum = RANDOM->Int(1, 3);
					switch (soundNum)
					{
					case 1:SOUND->Stop("RePairTower1"); SOUND->Play("RePairTower1"); break;
					case 2:SOUND->Stop("RePairTower2"); SOUND->Play("RePairTower2"); break;
					case 3:SOUND->Stop("RePairTower3"); SOUND->Play("RePairTower3"); break;
					}

					//본인 회복
					RepairPtr->GetHpbar()->Repair(RepairPtr->GetHeal(), 4);
					//범위 안에 들어온 객체 회복
					buildPtr2->GetHpbar()->Repair(RepairPtr->GetHeal(), 4);
					return;
				}
			}
		}
	}
}

void BuildManager::Render()
{
	for (auto buildPtr : build) {
		buildPtr->Render();
	}
}



void BuildManager::Create(Vector2 Pos, int Type)
{
	Build* Tower = new Build();
	switch (Type) {
	case 0:
		Tower = new DefenceTower(100, 500);
		break;
	case 1:
		Tower = new RepairTower(100, 300, 350, 20);
		break;
	case 2:
		Tower = new AttackTower(100, 450, 1000, 25, Int2(3, 16));
		break;
	}
	Tower->SetPos(Pos);

	build.push_back(Tower);
}
