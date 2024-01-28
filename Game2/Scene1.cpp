#include "stdafx.h"
#include "ProgressBar.h"
#include "Player.h"
#include "Bullet.h"
#include "PlayerUI.h"	
#include "TypeMonster.h"
#include "Build.h"
#include "AttackTower.h"
#include "RepairTower.h"
#include "Scene1.h"

extern bool DEBUGMODE;

void MakeWall(ObTileMap* map) {
	while (BUILD->GetBuildVector().size() != 50) {
		Int2 Idx(RANDOM->Int(0, map->GetTileSize().x - 1), RANDOM->Int(0, map->GetTileSize().y - 1));

		if (map->GetTileState(Idx) == TILE_WALL) {
			continue;
		}

		Vector2 diam = map->scale;
		Vector2 centerPos = Vector2(Idx.x * diam.x + diam.x / 2, Idx.y * diam.y + diam.x / 2);

		Vector2 Pos(Idx.x * map->GetTileSize().x, Idx.y * map->GetTileSize().y);
		bool isDuplicate = false;

		if (BUILD->GetBuildVector().size() > 1)
			for (auto buildPtr : BUILD->GetBuildVector()) {
				if (Pos == buildPtr->GetWorldPos()) {
					
					cout << "중복된 건물 좌표" << endl;
					isDuplicate = true;
					break;
				}
			}
		if (!isDuplicate) {
			BUILD->Create(Pos, 0);
		}
	}
}

void Scene1::randomPos()
{
	const int maxAttempts = 1000; // 최대 시도 횟수

	for (int attempt = 0; attempt < maxAttempts; ++attempt) {
		// 랜덤한 좌표 생성
		Int2 Pos(RANDOM->Int(1, map->GetTileSize().x - 1), RANDOM->Int(1, map->GetTileSize().y - 1));

		// 생성된 좌표가 맵 내에 있는지 확인
		if (map->IsInMap(Pos)) {
			bool isAllNonWall = true; // 주변 모든 타일이 벽이 아닌지 확인하기 위한 플래그
			// 주변 3x3 영역을 순회하며 타일 상태 확인
			for (int y = Pos.y - 1; y <= Pos.y + 1; y++) {
				for (int x = Pos.x - 1; x <= Pos.x + 1; x++) {
					// 인덱스가 맵 범위 내에 있는지 확인
					if (y >= 0 && y < map->GetTileSize().y && x >= 0 && x < map->GetTileSize().x) {
						Int2 currentIdx(x, y);

						// 현재 타일이 벽인지 확인하여 isAllNonWall 업데이트
						if (map->GetTileState(currentIdx) == TILE_WALL) {
							isAllNonWall = false;
							break; // 벽이 하나라도 있으면 더 이상 확인할 필요 없음
						}
					}
				}
				if (!isAllNonWall) {
					break; // 벽이 하나라도 있으면 더 이상 확인할 필요 없음
				}
			}
			// 주변의 모든 타일이 벽이 아닌 경우 적절한 위치로 설정하고 종료
			if (isAllNonWall) {
				Position = Vector2(Pos.x * map->scale.x + map->scale.x / 2, Pos.y * map->scale.y + map->scale.y / 2);
				return;
			}
		}
	}
	// 만약 적절한 위치를 찾지 못했다면 Position을 초기화하거나 특정 기본 값으로 설정할 수 있습니다.
	Position = Vector2(); // 예시로 Position을 초기화합니다.
}

Scene1::Scene1()
{
	map = new ObTileMap();
	map->file = "TileMap_1.txt";
	map->CreateTileCost();

	pl = new Player();
	cam = new Camera();
	UI = new PlayerUI();
	UI->MaxHp = UI->CurHp = 200;

	Position = Vector2();

	map->Load();

}
Scene1::~Scene1() {}


static int recursiveCallCount = 0;


