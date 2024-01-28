#include "framework.h"

Utility::RECT::RECT(Vector2 pivot, Vector2 scale)
{
	min.x = pivot.x - scale.x * 0.5f;
	min.y = pivot.y - scale.y * 0.5f;
	max.x = pivot.x + scale.x * 0.5f;
	max.y = pivot.y + scale.y * 0.5f;
}

Utility::CIRCLE::CIRCLE(Vector2 pivot, Vector2 scale)
{
	this->pivot = pivot;
	radius = scale.x * 0.5f;
}

bool Utility::IntersectRectCoord(RECT& rc, Vector2 coord)
{
	if (rc.min.x < coord.x && coord.x < rc.max.x &&
		rc.min.y < coord.y && coord.y < rc.max.y)
	{
		return true;
	}
	return false;
}

bool Utility::IntersectRectRect(RECT& rc1, RECT& rc2)
{
	if (rc1.min.x < rc2.max.x &&
		rc1.max.x > rc2.min.x &&
		rc1.min.y < rc2.max.y &&
		rc1.max.y > rc2.min.y)
	{
		return true;
	}
	return false;
}

bool Utility::IntersectRectRect(GameObject* ob1, GameObject* ob2)
{
	//중심점
	Vector2 rc1Pivot = ob1->GetWorldPivot();
	Vector2 rc2Pivot = ob2->GetWorldPivot();

	//두 중심점간의 차이 벡터
	Vector2 dis = rc1Pivot - rc2Pivot;

	//사각형마다 2개의 절반크기의 벡터
	Vector2 Rc1Up =
		ob1->GetUp() * ob1->scale.y * 0.5f;
	Vector2 Rc1Right =
		ob1->GetRight() * ob1->scale.x * 0.5f;

	Vector2 Rc2Up =
		ob2->GetUp() * ob2->scale.y * 0.5f;
	Vector2 Rc2Right =
		ob2->GetRight() * ob2->scale.x * 0.5f;

	//ob1의 right축 비교
	//       절대값(내적 a . b)
	float c = fabs(dis.Dot(ob1->GetRight()));

	//ob2에서 두벡터가 투영된 길이
	float a = fabs(Rc2Up.Dot(ob1->GetRight()))
		+ fabs(Rc2Right.Dot(ob1->GetRight()));

	//ob1에서 두벡터가 투영된 길이
	float b = ob1->scale.x * 0.5f;

	if (c > a + b)return false;

	//ob1의 Up축 비교
	//       절대값(내적 a . b)
	c = fabs(dis.Dot(ob1->GetUp()));

	//ob2에서 두벡터가 투영된 길이
	a = fabs(Rc2Up.Dot(ob1->GetUp()))
		+ fabs(Rc2Right.Dot(ob1->GetUp()));
	//ob1에서 두벡터가 투영된 길이
	b = ob1->scale.y * 0.5f;

	if (c > a + b)return false;

	//ob2의 Right축 비교
	//       절대값(내적 a . b)
	c = fabs(dis.Dot(ob2->GetRight()));

	//ob1에서 두벡터가 투영된 길이
	a = fabs(Rc1Up.Dot(ob2->GetRight()))
		+ fabs(Rc1Right.Dot(ob2->GetRight()));
	//ob2에서 두벡터가 투영된 길이
	b = ob2->scale.x * 0.5f;

	if (c > a + b)return false;

	//ob2의 Up축 비교
	//       절대값(내적 a . b)
	c = fabs(dis.Dot(ob2->GetUp()));

	//ob1에서 두벡터가 투영된 길이
	a = fabs(Rc1Up.Dot(ob2->GetUp()))
		+ fabs(Rc1Right.Dot(ob2->GetUp()));
	//ob2에서 두벡터가 투영된 길이
	b = ob2->scale.y * 0.5f;

	if (c > a + b)return false;

	return true;
}

bool Utility::IntersectRectCircle(RECT& rc, CIRCLE& cc)
{
	Vector2 rectPivot = (rc.min + rc.max) * 0.5f;
	Vector2 rectScale = rc.max - rc.min;

	RECT wRect(rectPivot, rectScale + Vector2(cc.radius * 2.0f, 0.0f));
	if (IntersectRectCoord(wRect, cc.pivot))
	{
		return true;
	}

	RECT hRect(rectPivot, rectScale + Vector2(0.0f, cc.radius * 2.0f));
	if (IntersectRectCoord(hRect, cc.pivot))
	{
		return true;
	}

	Vector2 edge[4];
	edge[0] = Vector2(rc.min.x, rc.max.y);
	edge[1] = Vector2(rc.min.x, rc.min.y);
	edge[2] = Vector2(rc.max.x, rc.min.y);
	edge[3] = Vector2(rc.max.x, rc.max.y);

	for (int i = 0; i < 4; i++)
	{
		if (IntersectCircleCoord(cc, edge[i]))
		{
			return true;
		}
	}

	return false;
}

bool Utility::IntersectCircleCoord(CIRCLE& cc, Vector2 coord)
{
	Vector2 distance = cc.pivot - coord;

	if (distance.Length() < cc.radius)
	{
		return true;
	}
	return false;
}

bool Utility::IntersectCircleCircle(CIRCLE& cc1, CIRCLE& cc2)
{
	Vector2 distance = cc1.pivot - cc2.pivot;

	if (distance.Length() < cc1.radius + cc2.radius)
	{
		return true;
	}

	return false;
}

