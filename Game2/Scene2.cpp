#include "stdafx.h"
#include "ProgressBar.h"
#include "PlayerUI.h"
#include "Scene2.h"

extern void CheckSurroundingTiles(ObTileMap* map, Int2 centerIdx, Int2 tileSize, int FindLength = 1);
extern bool CheckTilesWithinDistance(ObTileMap* map, Int2 centerIdx, Int2 tileSize, int FindLength = 1);
extern void RepaintTile(ObTileMap* map, Int2 centerIdx, int FindLength = 1, int Type = 0, Color Color = class Color());
extern void TileCheckLogic(ObTileMap* map, Int2 currentIdx);
extern void DetectTiles(ObTileMap* map, Int2 tileSize, int type, int recursionDepth = 0);


mutex m2;
bool isThreadRunning = false;

float Timer;
float EndTimer;



void MakeTile(ObTileMap* map, Int2 tileSize, Vector2 Scale) {
	isThreadRunning = true;
	map->file = "TileMap_1.txt";
	map->tileImages[1]->file = L"TileMap_2.png";

	Int2 tileSizeIdx = Int2(tileSize.x - 1, tileSize.y - 1);
	map->ResizeTile(tileSize);

	map->scale = Scale;
	Vector2 pos(-(tileSize.x * map->scale.x) / 2, -(tileSize.y * map->scale.y) / 2);
	map->SetWorldPos(pos);
	map->CreateTileCost();

	// 카메라 줌 계산
	//float cameraZoomX = app.GetWidth() / static_cast<float>(tileSize.x * Scale.x);
	//float cameraZoomY = app.GetHeight() / static_cast<float>(tileSize.y * Scale.y);
	//CAM->scale.x = cameraZoomY - 0.02;
	//CAM->scale.y = cameraZoomY - 0.02;
	m2.lock();
	// 맵 타일 초기화 
	for (int i = 0; i < tileSize.y; i++) {
		for (int j = 0; j < tileSize.x; j++) {
			Int2 Idx(i, j);
			float C = (255.f / 20.f) * RANDOM->Int(3, 8) / 255.f * 0.5f;
			Color color = Color(C, C, C, 0.5f);
			map->SetTile2(Idx, Int2(), 1, 0, color);
		}
	}
	m2.unlock();

	// 맵에 벽 추가
	for (int i = 0; i < tileSize.y; i++)
	{
		for (int j = 0; j < tileSize.x; j++)
		{
			// 벽 색상
			float C = (255.f / 20.f) * RANDOM->Int(3, 8) / 255.f * 0.5f;
			Color color = Color(C, C, C, 0.5f);
			// 테두리
			if (i == 0 or j == 0 or j == tileSizeIdx.x or i == tileSizeIdx.y or
				i == 1 or j == 1 or j == tileSizeIdx.x - 1 or i == tileSizeIdx.y - 1) {
				map->SetTile2(Int2(i, j), Int2(), 1, 1, color);
			}
			Int2 Idx(RANDOM->Int(2, tileSizeIdx.y - 2), RANDOM->Int(2, tileSizeIdx.y - 2));
			int Num = RANDOM->Int(0, 1);
			if (Num != 0) {
				int C = RANDOM->Int(50, 150);
				map->SetTile2(Idx, Int2(), 1, 1, color);
			}
		}
	}

	for (int k = 0; k < 4; k++) {
		DetectTiles(map, tileSize, 1, 0);

		// 맵에서 타일 검색
		for (int i = 0; i < tileSize.y; i++)
		{
			for (int j = 0; j < tileSize.x; j++)
			{
				CheckSurroundingTiles(map, Int2(i, j), tileSize);
			}
		}

		// 탐색된 타일 벽으로 전환
		for (int i = 0; i < tileSize.y; i++)
		{
			for (int j = 0; j < tileSize.x; j++)
			{
				// 벽 색상
				float C = (255.f / 20.f) * RANDOM->Int(3, 8) / 255.f * 0.5f;
				Color color = Color(C, C, C, 0.5f);
				if (map->GetTileState(Int2(i, j)) != TILE_NONE)
				{
					map->SetTile2(Int2(i, j), Int2(), 1, 1, color);
				}
			}
		}
	}

	for (int k = 0; k < 2; k++) {

		DetectTiles(map, tileSize, 1, 0);

		// 탐색되지않은 타일 벽으로 전환
		for (int i = 0; i < tileSize.y; i++)
		{
			for (int j = 0; j < tileSize.x; j++)
			{
				if (map->GetTileState(Int2(i, j)) == TILE_NONE) {
					float C = (255.f / 20.f) * RANDOM->Int(3, 8) / 255.f * 0.5f;
					Color color = Color(C, C, C, 0.5f);

					map->SetTile2(Int2(i, j), Int2(), 1, 1, color);
				}
			}
		}

		// 탐색된 타일들 타일로 전환
		for (int i = 0; i < tileSize.y; i++)
		{
			for (int j = 0; j < tileSize.x; j++)
			{
				if (map->GetTileState(Int2(i, j)) == TILE_FINDING) {
					float C = (255.f / 20.f) * RANDOM->Int(3, 8) / 255.f * 0.5f;
					Color color = Color(C, C, C, 0.5f);
					map->SetTile2(Int2(i, j), Int2(), 1, 0, color);
				}
			}
		}
	}

	// 맵에 벽 추가
	for (int i = 0; i < tileSize.y; i++)
	{
		for (int j = 0; j < tileSize.x; j++)
		{
			// 벽 색상
			float C = (255.f / 20.f) * RANDOM->Int(3, 8) / 255.f * 0.5f;
			Color color = Color(C, C, C, 0.5f);
			// 테두리
			if (i == 0 or j == 0 or j == tileSizeIdx.x or i == tileSizeIdx.y or
				i == 1 or j == 1 or j == tileSizeIdx.x - 1 or i == tileSizeIdx.y - 1) {
				map->SetTile2(Int2(i, j), Int2(), 1, 1, color);
			}
		}
	}

	for (int k = 0; k < 30; k++) {
		int idx(RANDOM->Int(3, 13));
		Int2 Idx(RANDOM->Int(0, tileSize.y - 1), RANDOM->Int(0, tileSize.y - 1));
		Vector2 diam = map->scale;
		Vector2 centerPos = Vector2(Idx.x * diam.x + diam.x / 2, Idx.y * diam.y + diam.x / 2);

		for (int y = Idx.y - idx; y <= Idx.y + idx; y++) {
			for (int x = Idx.x - idx; x <= Idx.x + idx; x++) {
				if (y >= 0 && y < tileSize.y && x >= 0 && x < tileSize.x) {
					Int2 currentIdx(x, y);
					Vector2 tilePos = Vector2(currentIdx.x * diam.x + diam.x / 2, currentIdx.y * diam.y + diam.x / 2);
					float distance = (centerPos - tilePos).Length();

					float C = (255.f / 20.f) * RANDOM->Int(3, 8) / 255.f * 0.5f;
					Color color = Color(C, C, C, 0.5f);

					if (distance < (idx - 2) * diam.x + diam.x / 2 && map->GetTileState(currentIdx) != TILE_WALL) {
						map->SetTile2(currentIdx, Int2(), 1, 3, color);
					}
				}
			}
		}
	}

	map->UpdateSub();
	isThreadRunning = false;

	map->Save();
}