void Scene1::Init()
{
	


	app.background = Color(0.5, 0.7, 1, 1);
	map->Load();
	map->SetWorldPos(Vector2(0, 0));
	map->CreateTileCost();

	MONSTER->GetMap(map);
	randomPos();
	if (Position.x == 0.0f || Position.y == 0.0f) SCENE->ChangeScene("SC3");
	pl->Init(Vector2(Position));

	UI->Init(Vector2(4, 4));
	SelectLength = 0;

	//MONSTER->Create(Vector2(1500.f, 1500.f));

	//for (int i = 0; i < 10; i++) {
	//	recursiveCallCount = 0;
	//	randomPos();
	//	MONSTER->Create(Position, RANDOM->Int(1, 2));
	//}


	//test1 = new thread(MakeWall, map);
	//test1->join();
	//
	//if (BUILD->GetBuildVector().size() == 50) {
	//	delete test1;
	//}
	pl->GetStatus().Init();
	pl->GetStatus().Update();
}

void Scene1::Release()
{
}

void Scene1::Update()
{

	if (ImGui::SliderFloat("Cam Scale %f", &CAM->scale.x, 0.0f, 2.0f)) {
		if (CAM->scale.x > 2.0f) CAM->scale.x = 2.0f;
		if (CAM->scale.x < 0.0f) CAM->scale.x = 0.0f;
		CAM->scale.y = CAM->scale.x;
	}


	CAM->position = pl->GetWorldPos();

	//UI출력할 카메라 셋
	cam->Set();
	pl->ChangeEffect(UI->Element_idx);

	UI->Atk = pl->GetStatus().Attack;
	UI->Def = pl->GetStatus().Defense;

	pl->GetStatus().Level = UI->Level;

	UI->MaxHp = pl->GetStatus().Hp;

	pl->GetStatus().bonus_Atk = UI->bonus_Atk * 5;
	pl->GetStatus().bonus_Def = UI->bonus_Def * 2;
	pl->GetStatus().bonus_AS = UI->bonus_AS * 0.05;
	pl->GetStatus().bonus_Hp = UI->bonus_Hp * 50;
	pl->GetStatus().bonus_Range = UI->bonus_Range * 25;

	BUILD->UpdateStatus(
		pl->GetStatus().bonus_Hp,
		pl->GetStatus().bonus_AS,
		pl->GetStatus().bonus_Range,
		UI->bonus_Healing * 5);


	if (UI->Event) {
		pl->GetStatus().LevelUp();
	}










	// 몬스터 소환
	if (INPUT->KeyDown(VK_F1)) {
		Vector2 Pos = INPUT->GetWorldMousePos();
		MONSTER->Create(Pos, RANDOM->Int(1, 8));
	}
	if (INPUT->KeyDown(VK_F2)) {
		isCreate = !isCreate;
	}

	isCreate = true;

	if (isCreate) {
		if (TIMER->GetTick(timer2, 3.0f - (TIMER->GetWorldTime())/300)) {
			recursiveCallCount = 0;
			randomPos();
			MONSTER->Create(Position, RANDOM->Int(1, 8));
		}
	}



	// 임시로 만든 건물 타입변경
	if (INPUT->KeyDown('1')) {
		buildType = 0;
	}
	if (INPUT->KeyDown('2')) {
		buildType = 1;
	}
	if (INPUT->KeyDown('3')) {
		buildType = 2;
	}


	// 우클릭시 건물짓기
	if (INPUT->KeyDown(VK_RBUTTON)) {
		Int2 Idx;
		map->WorldPosToTileIdx(INPUT->GetWorldMousePos(), Idx);
		Vector2 Pos(Idx.x * map->GetTileSize().x, Idx.y * map->GetTileSize().y);
		bool isDuplicate = false;
		for (auto buildPtr : BUILD->GetBuildVector()) {
			if (Pos == buildPtr->GetWorldPos()) {
				SOUND->Stop("BuildError");
				SOUND->Play("BuildError");
				cout << "중복된 건물 좌표" << endl;
				isDuplicate = true;
				break;
			}
		}
		if (!isDuplicate) {
			SOUND->Stop("BuildTrue");
			SOUND->Play("BuildTrue");
			BUILD->Create(Pos, buildType);
		}
	}

	MONSTER->SelectTarget(pl->GetWorldPos());
	MONSTER->Update();
	DAMAGE->Update();
	BUILD->Update();

	map->Update();

	pl->Update();
	UI->Update();
}