float Utility::DirToRadian(Vector2 Dir)
{
	//만약 단위벡터가 아니라면
	//Dir.Normalize();
	return atan2f(Dir.y, Dir.x);
}

Vector2 Utility::WorldToScreen(Vector2 wol)
{
	wol -= CAM->position;
	wol.x += app.GetHalfWidth();
	wol.y = app.GetHalfHeight() - wol.y;

	return wol;
}

void Utility::Replace(string* str, string comp, string rep)
{
	string temp = *str;

	size_t start_pos = 0;
	while ((start_pos = temp.find(comp, start_pos)) != wstring::npos)
	{
		temp.replace(start_pos, comp.length(), rep);
		start_pos += rep.length();
	}
	*str = temp;
}

static int FindWallCount = 0;
static int FindNoneCount = 0;

void TileCheckLogic(ObTileMap* map, Int2 currentIdx) {
	// 여기에 원하는 타일 검사 로직을 작성하세요.
	// 예시: 해당 타일의 정보를 얻고, 특정 조건을 확인하여 원하는 작업 수행
	int tileType = map->GetTileState(currentIdx);
	if (tileType == 1) {
		FindWallCount++;
	}
	else {
		FindNoneCount++;
	}
}

void CheckSurroundingTiles(ObTileMap* map, Int2 centerIdx, Int2 tileSize, int FindLength = 1) {
	FindWallCount = 0;
	FindNoneCount = 0;
	for (int y = centerIdx.y - FindLength; y <= centerIdx.y + FindLength; y++) {
		for (int x = centerIdx.x - FindLength; x <= centerIdx.x + FindLength; x++) {
			// 인덱스가 유효한지 검사 (범위를 벗어나지 않는지 확인)
			if (y >= 0 && y < tileSize.y && x >= 0 && x < tileSize.x) {
				Int2 currentIdx(x, y);

				// 현재 인덱스를 기준으로 타일 검사를 수행하는 함수 호출
				// 여기에 원하는 타일 검사 로직을 작성하세요.
				TileCheckLogic(map, currentIdx);
			}
		}
	}
	if (FindWallCount > 6) {
		int C = RANDOM->Int(50, 150);
		map->SetTile2(centerIdx, Int2(), 1, 1, Color(C / 255.0f * 0.5f, C / 255.0f * 0.5f, C / 255.0f * 0.5f, 0.5f));
	}
	else if (FindNoneCount > 5) {
		float C = (255.f / 20.f) * RANDOM->Int(3, 8) / 255.f * 0.5f;
		Color color = Color(C, C, C, 0.5f);
		map->SetTile2(centerIdx, Int2(), 1, 0, color);
	}

}
bool CheckTilesWithinDistance(ObTileMap* map, Int2 centerIdx, Int2 tileSize, int FindLength = 1) {

	int CheckTileNum = 0;

	for (int y = centerIdx.y - FindLength; y <= centerIdx.y + FindLength; y++) {
		for (int x = centerIdx.x - FindLength; x <= centerIdx.x + FindLength; x++) {
			// 인덱스가 유효한지 검사 (범위를 벗어나지 않는지 확인)
			if (y >= 0 && y < tileSize.y && x >= 0 && x < tileSize.x) {
				Int2 currentIdx(x, y);

				// 현재 인덱스를 기준으로 타일 검사를 수행하는 함수 호출
				// 여기에 원하는 타일 검사 로직을 작성하세요.
				if (map->IsInMap(currentIdx)) {
					CheckTileNum++;
				}
				else {
					return false;
				}
			}
		}
	}

	if (CheckTileNum == pow(2 * FindLength + 1, 2)) {
		return true;
	}
}

void RepaintTile(ObTileMap* map, Int2 centerIdx, int FindLength = 1,int Type = 0, Color Color = class Color()) {

	Int2 tileSize = map->GetTileSize();

	for (int y = centerIdx.y - FindLength; y <= centerIdx.y + FindLength; y++) {
		for (int x = centerIdx.x - FindLength; x <= centerIdx.x + FindLength; x++) {
			// 인덱스가 유효한지 검사 (범위를 벗어나지 않는지 확인)
			if (y >= 0 && y < tileSize.y && x >= 0 && x < tileSize.x) {
				Int2 currentIdx(x, y);

				if (map->GetTileState(currentIdx) == TILE_WALL) {
					continue;
				}
				else {
					map->SetTile2(currentIdx, Int2(), 1, Type, Color);
				}
				
			}
		}
	}
}


void DetectTiles(ObTileMap* map, Int2 tileSize, int type, int recursionDepth = 0)
{
	// 재귀 깊이 제한 설정 (예를 들어, 1000)
	const int recursionLimit = 10;
	static int MaxSize = 0;
	static Int2 LastPos = Int2();
	
	if (recursionDepth >= recursionLimit) {
		// 재귀 깊이 제한에 도달하면, 추가적인 재귀 호출 없이 반환합니다.
		map->FindTilesInRange(LastPos, 1);
		MaxSize = 0;
		LastPos = Int2();
		return;
	}
	Int2 Idx(RANDOM->Int(0, tileSize.x-1), RANDOM->Int(0, tileSize.y - 1));
	int size = map->FindTilesInRange(Idx, 1);

	if (size >= MaxSize) {
		LastPos = Idx;
	}
	MaxSize = max(MaxSize, size);
	if (size >= MaxSize && recursionDepth > 2) {
		MaxSize = 0;
		LastPos = Int2();
		map->Save();
		return;
	}
	return DetectTiles(map, tileSize, recursionDepth + 1, type);
}