void CreateTile(ObTileMap* map, Int2 tileSize, Vector2 Scale) {
	//스레드 시작
	isThreadRunning = true;

	//가상의 2차원 타일 배열 생성코드
	int** instance = new int* [tileSize.y];
	for (int i = 0; i < tileSize.y; i++) {
		instance[i] = new int[tileSize.x];
		for (int j = 0; j < tileSize.x; j++) {
			// 0으로 초기화
			instance[i][j] = 0;
		}
	}

	// 랜덤함수를 이용하여 타일에 값 할당
	for (int i = 0; i < tileSize.y; i++) {
		for (int j = 0; j < tileSize.x; j++) {
			instance[i][j] = RANDOM->Int(0, 1);
		}
	}

	// 셀룰러 오토마타를 이용한 맵 생성 규칙 설정
	for (int k = 0; k < 3; k++) {
		for (int i = 0; i < tileSize.y; i++) {
			for (int j = 0; j < tileSize.x; j++) {
				int FindLength = 1;
				int FindWallCount = 0;
				int FindNoneCount = 0;
				for (int y = i - FindLength; y <= i + FindLength; y++) {
					for (int x = j - FindLength; x <= j + FindLength; x++) {
						if (y >= 0 && y < tileSize.y && x >= 0 && x < tileSize.x) {
							if (instance[x][y] == 0)
								FindWallCount++;
							else {
								FindNoneCount++;
							}
						}
						else {
							FindWallCount = 9;
						}
					}
				}
				if (FindWallCount > 6) {
					instance[i][j] = 0;
				}
				else if (FindNoneCount > 5) {
					instance[i][j] = 1;
				}
			}
		}
		for (int i = 0; i < tileSize.y; i++) {
			for (int j = 0; j < tileSize.x; j++) {
				if (instance[i][j] == 2) {
					instance[i][j] = 0;
				}
			}
		}
	}


	auto bfsLambda = [&tileSize, &instance](int i, int j) {
		vector<vector<bool>> visited(tileSize.y, std::vector<bool>(tileSize.x, false));
		vector<Int2> BigTiles;
		visited[i][j] = false;

		Int2 sour(j, i);
		// BFS를 이용하여 탐색
		std::queue<Int2> q;
		q.push(sour);
		BigTiles.push_back(q.front());
		const int dx[] = { -1, 0, 0, 1, };
		const int dy[] = { 0, -1, 1,  0, };
		while (!q.empty()) {
			Int2 current = q.front();
			q.pop();
			for (int i = 0; i < 4; i++) {
				Int2 next(current.x + dx[i], current.y + dy[i]);
				// 이동한 위치가 타일 맵 내에 있고, 아직 검사하지 않은 타일인 경우
				if ((next.x >= 0 && next.y >= 0 && next.x < tileSize.x && next.y < tileSize.y) &&
					!visited[next.x][next.y] && instance[next.x][next.y] == 1) {
					q.push(next);
					BigTiles.push_back(next);
					visited[next.x][next.y] = true;
				}
			}
		}
		return BigTiles;
	};

	int count = 0;
	int FindLength = 2; // 1 = 3 , 2 = 5 , 3 = 7, 4 = 9
	Int2 Rpos;
	do {
		count = 0;
		Int2 randNum = Int2(RANDOM->Int(0, tileSize.x), RANDOM->Int(0, tileSize.y));
		for (int y = randNum.y - FindLength; y <= randNum.y + FindLength; y++) {
			for (int x = randNum.x - FindLength; x <= randNum.x + FindLength; x++) {
				if (instance[y][x] == 1) {
					count++;
				}
			}
		}
		Rpos = randNum;
	} while (long(count + 1) == pow(FindLength + 1, 2));

	auto bigTile = bfsLambda(Rpos.y, Rpos.x);

	for (auto idx : bigTile) {
		instance[idx.y][idx.x] = 2;
	}

	for (int i = 0; i < tileSize.y; i++) {
		for (int j = 0; j < tileSize.x; j++) {
			if (instance[i][j] < 2) {
				instance[i][j] = 0;
			}
		}
	}

	map->file = "TileMap_1.txt";
	map->tileImages[1]->file = L"tile-1.png";
	map->tileImages[2]->file = L"tile-2.png";

	Int2 tileSizeIdx = Int2(tileSize.x - 1, tileSize.y - 1);
	map->ResizeTile(tileSize);

	map->scale = Scale;
	Vector2 pos(-(tileSize.x * map->scale.x) / 2, -(tileSize.y * map->scale.y) / 2);
	map->SetWorldPos(pos);
	map->CreateTileCost();


	for (int i = 0; i < tileSize.y; i++) {
		for (int j = 0; j < tileSize.x; j++) {
			Int2 Idx(i, j);
			Color color = Color(0.5, 0.5, 0.5, 0.5f);
			if (instance[i][j] == 2) {
				map->SetTile2(Idx, Int2(), 1, 0);
			}
			else {
				map->SetTile2(Idx, Int2(), 2, 1);
			}

		}
	}

	/*cout << "======================" << endl;
	for (int i = 0; i < tileSize.y; i++) {
		for (int j = 0; j < tileSize.x; j++) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			if (instance[i][j] == 1) {
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				cout << "P";
				SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else if (instance[i][j] == 2) {
				SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
				cout << "E";
				SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			}
			else {
				cout << "X";
			}
		}
		cout << endl;
	}
	cout << "======================" << endl;*/



	for (int i = 0; i < tileSize.y; i++)
	{
		delete[] instance[i];
	}
	delete[] instance;
	isThreadRunning = false;
}

