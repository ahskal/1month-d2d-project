#include "stdafx.h"
#include "Main.h"

extern void CheckSurroundingTiles(ObTileMap* map, Int2 centerIdx, Int2 tileSize, int FindLength = 1);
extern bool CheckTilesWithinDistance(ObTileMap* map, Int2 centerIdx, Int2 tileSize, int FindLength = 1);
extern void RepaintTile(ObTileMap* map, Int2 centerIdx, int FindLength = 1, int Type = 0, Color Color = class Color());
extern void TileCheckLogic(ObTileMap* map, Int2 currentIdx);
extern void DetectTiles(ObTileMap* map, Int2 tileSize, int type, int recursionDepth = 0);

void InitializeTileMap(ObTileMap& map, Int2& tileSize) {
	map.file = "TileMap_1.txt";
	map.tileImages[1]->file = L"TileMap_2.png";

	Int2 tileSizeIdx = Int2(tileSize.x - 1, tileSize.y - 1);
	map.ResizeTile(tileSize);
	Vector2 Scale = Vector2(100, 100);
	map.scale = Scale;
	Vector2 pos(-(tileSize.x * map.scale.x) / 2, -(tileSize.y * map.scale.y) / 2);
	map.SetWorldPos(pos);

	map.CreateTileCost();

	CAM->scale.x = 0.05;
	CAM->scale.y = 0.05;

}
void FillTilesWithRandomColors(ObTileMap* map, Int2 tileSize) {
	for (int i = 0; i < tileSize.y; i++) {
		for (int j = 0; j < tileSize.x; j++) {
			Int2 Idx(i, j);
			float C = (255.f / 20.f) * RANDOM->Int(3, 8) / 255.f * 0.5f;
			Color color = Color(C, C, C, 0.5f);
			map->SetTile(Idx, Int2(), 1, 0, color);
		}
	}
	map->Save();
}
void AddWallsToTileMap(ObTileMap* map, Int2 tileSize) {
	Int2 tileSizeIdx = Int2(tileSize.x - 1, tileSize.y - 1);
	for (int i = 0; i < tileSize.y; i++)
	{
		for (int j = 0; j < tileSize.x; j++)
		{
			// 벽 색상
			float C = 25.f * RANDOM->Int(1, 8) / 255.f * 0.5f;
			Color color = Color(C, C, C, 0.5f);
			// 테두리
			if (i == 0 or j == 0 or j == tileSizeIdx.x or i == tileSizeIdx.y or
				i == 1 or j == 1 or j == tileSizeIdx.x - 1 or i == tileSizeIdx.y - 1) {
				map->SetTile(Int2(i, j), Int2(), 1, 1, color);
			}
			Int2 Idx(RANDOM->Int(2, tileSizeIdx.y - 2), RANDOM->Int(2, tileSizeIdx.y - 2));
			int Num = RANDOM->Int(0, 1);
			if (Num != 0) {
				int C = RANDOM->Int(50, 150);
				map->SetTile(Idx, Int2(), 1, 1, color);
			}
		}
	}
	map->Save();
}
void FillGroundTiles(ObTileMap* map, Int2 tileSize) {
	// 땅 채원걸로 화면 정렬
	for (int i = 0; i < tileSize.y; i++)
	{
		for (int j = 0; j < tileSize.x; j++)
		{
			CheckSurroundingTiles(map, Int2(i, j), tileSize);
		}
	}
	map->Save();
}
void ConvertDetectedTilesToWalls(ObTileMap* map, Int2 tileSize)
{
	// 탐색된 타일 벽으로 전환
	for (int i = 0; i < tileSize.y; i++)
	{
		for (int j = 0; j < tileSize.x; j++)
		{
			// 벽 색상
			float C = 25.f * RANDOM->Int(1, 8) / 255.f * 0.5f;
			Color color = Color(C, C, C, 0.5f);
			if (map->GetTileState(Int2(i, j)) != TILE_NONE)
			{
				map->SetTile(Int2(i, j), Int2(), 1, 1, color);
			}
		}
	}
	map->Save();
}
void FillNonWallTilesWithRandomColor(ObTileMap* map, Int2 tileSize) {
	// 탐색되지않은 타일 벽으로 전환
	for (int i = 0; i < tileSize.y; i++)
	{
		for (int j = 0; j < tileSize.x; j++)
		{
			if (map->GetTileState(Int2(i, j)) == TILE_NONE) {
				float C = 25.f * RANDOM->Int(1, 8) / 255.f * 0.5f;
				Color color = Color(C, C, C, 0.5f);
				map->SetTile(Int2(i, j), Int2(), 1, 1, color);
			}
		}
	}
	map->Save();
}
void FillFoundTilesWithRandomColor(ObTileMap* map, Int2 tileSize) {
	// 탐색된 타일들 타일로 전환
	for (int i = 0; i < tileSize.y; i++)
	{
		for (int j = 0; j < tileSize.x; j++)
		{
			if (map->GetTileState(Int2(i, j)) == TILE_FINDING) {
				float C = (255.f / 20.f) * RANDOM->Int(3, 8) / 255.f * 0.5f;
				Color color = Color(C, C, C, 0.5f);
				map->SetTile(Int2(i, j), Int2(), 1, 0, color);
			}
		}
	}
	map->Save();
}
void FillSurroundingTiles(ObTileMap* map, Int2 tileSize, int radius) {
	Int2 Idx(RANDOM->Int(0, tileSize.y - 1), RANDOM->Int(0, tileSize.y - 1));
	Vector2 diam = map->scale;
	Vector2 centerPos = Vector2(Idx.x * diam.x + diam.x / 2, Idx.y * diam.y + diam.x / 2);

	for (int y = Idx.y - radius; y <= Idx.y + radius; y++) {
		for (int x = Idx.x - radius; x <= Idx.x + radius; x++) {
			if (y >= 0 && y < tileSize.y && x >= 0 && x < tileSize.x) {
				Int2 currentIdx(x, y);
				Vector2 tilePos = Vector2(currentIdx.x * diam.x + diam.x / 2, currentIdx.y * diam.y + diam.x / 2);
				float distance = (centerPos - tilePos).Length();

				float C = 25.f * RANDOM->Int(1, 8) / 255.f * 0.5f;
				Color color = Color(C, C, C, 0.5f);

				if (distance < (radius - 2) * diam.x + diam.x / 2 && map->GetTileState(currentIdx) != TILE_WALL) {
					map->SetTile(currentIdx, Int2(), 1, 3, color);
				}
			}
		}
	}
	map->Save();
}


