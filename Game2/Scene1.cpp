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
					
					cout << "�ߺ��� �ǹ� ��ǥ" << endl;
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
	const int maxAttempts = 1000; // �ִ� �õ� Ƚ��

	for (int attempt = 0; attempt < maxAttempts; ++attempt) {
		// ������ ��ǥ ����
		Int2 Pos(RANDOM->Int(1, map->GetTileSize().x - 1), RANDOM->Int(1, map->GetTileSize().y - 1));

		// ������ ��ǥ�� �� ���� �ִ��� Ȯ��
		if (map->IsInMap(Pos)) {
			bool isAllNonWall = true; // �ֺ� ��� Ÿ���� ���� �ƴ��� Ȯ���ϱ� ���� �÷���
			// �ֺ� 3x3 ������ ��ȸ�ϸ� Ÿ�� ���� Ȯ��
			for (int y = Pos.y - 1; y <= Pos.y + 1; y++) {
				for (int x = Pos.x - 1; x <= Pos.x + 1; x++) {
					// �ε����� �� ���� ���� �ִ��� Ȯ��
					if (y >= 0 && y < map->GetTileSize().y && x >= 0 && x < map->GetTileSize().x) {
						Int2 currentIdx(x, y);

						// ���� Ÿ���� ������ Ȯ���Ͽ� isAllNonWall ������Ʈ
						if (map->GetTileState(currentIdx) == TILE_WALL) {
							isAllNonWall = false;
							break; // ���� �ϳ��� ������ �� �̻� Ȯ���� �ʿ� ����
						}
					}
				}
				if (!isAllNonWall) {
					break; // ���� �ϳ��� ������ �� �̻� Ȯ���� �ʿ� ����
				}
			}
			// �ֺ��� ��� Ÿ���� ���� �ƴ� ��� ������ ��ġ�� �����ϰ� ����
			if (isAllNonWall) {
				Position = Vector2(Pos.x * map->scale.x + map->scale.x / 2, Pos.y * map->scale.y + map->scale.y / 2);
				return;
			}
		}
	}
	// ���� ������ ��ġ�� ã�� ���ߴٸ� Position�� �ʱ�ȭ�ϰų� Ư�� �⺻ ������ ������ �� �ֽ��ϴ�.
	Position = Vector2(); // ���÷� Position�� �ʱ�ȭ�մϴ�.
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

	//UI����� ī�޶� ��
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










	// ���� ��ȯ
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



	// �ӽ÷� ���� �ǹ� Ÿ�Ժ���
	if (INPUT->KeyDown('1')) {
		buildType = 0;
	}
	if (INPUT->KeyDown('2')) {
		buildType = 1;
	}
	if (INPUT->KeyDown('3')) {
		buildType = 2;
	}


	// ��Ŭ���� �ǹ�����
	if (INPUT->KeyDown(VK_RBUTTON)) {
		Int2 Idx;
		map->WorldPosToTileIdx(INPUT->GetWorldMousePos(), Idx);
		Vector2 Pos(Idx.x * map->GetTileSize().x, Idx.y * map->GetTileSize().y);
		bool isDuplicate = false;
		for (auto buildPtr : BUILD->GetBuildVector()) {
			if (Pos == buildPtr->GetWorldPos()) {
				SOUND->Stop("BuildError");
				SOUND->Play("BuildError");
				cout << "�ߺ��� �ǹ� ��ǥ" << endl;
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


	// �÷��̾� �浹 ����
	{
		// �÷��̾ ���� �ı��Ҷ� 
		Int2 Idx;
		map->WorldPosToTileIdx(pl->GetWorldPos(), Idx);
		// �� ��� ������ Ÿ�Ͽ� ���ؼ��� �˻�
		if (Idx.x > 2 && Idx.y > 2 && Idx.x < map->GetTileSize().x - 3 && Idx.y < map->GetTileSize().y - 3) {
			for (int y = -1; y <= 1; y++) {
				for (int x = -1; x <= 1; x++) {
					Int2 Tpos(Idx.x + x, Idx.y + y);
					// Ÿ�� �ε����� ��ȿ���� Ȯ��
					if (Tpos.x >= 0 && Tpos.x < map->GetTileSize().x && Tpos.y >= 0 && Tpos.y < map->GetTileSize().y) {
						// ���� Ÿ�ϸ� ó��
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
		// ���̶� �浹������
		if (map->GetTileState(pl->GetFoot()) == TILE_WALL)
		{
			pl->GoBack();
		}

		// �ǹ��̶� �浹������
		for (auto buildPtr : BUILD->GetBuildVector()) {
			if (buildPtr->GetCollision()->Intersect(pl->GetFoot())) {
				pl->GoBack();
			}
		}
	}

	// ���� ���� ����
	for (auto MonPtr : MONSTER->GetMonsterVector())
	{
		// ���Ͱ� ���̶� �浹������
		if (map->GetTileState(MonPtr->GetCol()->GetWorldPos()) == TILE_WALL) {
			MonPtr->GoBack();
		}
		// ���Ͱ� ���̶� ���� ����
		for (auto buildPtr : BUILD->GetBuildVector()) {
			// �ǹ��� ���Ͱ� �浹������
			if (buildPtr->GetCollision()->Intersect(MonPtr->GetCol())) {
				//MonPtr->GoBack();
				Vector2 enemyDir = MonPtr->GetPos() - buildPtr->GetCollision()->GetWorldPivot();
				enemyDir.Normalize();

				MonPtr->GetCol()->MoveWorldPos(enemyDir * 250 * DELTA);
			}
			// ������ �Ѿ��� ���̶� �浹������
			for (auto MbulletPtr : MonPtr->bullet) {
				if (MbulletPtr->Intersect(buildPtr->GetCollision())) {
					int result = MonPtr->Atk < pl->GetStatus().Defense ? 0 : MonPtr->Atk - pl->GetStatus().Defense;
					buildPtr->GetHpbar()->Damage(result, 0);
					MbulletPtr->Release();
				}
			}
		}

		//�÷��̾��� ����
		for (auto bulletPtr : pl->GetBulletVector()) {
			if (bulletPtr->Intersect(MonPtr->GetCol())) {
				MonPtr->hp->Damage(pl->GetStatus().Attack, UI->Element_idx);
				bulletPtr->Release();
			}
		}

		//������ ����
		for (auto MbulletPtr : MonPtr->bullet) {
			if (MbulletPtr->Intersect(pl)) {
				int result = MonPtr->Atk < pl->GetStatus().Defense ? 0 : MonPtr->Atk - pl->GetStatus().Defense;
				UI->Damage(result, pl->GetWorldPos(), 0);
				MbulletPtr->Release();
			}
		}
	}

	// ����Ÿ�� - ���� �浹
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

	// ����Ÿ�� - ���� ��ġ �Ѿ˹߻�
	for (auto buildPtr : BUILD->GetBuildVector()) {
		AttackTower* AttackPtr = dynamic_cast<AttackTower*>(buildPtr);
		if (AttackPtr == nullptr) continue;

		for (auto MonPtr : MONSTER->GetMonsterVector()) {
			if (AttackPtr->GetInteractionRect()->Intersect(MonPtr->GetCol())) {
				// Ÿ���� ���͸� �ν��Ͽ� ������ �����ϴ� �κ�
				AttackPtr->GetTargetPos(MonPtr->GetPos());

				// ������ ������ �������� Ÿ�� �̹��� �������� ����
				int index = round((Utility::DirToRadian(MonPtr->GetPos() - AttackPtr->GetWorldPivot()) + PI) / (22.5f * ToRadian));
				AttackPtr->SetImageFreamY(index);

				// ���� �ð����� Ÿ���� �Ѿ� �߻��ϴ� �κ�
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

				// �ϳ��� ���Ϳ� ���� ������ ó���Ǿ����Ƿ� ���� ���ͷ� �̵�
				break;
			}
		}
	}


	const int maxExpChange = 10; // ����ġ ȹ�淮 ���� ���� ��
	if (MONSTER->giveExp > 0) {
		// ������ ȹ���� �� �ִ� ����ġ ���
		int expToGain = min(MONSTER->giveExp, maxExpChange);

		// ���� ����ġ�� ��ǥ ����ġ�� ����մϴ�.
		int targetExp = UI->CurExp + expToGain;

		// ���ͷκ��� ���� ����ġ�� ���ҽ�ŵ�ϴ�.
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