Scene2::Scene2()
{
	//CAM->scale = Vector2(0.5, 0.5);

	Loading = new ObImage(L"Loading.png");
	Loading->maxFrame.x = 13;
	Loading->scale.x = Loading->imageSize.x / Loading->maxFrame.x * 3;
	Loading->scale.y = Loading->imageSize.y * 3;

	Loading->ChangeAnim(ANIMSTATE::ONCE, 0.1);

	map = new ObTileMap;
	tileSize = Int2(100, 100);

	//test1 = new thread(MakeTile, map, tileSize, Vector2(100, 100));
	test1 = new thread(CreateTile, map, tileSize, Vector2(100, 100));
}

Scene2::~Scene2() {
	//delete Loading;
	//TEXTURE->DeleteTexture(L"Loading.png");
}

void Scene2::Init() {}
void Scene2::Release() {}
void Scene2::Update()
{
	Timer += DELTA;
	if (!Loading->isAniStop()) {
		Loading->Update();
	}
	if (!isThreadRunning && Loading->isAniStop()) {
		map->Save();

		SCENE->ChangeScene("SC1");
		SCENE->DeleteScene("SC2");
		cout << "신2 삭제" << endl;
	}

}
void Scene2::LateUpdate() {}

void Scene2::Render() {
	if (!Loading->isAniStop())
		Loading->Render();
}

void Scene2::ResizeScreen()
{
	CAM->ResizeScreen();
}