void TileMake() {

	{
		//for (int i = 0; i < tileSize.y - 1; i++)
		//{
		//	for (int j = 0; j < tileSize.x - 1; j++)
		//	{
		//		Int2 Idx = Int2(i, j);
		//		map->SetTile(Idx, Int2(), 1, 0, Color(
		//			150 / 255.f * 0.5f,
		//			230 / 255.f * 0.5f,
		//			30 / 255.f * 0.5f,
		//			0.5f
		//		));
		//	}
		//}

		//// 타일 바닥 생성 
		//for (int i = 0; i < tileSize.y - 1; i++)
		//{
		//	for (int j = 0; j < tileSize.x - 1; j++)
		//	{
		//		Int2 Idx = Int2(i, j);
		//		// 지형 색상
		//		Color color = Color(
		//			RANDOM->Int(102, 153) / 255.f * 0.5f,
		//			RANDOM->Int(204, 255) / 255.f * 0.5f,
		//			RANDOM->Int(051, 051) / 255.f * 0.5f,
		//			0.5f);
		//		map->SetTile(Idx, Int2(), 1, 0, color);
		//	}
		//}

		//// 벽 생성
		//for (int i = 0; i < tileSize.y - 1; i++)
		//{
		//	for (int j = 0; j < tileSize.x - 1; j++)
		//	{
		//		// 벽 색상
		//		Color color = Color(
		//			RANDOM->Int(051, 204) / 255.f * 0.5f,
		//			RANDOM->Int(102, 204) / 255.f * 0.5f,
		//			RANDOM->Int(051, 204) / 255.f * 0.5f,
		//			0.5f);
		//		// 테두리
		//		if ((i == 0 || j == 0 || j == tileSize.x - 2 || i == tileSize.y - 2) ||
		//			(i == 1 || j == 1 || j == tileSize.x - 3 || i == tileSize.y - 3))
		//		{
		//			map->SetTile(Int2(j, i), Int2(), 1, 1, color);
		//		}
		//		Int2 Idx(RANDOM->Int(2, tileSize.y - 3), RANDOM->Int(2, tileSize.y - 3));
		//		int Num = RANDOM->Int(0, 1);
		//		if (Num != 0) {
		//			int C = RANDOM->Int(50, 150);
		//			map->SetTile(Idx, Int2(), 1, 1, color);
		//		}
		//	}
		//}

		//for (int k = 0; k < 4; k++) {
		//	// 탐색한 타일 채우기
		//	//DetectTiles(map, tileSize, 1);
		//	// 
		//	for (int i = 0; i < 100; i++) {
		//		Int2 Idx2(RANDOM->Int(2, tileSize.y - 3), RANDOM->Int(2, tileSize.y - 3));
		//		int size = map->FindTilesInRange(Idx2, 1);
		//		if (size > 100) {
		//			return;
		//		}
		//	}
		//	// 땅 채원걸로 화면 정렬
		//	for (int i = 2; i < tileSize.y - 3; i++)
		//	{
		//		for (int j = 2; j < tileSize.x - 3; j++)
		//		{
		//			CheckSurroundingTiles(map, Int2(i, j), tileSize);
		//		}
		//	}
		//	// 탐색된 타일 벽으로 전환
		//	for (int i = 2; i < tileSize.y - 3; i++)
		//	{
		//		for (int j = 2; j < tileSize.x - 3; j++)
		//		{
		//			// 벽 색상
		//			Color color = Color(
		//				RANDOM->Int(051, 204) / 255.f * 0.5f,
		//				RANDOM->Int(102, 204) / 255.f * 0.5f,
		//				RANDOM->Int(051, 204) / 255.f * 0.5f,
		//				0.5f);
		//			if (map->GetTileState(Int2(i, j)) != TILE_NONE)
		//			{
		//				map->SetTile(Int2(i, j), Int2(), 1, 1, color);
		//			}
		//		}
		//	}
		//}

		//// 탐색되지않은 타일 벽으로 전환
		//for (int i = 2; i < tileSize.y - 3; i++)
		//{
		//	for (int j = 2; j < tileSize.x - 3; j++)
		//	{
		//		// 벽 색상
		//		if (map->GetTileState(Int2(i, j)) == TILE_NONE)
		//		{
		//			Color color = Color(
		//				RANDOM->Int(051, 204) / 255.f * 0.5f,
		//				RANDOM->Int(102, 204) / 255.f * 0.5f,
		//				RANDOM->Int(051, 204) / 255.f * 0.5f,
		//				0.5f);
		//			map->SetTile(Int2(i, j), Int2(), 1, 1, color);
		//		}
		//	}
		//}
		//// 탐색된 타일들 타일로 전환
		//for (int i = 2; i < tileSize.y - 3; i++)
		//{
		//	
		//	for (int j = 2; j < tileSize.x - 3; j++)
		//	{
		//		if (map->GetTileState(Int2(i, j)) == TILE_FINDING)
		//		{
		//			Color color = Color(
		//				RANDOM->Int(102, 153) / 255.f * 0.5f,
		//				RANDOM->Int(204, 255) / 255.f * 0.5f,
		//				RANDOM->Int(051, 051) / 255.f * 0.5f,
		//				0.5f);
		//			map->SetTile(Int2(i, j), Int2(), 1, 0, color);
		//		}
		//	}
		//}
		//// 땅 채원걸로 화면 정렬
		//for (int i = 2; i < tileSize.y - 3; i++)
		//{
		//	
		//	for (int j = 2; j < tileSize.x - 3; j++) {
		//		CheckSurroundingTiles(map, Int2(i, j), tileSize);
		//	}
		//}
		// 
		//for (int k = 0; k < 2; k++) {
		//	// 탐색한 타일 채우기
		//	DetectTiles(map, tileSize, 1);
		//	// 탐색되지않은 타일 벽으로 전환
		//	for (int i = 2; i < tileSize.y - 3; i++)
		//	{
		//		for (int j = 2; j < tileSize.x - 3; j++)
		//		{
		//			if (map->GetTileState(Int2(i, j)) == TILE_NONE)
		//				map->SetTile(Int2(i, j), Int2(), 1, 1, WALL_COLOR);
		//		}
		//		// 탐색된 타일들 타일로 전환
		//		for (int j = 2; j < tileSize.x - 3; j++)
		//		{
		//			if (map->GetTileState(Int2(i, j)) == TILE_FINDING)
		//				map->SetTile(Int2(i, j), Int2(), 1, 0, TILE_COLOR);
		//		}
		//		// 땅 채원걸로 화면 정렬
		//		for (int j = 2; j < tileSize.x - 3; j++)
		//		{
		//			CheckSurroundingTiles(map, Int2(i, j), tileSize);
		//		}
		//	}
		//}

		//for (int k = 0; k < 20; k++) {
		//	// 랜덤한 일정 구역 만들기
		//	Int2 Idx(RANDOM->Int(2, tileSize.y - 3), RANDOM->Int(2, tileSize.y - 3));

		//	Vector2 diam = map->scale;
		//	Vector2 Pos = Vector2(Idx.x * diam.x + diam.x / 2, Idx.y * diam.y + diam.x / 2);

		//	for (int y = Idx.y - 10; y <= Idx.y + 10; y++)
		//	{
		//		for (int x = Idx.x - 10; x <= Idx.x + 10; x++)
		//		{
		//			if (y >= 0 && y < tileSize.y && x >= 0 && x < tileSize.x) {
		//				Int2 currentIdx(x, y);
		//				Vector2 tilePos = Vector2(currentIdx.x * diam.x + diam.x / 2, currentIdx.y * diam.y + diam.x / 2);
		//				float distance = (Pos - tilePos).Length();

		//				if (distance < 8 * diam.x + diam.x / 2 && map->GetTileState(currentIdx) != TILE_WALL)
		//				{
		//					map->SetTile(currentIdx, Int2(), 1, 3, Color(RANDOM->Float(0.15, 0.3), 0, 0, 1));
		//				}
		//			}
		//		}
		//	}
		//}
	}



}