void Scene1::LateUpdate()
{


	// 플레이어 충돌 관련
	{
		// 플레이어가 벽을 파괴할때 
		Int2 Idx;
		map->WorldPosToTileIdx(pl->GetWorldPos(), Idx);
		// 맵 경계 안쪽의 타일에 대해서만 검사
		if (Idx.x > 2 && Idx.y > 2 && Idx.x < map->GetTileSize().x - 3 && Idx.y < map->GetTileSize().y - 3) {
			for (int y = -1; y <= 1; y++) {
				for (int x = -1; x <= 1; x++) {
					Int2 Tpos(Idx.x + x, Idx.y + y);
					// 타일 인덱스가 유효한지 확인
					if (Tpos.x >= 0 && Tpos.x < map->GetTileSize().x && Tpos.y >= 0 && Tpos.y < map->GetTileSize().y) {
						// 벽인 타일만 처리
						if (map->GetTileState(Tpos) == TILE_WALL) {
							if (pl->GetAttackCollision()->Intersect(map->GetTile(Tpos.x, Tpos.y).Pos) && UI->Element_idx == 0) {
								int soundNum = RANDOM->Int(1,4);
								switch (soundNum)
								{
								case 1:SOUND->Stop("BreakGround1"); SOUND->Play("BreakGround1"); break;
								case 2:SOUND->Stop("BreakGround2"); SOUND->Play("BreakGround2"); break;
								case 3:SOUND->Stop("BreakGround3"); SOUND->Play("BreakGround3"); break;
								case 4:SOUND->Stop("BreakGround4"); SOUND->Play("BreakGround4"); break;
								}
								float C = (255.f / 20.f) * RANDOM->Int(3, 8) / 255.f * 0.5f;
								Color color = Color(C, C, C, 0.5f);
								map->SetTile2(Tpos, Int2(), 1, 0, color);
								map->UpdateSub();
								map->CreateTileCost();
							}
						}
					}
				}
			}
		}
		// 벽이랑 충돌했을때
		if (map->GetTileState(pl->GetFoot()) == TILE_WALL)
		{
			pl->GoBack();
		}

		// 건물이랑 충돌했을때
		for (auto buildPtr : BUILD->GetBuildVector()) {
			if (buildPtr->GetCollision()->Intersect(pl->GetFoot())) {
				pl->GoBack();
			}
		}
	}

	// 몬스터 관련 동작
	for (auto MonPtr : MONSTER->GetMonsterVector())
	{
		// 몬스터가 벽이랑 충돌했을때
		if (map->GetTileState(MonPtr->GetCol()->GetWorldPos()) == TILE_WALL) {
			MonPtr->GoBack();
		}
		// 몬스터가 벽이랑 관련 동작
		for (auto buildPtr : BUILD->GetBuildVector()) {
			// 건물과 몬스터가 충돌했을때
			if (buildPtr->GetCollision()->Intersect(MonPtr->GetCol())) {
				//MonPtr->GoBack();
				Vector2 enemyDir = MonPtr->GetPos() - buildPtr->GetCollision()->GetWorldPivot();
				enemyDir.Normalize();

				MonPtr->GetCol()->MoveWorldPos(enemyDir * 250 * DELTA);
			}
			// 몬스터의 총알이 벽이랑 충돌했을때
			for (auto MbulletPtr : MonPtr->bullet) {
				if (MbulletPtr->Intersect(buildPtr->GetCollision())) {
					int result = MonPtr->Atk < pl->GetStatus().Defense ? 0 : MonPtr->Atk - pl->GetStatus().Defense;
					buildPtr->GetHpbar()->Damage(result, 0);
					MbulletPtr->Release();
				}
			}
		}

		//플레이어의 공격
		for (auto bulletPtr : pl->GetBulletVector()) {
			if (bulletPtr->Intersect(MonPtr->GetCol())) {
				MonPtr->hp->Damage(pl->GetStatus().Attack, UI->Element_idx);
				bulletPtr->Release();
			}
		}

		//몬스터의 공격
		for (auto MbulletPtr : MonPtr->bullet) {
			if (MbulletPtr->Intersect(pl)) {
				int result = MonPtr->Atk < pl->GetStatus().Defense ? 0 : MonPtr->Atk - pl->GetStatus().Defense;
				UI->Damage(result, pl->GetWorldPos(), 0);
				MbulletPtr->Release();
			}
		}
	}

	// 공격타워 - 몬스터 충돌
	for (auto buildPtr : BUILD->GetBuildVector())
	{
		AttackTower* AttackPtr = dynamic_cast<AttackTower*>(buildPtr);
		if (AttackPtr == nullptr) continue;
		for (auto MonPtr : MONSTER->GetMonsterVector())
		{
			for (auto TowerBulletPtr : AttackPtr->GetBulletVector()) {
				if (TowerBulletPtr->Intersect(MonPtr->GetCol())) {
					MonPtr->hp->Damage(pl->GetStatus().Attack, UI->Element_idx);
					TowerBulletPtr->Release();
					break;
				}
			}
		}
	}

	// 공격타워 - 몬스터 감치 총알발사
	for (auto buildPtr : BUILD->GetBuildVector()) {
		AttackTower* AttackPtr = dynamic_cast<AttackTower*>(buildPtr);
		if (AttackPtr == nullptr) continue;

		for (auto MonPtr : MONSTER->GetMonsterVector()) {
			if (AttackPtr->GetInteractionRect()->Intersect(MonPtr->GetCol())) {
				// 타워가 몬스터를 인식하여 동작을 수행하는 부분
				AttackPtr->GetTargetPos(MonPtr->GetPos());

				// 몬스터의 방향을 기준으로 타워 이미지 프레임을 설정
				int index = round((Utility::DirToRadian(MonPtr->GetPos() - AttackPtr->GetWorldPivot()) + PI) / (22.5f * ToRadian));
				AttackPtr->SetImageFreamY(index);

				// 일정 시간마다 타워가 총알 발사하는 부분
				if (TIMER->GetTick(AttackPtr->timer, AttackPtr->as)) {
					int soundNum = RANDOM->Int(1, 5);
					switch (soundNum)
					{
					case 1:SOUND->Stop("GunFire1"); SOUND->Play("GunFire1"); break;
					case 2:SOUND->Stop("GunFire2"); SOUND->Play("GunFire2"); break;
					case 3:SOUND->Stop("GunFire3"); SOUND->Play("GunFire3"); break;
					case 4:SOUND->Stop("GunFire4"); SOUND->Play("GunFire4"); break;
					case 5:SOUND->Stop("GunFire5"); SOUND->Play("GunFire5"); break;
					}



					Bullet* B = new Bullet();
					Vector2 dir = Vector2(MonPtr->GetPos() - AttackPtr->GetWorldPivot());
					dir.Normalize();
					B->Fire(AttackPtr->GetWorldPivot(), dir, 300);
					AttackPtr->bullet.push_back(B);
				}

				// 하나의 몬스터에 대한 동작이 처리되었으므로 다음 몬스터로 이동
				break;
			}
		}
	}


	const int maxExpChange = 10; // 경험치 획득량 증가 제한 값
	if (MONSTER->giveExp > 0) {
		// 실제로 획득할 수 있는 경험치 계산
		int expToGain = min(MONSTER->giveExp, maxExpChange);

		// 현재 경험치와 목표 경험치를 계산합니다.
		int targetExp = UI->CurExp + expToGain;

		// 몬스터로부터 받은 경험치를 감소시킵니다.
		MONSTER->giveExp -= expToGain;
		UI->CurExp = targetExp;

	}

	pl->LateUpdate();
	MONSTER->LateUpdate();
	DAMAGE->LateUpdate();
	BUILD->LateUpdate();
}

void Scene1::Render()
{
	DWRITE->PosRenderText(to_wstring((int)TIMER->GetFramePerSecond()), Vector2(app.GetWidth() - 40, 0), 40);

	map->Render();

	BUILD->Render();

	MONSTER->Render();

	pl->Render();
	MONSTER->HpRender();

	pl->EffectRender();

	UI->Render(cam);

	DAMAGE->Render();

	for (auto buildPtr : BUILD->GetBuildVector()) {
		if (buildPtr->GetCollision()->Intersect(INPUT->GetWorldMousePos()))
		{
			wstring wstr = to_wstring((int)buildPtr->GetHpbar()->CurHp) + L" / " + to_wstring((int)buildPtr->GetHpbar()->MaxHp);
			Vector2 pos = GetAdjustedPosition(buildPtr->GetWorldPivot()) - Vector2(wstr.size() * 5, 10);
			DWRITE->PosRenderText(wstr, pos, 20);
		}
		else {
			continue;
		}

	}
}

void Scene1::ResizeScreen()
{
	UI->Init(UI->Scale);
}