Main::Main()
{
	CAM->scale = Vector2(0.5, 0.5);

	map = new ObTileMap;
	tileSize = Int2(110, 110);

	map->file = "TileMap_1.txt";
	InitializeTileMap(*map, tileSize);

	TotalTime = 0;

	for (int i = 0; i < 30; i++) {
		step[i] = true;
	}
	StepCount = 0;



}

Main::~Main()
{
}

void Main::Init(){}

void Main::Release(){}

void Main::Update()
{
	if(StepCount != 41)
	switch (StepCount ) {
	case 0: {
		cout << StepCount << "스레드 시작 " << endl;
		auto startTime = chrono::high_resolution_clock::now();
		test1 = new thread(FillTilesWithRandomColors, map, tileSize);
		test1->join();
		map->Load();
		step[StepCount] = false;
		auto endTime = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
		double elapsed_time = duration.count() / 1000000.0; // 초 단위로 변환
		std::cout << "작업에 걸린 시간: " << elapsed_time << "초" << std::endl;
		cout << "스레드 끝" << endl;
		TotalTime += elapsed_time;
		break;
	}
	case 1: {
		cout << StepCount << "스레드 시작 " << endl;
		auto startTime = chrono::high_resolution_clock::now();
		test1 = new thread(AddWallsToTileMap, map, tileSize);
		test1->join();
		map->Load();
		step[StepCount] = false;
		auto endTime = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
		double elapsed_time = duration.count() / 1000000.0; // 초 단위로 변환
		std::cout << "작업에 걸린 시간: " << elapsed_time << "초" << std::endl;
		cout << "스레드 끝" << endl;
		break;
	}
	case 2: case 5: case 8: case 11: case 14: case 18: {
		cout << StepCount << "스레드 시작 " << endl;
		auto startTime = chrono::high_resolution_clock::now();
		test1 = new thread(DetectTiles, map, tileSize, 1, 0);
		test1->join();
		map->Load();
		step[StepCount] = false;
		auto endTime = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
		double elapsed_time = duration.count() / 1000000.0; // 초 단위로 변환
		std::cout << "작업에 걸린 시간: " << elapsed_time << "초" << std::endl;
		cout << "스레드 끝" << endl;
		TotalTime += elapsed_time;
		break;
	}
	case 3: case 6: case 9: case 12: case 17: {
		cout << StepCount << "스레드 시작 " << endl;
		auto startTime = chrono::high_resolution_clock::now();
		test1 = new thread(FillGroundTiles, map, tileSize);
		test1->join();
		map->Load();
		step[StepCount] = false;
		auto endTime = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
		double elapsed_time = duration.count() / 1000000.0; // 초 단위로 변환
		std::cout << "작업에 걸린 시간: " << elapsed_time << "초" << std::endl;
		cout << "스레드 끝" << endl;
		TotalTime += elapsed_time;
		break;
	}
	case 4: case 7: case 10: case 13: {
		cout << StepCount << "스레드 시작 " << endl;
		auto startTime = chrono::high_resolution_clock::now();
		test1 = new thread(ConvertDetectedTilesToWalls, map, tileSize);
		test1->join();
		map->Load();
		step[StepCount] = false;
		auto endTime = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
		double elapsed_time = duration.count() / 1000000.0; // 초 단위로 변환
		std::cout << "작업에 걸린 시간: " << elapsed_time << "초" << std::endl;
		cout << "스레드 끝" << endl;
		TotalTime += elapsed_time;
		break;
	}
	case 15: case 19: {
		cout << StepCount << "스레드 시작 " << endl;
		auto startTime = chrono::high_resolution_clock::now();
		test1 = new thread(FillNonWallTilesWithRandomColor, map, tileSize);
		test1->join();
		map->Load();
		step[StepCount] = false;
		auto endTime = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
		double elapsed_time = duration.count() / 1000000.0; // 초 단위로 변환
		std::cout << "작업에 걸린 시간: " << elapsed_time << "초" << std::endl;
		cout << "스레드 끝" << endl;
		TotalTime += elapsed_time;
		break;
	}
	case 16: case 20: {
		cout << StepCount << "스레드 시작 " << endl;
		auto startTime = chrono::high_resolution_clock::now();
		test1 = new thread(FillFoundTilesWithRandomColor, map, tileSize);
		test1->join();
		map->Load();
		step[StepCount] = false;
		auto endTime = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
		double elapsed_time = duration.count() / 1000000.0; // 초 단위로 변환
		std::cout << "작업에 걸린 시간: " << elapsed_time << "초" << std::endl;
		cout << "스레드 끝" << endl;
		TotalTime += elapsed_time;
		break;
	}
	default: {
		cout << StepCount << "스레드 시작 " << endl;
		auto startTime = chrono::high_resolution_clock::now();
		test1 = new thread(FillSurroundingTiles, map, tileSize, 9);
		test1->join();
		map->Load();
		step[StepCount] = false;
		auto endTime = chrono::high_resolution_clock::now();
		auto duration = chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
		double elapsed_time = duration.count() / 1000000.0; // 초 단위로 변환
		std::cout << "작업에 걸린 시간: " << elapsed_time << "초" << std::endl;
		cout << "스레드 끝" << endl;
		break;
	}
	}



	if (INPUT->KeyDown('1')) {
		InitializeTileMap(*map, tileSize);

		for (int i = 0; i < 5; i++) {
			step[i] = true;
			StepCount = 0;
		}
		return;
	}
	//if (INPUT->KeyDown('2')) {
	//	TileMake();
	//	map->Load();
	//
	//}
	//cout << a << endl;

	{
		ImGuiIO& io = ImGui::GetIO();

		ImGui::Text("FPS : %d", (int)TIMER->GetFramePerSecond());

		ImGui::Text("CAM Scale %f, %f", CAM->scale.x, CAM->scale.y);
		ImGui::Text("screen Pos %f %f", ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y);
		ImGui::Text("Make Time %f ", TotalTime);
		ImGui::Text("Real Time %f ", TIMER->GetWorldTime());


		ImVec2 mousePos;
		mousePos.x = ImGui::GetIO().MousePos.x * ImVec2(CAM->scale.x, CAM->scale.y).x;
		mousePos.y = ImGui::GetIO().MousePos.y * ImVec2(CAM->scale.x, CAM->scale.y).y;

		// 화면 크기를 얻어옴
		ImVec2 screenSize = ImGui::GetIO().DisplaySize;

		// 마우스 커서가 화면 밖으로 나갔는지 확인
		bool isMouseOutside = (mousePos.x < 0 || mousePos.y < 0 || mousePos.x >= screenSize.x || mousePos.y >= screenSize.y);

		// 마우스가 나갔다 
		if (isMouseOutside or io.WantCaptureMouse)
		{
			isApiScreen = false;
		}
		// 마우스가 들어와있다
		else {
			isApiScreen = true;
		}
		ImGui::Text("screen Pos (%g, %g)", io.MousePos.x, io.MousePos.y);

		if (io.MouseWheel >= 1.0 && isApiScreen) {
			CAM->scale.x -= 0.04f;
			CAM->scale.y -= 0.04f;
		}
		else if (io.MouseWheel <= -1.0 && isApiScreen) {
			CAM->scale.x += 0.04f;
			CAM->scale.y += 0.04f;
		}

		if (CAM->scale.x < -0.0001) {
			CAM->scale *= -1;
		}



	}

	//=================================================================================

	if (INPUT->KeyDown('1'))
	{
		map->Load();
	}

	if (INPUT->KeyPress('W'))
	{
		CAM->position += UP * 3000.0f * DELTA / CAM->scale;
	}
	if (INPUT->KeyPress('S'))
	{
		CAM->position += DOWN * 3000.0f * DELTA / CAM->scale;
	}
	if (INPUT->KeyPress('A'))
	{
		CAM->position += LEFT * 3000.0f * DELTA / CAM->scale;
	}
	if (INPUT->KeyPress('D'))
	{
		CAM->position += RIGHT * 3000.0f * DELTA / CAM->scale;
	}

	// 타일 초기화


	//if (INPUT->KeyDown('2'))
	//{
	//	Int2 Idx(RANDOM->Int(1, tileSize.y - 2), RANDOM->Int(1, tileSize.y - 2));
	//
	//	if (CheckTilesWithinDistance(map, Idx, tileSize, 5) && map->GetTileState(Idx) != TILE_WALL) {
	//		RepaintTile(map, Idx, 5, 0, Color(0, 1, 0, 1));
	//	}
	//	else {
	//		cout << "검색 실패" << endl;
	//	}
	//}
	//
	//if (INPUT->KeyDown('3'))
	//{
	//	Int2 Idx(RANDOM->Int(1, tileSize.y - 2), RANDOM->Int(1, tileSize.y - 2));
	//
	//
	//	Vector2 diam = map->scale;
	//	Vector2 Pos = Vector2(Idx.x * diam.x + diam.x / 2, Idx.y * diam.y + diam.x / 2);
	//
	//	for (int y = Idx.y - 10; y <= Idx.y + 10; y++)
	//	{
	//		for (int x = Idx.x - 10; x <= Idx.x + 10; x++)
	//		{
	//			if (y >= 0 && y < tileSize.y && x >= 0 && x < tileSize.x) {
	//				Int2 currentIdx(x, y);
	//				Vector2 tilePos = Vector2(currentIdx.x * diam.x + diam.x / 2, currentIdx.y * diam.y + diam.x / 2);
	//				float distance = (Pos - tilePos).Length();
	//
	//				if (distance < 8 * diam.x + diam.x / 2 && map->GetTileState(currentIdx) != TILE_WALL)
	//				{
	//					map->SetTile(currentIdx, Int2(), 1, 3, Color(RANDOM->Float(0.15, 0.3), 0, 0, 1));
	//				}
	//			}
	//		}
	//
	//	}
	//}
	//
	////TileSize
	//if (ImGui::SliderInt2("TileSize", (int*)&tileSize, 1, 100))
	//{
	//	for (int i = 0; i < MAXLAYER; i++) {
	//		map[i]->ResizeTile(tileSize);
	//	}
	//}
	//
	//
	////TileScale
	////ImGui::SliderFloat2("TileScale", (float*)&map->scale, 1.0f, 200.0f);
	//if (ImGui::InputFloat("TileScale", (float*)&map->scale.x, 1.0f, 200.0f))
	//{
	//	for (int i = 0; i < MAXLAYER; i++) {
	//		map[i]->scale.y = map[i]->scale.x = map->scale.x;
	//	}
	//}
	//
	//
	////TilePos
	//Vector2 pos = map->GetWorldPos();
	//if (ImGui::SliderFloat2("TilePos", (float*)&pos, -2000.0f, 2000.0f))
	//{
	//	for (int i = 0; i < MAXLAYER; i++) {
	//		map[i]->SetWorldPos(pos);
	//	}
	//}ImGui::SameLine();
	//if (ImGui::Button("ReSet")) {
	//	for (int i = 0; i < MAXLAYER; i++) {
	//		map[i]->SetWorldPosX(0);
	//		map[i]->SetWorldPosY(0);
	//	}
	//}
	//
	//if (ImGui::TreeNode("Textuer Load")) {
	//	for (int j = 0; j < MAXLAYER; j++) {
	//		for (int i = 0; i < 4; i++)
	//		{
	//			string str = "Texture" + to_string(j) + "_" + to_string(i);
	//			if (GUI->FileImGui(str.c_str(), str.c_str(),
	//				".png,.jpg,.bmp,.dds,.tga", "../Contents/Images"))
	//			{
	//				string path = ImGuiFileDialog::Instance()->GetFilePathName();
	//				Utility::Replace(&path, "\\", "/");
	//				size_t tok = path.find_last_of("/") + 1;
	//				path = path.substr(tok, path.length() - tok);
	//				SafeDelete(map[j]->tileImages[i]);
	//				wstring wImgFile = L"";
	//				wImgFile.assign(path.begin(), path.end());
	//				map[j]->tileImages[i] = new ObImage(wImgFile);
	//
	//				break;
	//			}
	//			if (i < 3)
	//			{
	//				ImGui::SameLine();
	//			}
	//		}
	//	}
	//	ImGui::TreePop();
	//}
	//if (ImGui::TreeNode("Layer")) {
	//	for (int i = 0; i < MAXLAYER; i++) {
	//		if (ImGui::Selectable(("Layer " + std::to_string(i)).c_str(), SelectLayerIdx == i)) {
	//			SelectLayerIdx = i;
	//		}
	//		if (ImGui::Button(("Draw" + to_string(i)).c_str())) {
	//			map[i]->isVisible = !map[i]->isVisible;
	//		}
	//		ImGui::SameLine();
	//		if (GUI->FileImGui(("Save" + to_string(i)).c_str(), "Save Map", ".txt", "../Contents/TileMap"))
	//		{
	//			string path = ImGuiFileDialog::Instance()->GetFilePathName();
	//			Utility::Replace(&path, "\\", "/");
	//			size_t tok = path.find_last_of("/") + 1;
	//			path = path.substr(tok, path.length() - tok);
	//			map[i]->file = path;
	//			map[i]->Save();
	//		}
	//		ImGui::SameLine();
	//		if (GUI->FileImGui(("Load" + to_string(i)).c_str(), "Load Map", ".txt", "../Contents/TileMap"))
	//		{
	//			string path = ImGuiFileDialog::Instance()->GetFilePathName();
	//			Utility::Replace(&path, "\\", "/");
	//			size_t tok = path.find_last_of("/") + 1;
	//			path = path.substr(tok, path.length() - tok);
	//			map[i]->file = path;
	//			map[i]->Load();
	//			tileSize = map[i]->GetTileSize();
	//		}
	//	}
	//	if (ImGui::Button("Save All")) {
	//		map->file = "map1.txt";
	//		map->Save();
	//		map[1]->file = "map2.txt";
	//		map[1]->Save();
	//		map[2]->file = "map3.txt";
	//		map[2]->Save();
	//		map[3]->file = "map4.txt";
	//		map[3]->Save();
	//	}
	//
	//	ImGui::TreePop();
	//}
	//
	////"감바스";
	////L"감바스";
	////ImgIdx
	//if (ImGui::InputInt("ImgIdx", &brushImgIdx))
	//{
	//	brushImgIdx = Utility::Saturate(brushImgIdx, 0, 3);
	//	if (not map->tileImages[brushImgIdx])
	//	{
	//		brushImgIdx = 0;
	//	}
	//}
	////maxFrame
	//if (ImGui::InputInt2("maxFrame", (int*)&map[SelectLayerIdx]->tileImages[brushImgIdx]->maxFrame)) {
	//	map[SelectLayerIdx]->tileImages[brushImgIdx]->maxFrame = map[SelectLayerIdx]->tileImages[brushImgIdx]->maxFrame;
	//}
	//
	//if (brushImgIdx != 0) {
	//	Int2 MF = map[SelectLayerIdx]->tileImages[brushImgIdx]->maxFrame;
	//	ImVec2 size;
	//	size.x = 400.0f / (float)MF.x;
	//	size.y = 400.0f / (float)MF.y;
	//	ImVec2 LT, RB;
	//	int index = 0;
	//	for (UINT i = 0; i < MF.y; i++)
	//	{
	//		for (UINT j = 0; j < MF.x; j++)
	//		{
	//			if (j != 0)
	//			{
	//				//같은줄에 배치
	//				ImGui::SameLine();
	//			}
	//			//텍스쳐 좌표
	//			LT.x = 1.0f / MF.x * j;
	//			LT.y = 1.0f / MF.y * i;
	//			RB.x = 1.0f / MF.x * (j + 1);
	//			RB.y = 1.0f / MF.y * (i + 1);
	//
	//			ImGui::PushID(index);
	//			if (ImGui::ImageButton((void*)map[SelectLayerIdx]->tileImages[brushImgIdx]->GetSRV()
	//				, size, LT, RB))
	//			{
	//				brushFrame.x = j;
	//				brushFrame.y = i;
	//			}
	//			index++;
	//			ImGui::PopID();
	//		}
	//	}
	//}
	//
	////TileState
	//ImGui::SliderInt("TileState", &brushState, TILE_NONE, TILE_SIZE - 1);
	////TileColor
	//ImGui::ColorEdit4("TileColor", (float*)&brushColor, ImGuiColorEditFlags_PickerHueWheel);
	//
	////{
	////	if (GUI->FileImGui("Save", "Save Map",
	////		".txt", "../Contents/TileMap"))
	////	{
	////		string path = ImGuiFileDialog::Instance()->GetFilePathName();
	////		Utility::Replace(&path, "\\", "/");
	////		size_t tok = path.find_last_of("/") + 1;
	////		path = path.substr(tok, path.length() - tok);
	////		map->file = path;
	////		map->Save();
	////	}
	////	ImGui::SameLine();
	//
	////	if (GUI->FileImGui("Load", "Load Map", ".txt", "../Contents/TileMap"))
	////	{
	////		string path = ImGuiFileDialog::Instance()->GetFilePathName();
	////		Utility::Replace(&path, "\\", "/");
	////		size_t tok = path.find_last_of("/") + 1;
	////		path = path.substr(tok, path.length() - tok);
	////		map->file = path;
	////		map->Load();
	////		tileSize = map->GetTileSize();
	////	}
	////}
	//
	//
	//if (INPUT->KeyPress(VK_LBUTTON) && isApiScreen)
	//{
	//	Int2 Idx;
	//	if (map[SelectLayerIdx]->WorldPosToTileIdx(INPUT->GetWorldMousePos(), Idx))
	//	{
	//		map[SelectLayerIdx]->SetTile(Idx, brushFrame, brushImgIdx, brushState, brushColor);
	//	}
	//
	//}
	//if (INPUT->KeyPress(VK_RBUTTON) && isApiScreen)
	//{
	//	Int2 Idx;
	//	//?
	//	if (map[SelectLayerIdx]->WorldPosToTileIdx(INPUT->GetWorldMousePos(), Idx))
	//	{
	//		map[SelectLayerIdx]->SetTile(Idx, brushFrame, 0, 0, brushColor);
	//	}
	//
	//}
	//
	//
	//for (int i = 0; i < MAXLAYER; i++) {
	//	map[i]->Update();
	//}
	//LineX->Update();
	//LineY->Update();

	map->Update();
	if(StepCount != 41)
		StepCount++;
}

void Main::LateUpdate()
{
}

void Main::Render()
{
	map->Render();

	//for (int i = 0; i < MAXLAYER; i++) {
	//	map[i]->Render();
	//}
	//
	//LineX->Render();
	//LineY->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"MapTool");
	app.SetInstance(instance);
	app.InitWidthHeight(1000.f, 700.0f);
	app.background = Color(0.3, 0.3, 0.3);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}