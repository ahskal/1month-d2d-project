#include "framework.h"


ObTileMap::ObTileMap()
{
	SafeRelease(vertexBuffer);
	SafeDeleteArray(vertices);
	for (int i = 0; i < 4; i++)
		SafeDelete(tileImages[i]);

	tileSize.x = 20;
	tileSize.y = 20;
	file = "map1.txt";
	scale = Vector2(50.0f, 50.0f);

	tileImages[0] = new ObImage(L"Tile_NONE.png");
	tileImages[0]->maxFrame = Int2(1, 1);
	tileImages[1] = new ObImage(L"Tile_NONE.png");
	tileImages[1]->maxFrame = Int2(1, 1);
	tileImages[2] = new ObImage(L"Tile_NONE.png");
	tileImages[2]->maxFrame = Int2(1, 1);
	tileImages[3] = new ObImage(L"Tile_NONE.png");
	tileImages[3]->maxFrame = Int2(1, 1);

	ResizeTile(tileSize);
}

ObTileMap::~ObTileMap()
{
	SafeRelease(vertexBuffer);
	SafeDeleteArray(vertices);
	for (int i = 0; i < 4; i++)
		SafeDelete(tileImages[i]);
}

void ObTileMap::Render()
{
	if (!isVisible)return;
	GameObject::Render();

	for (int i = 0; i < 4; i++)
	{
		if (tileImages[i])
		{
			D3D->GetDC()->PSSetShaderResources(i, 1, &tileImages[i]->SRV);
			D3D->GetDC()->PSSetSamplers(i, 1, &tileImages[i]->sampler);
		}
	}

	tileMapShader->Set();

	UINT stride = sizeof(VertexTile);
	UINT offset = 0;

	D3D->GetDC()->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	D3D->GetDC()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D->GetDC()->Draw(tileSize.x * tileSize.y * 6, 0);
}

mutex m1;

void ObTileMap::SetTile(Int2 TileIdx, Int2 FrameIdx, int ImgIdx, int TileState, Color color)
{
	int tileIdx = tileSize.x * TileIdx.y + TileIdx.x;
	vertices[tileIdx * 6 + 0].uv.x = FrameIdx.x / (float)tileImages[ImgIdx]->maxFrame.x;
	vertices[tileIdx * 6 + 1].uv.x = FrameIdx.x / (float)tileImages[ImgIdx]->maxFrame.x;
	vertices[tileIdx * 6 + 5].uv.x = FrameIdx.x / (float)tileImages[ImgIdx]->maxFrame.x;


	vertices[tileIdx * 6 + 2].uv.x = (FrameIdx.x + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.x;
	vertices[tileIdx * 6 + 3].uv.x = (FrameIdx.x + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.x;
	vertices[tileIdx * 6 + 4].uv.x = (FrameIdx.x + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.x;

	vertices[tileIdx * 6 + 3].uv.y = FrameIdx.y / (float)tileImages[ImgIdx]->maxFrame.y;
	vertices[tileIdx * 6 + 1].uv.y = FrameIdx.y / (float)tileImages[ImgIdx]->maxFrame.y;
	vertices[tileIdx * 6 + 5].uv.y = FrameIdx.y / (float)tileImages[ImgIdx]->maxFrame.y;

	vertices[tileIdx * 6 + 2].uv.y = (FrameIdx.y + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.y;
	vertices[tileIdx * 6 + 0].uv.y = (FrameIdx.y + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.y;
	vertices[tileIdx * 6 + 4].uv.y = (FrameIdx.y + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.y;

	for (int i = 0; i < 6; i++)
	{
		vertices[tileIdx * 6 + i].tileMapIdx = ImgIdx;
		vertices[tileIdx * 6 + i].color = color;
		vertices[tileIdx * 6 + i].tileState = TileState;
	}
	m1.lock();
	D3D->GetDC()->UpdateSubresource
	(vertexBuffer, 0, NULL, vertices, 0, 0);
	m1.unlock();
}

void ObTileMap::SetTile2(Int2 TileIdx, Int2 FrameIdx, int ImgIdx, int TileState, Color color)
{
	int tileIdx = tileSize.x * TileIdx.y + TileIdx.x;
	vertices[tileIdx * 6 + 0].uv.x = FrameIdx.x / (float)tileImages[ImgIdx]->maxFrame.x;
	vertices[tileIdx * 6 + 1].uv.x = FrameIdx.x / (float)tileImages[ImgIdx]->maxFrame.x;
	vertices[tileIdx * 6 + 5].uv.x = FrameIdx.x / (float)tileImages[ImgIdx]->maxFrame.x;


	vertices[tileIdx * 6 + 2].uv.x = (FrameIdx.x + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.x;
	vertices[tileIdx * 6 + 3].uv.x = (FrameIdx.x + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.x;
	vertices[tileIdx * 6 + 4].uv.x = (FrameIdx.x + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.x;

	vertices[tileIdx * 6 + 3].uv.y = FrameIdx.y / (float)tileImages[ImgIdx]->maxFrame.y;
	vertices[tileIdx * 6 + 1].uv.y = FrameIdx.y / (float)tileImages[ImgIdx]->maxFrame.y;
	vertices[tileIdx * 6 + 5].uv.y = FrameIdx.y / (float)tileImages[ImgIdx]->maxFrame.y;

	vertices[tileIdx * 6 + 2].uv.y = (FrameIdx.y + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.y;
	vertices[tileIdx * 6 + 0].uv.y = (FrameIdx.y + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.y;
	vertices[tileIdx * 6 + 4].uv.y = (FrameIdx.y + 1.0f) / (float)tileImages[ImgIdx]->maxFrame.y;

	for (int i = 0; i < 6; i++)
	{
		vertices[tileIdx * 6 + i].tileMapIdx = ImgIdx;
		vertices[tileIdx * 6 + i].color = color;
		vertices[tileIdx * 6 + i].tileState = TileState;
	}
}

void ObTileMap::UpdateSub()
{
	m1.lock();
	D3D->GetDC()->UpdateSubresource
	(vertexBuffer, 0, NULL, vertices, 0, 0);
	m1.unlock();
}



int ObTileMap::GetTileState(Int2 TileIdx)
{
	int tileIdx = tileSize.x * TileIdx.y + TileIdx.x;
	return vertices[tileIdx * 6].tileState;
}

int ObTileMap::GetTileState(Vector2 WorldPos)
{
	Int2 plIdx;
	if (WorldPosToTileIdx(WorldPos, plIdx))
	{
		return GetTileState(plIdx);
	}

	return TILE_SIZE;
}

Vector2 ObTileMap::GetTilePosition(Int2 TileIdx)
{
	int tileIdx = tileSize.x * TileIdx.y + TileIdx.x;
	return Vector2(vertices[tileIdx * 6].position.x, vertices[tileIdx * 6].position.y);
}


bool ObTileMap::WorldPosToTileIdx(Vector2 WPos, Int2& TileIdx)
{
	WPos -= GetWorldPos();
	Vector2 tileCoord;
	tileCoord.x = WPos.x / scale.x;
	tileCoord.y = WPos.y / scale.y;
	if ((tileCoord.x < 0) or (tileCoord.y < 0) or
		(tileCoord.x >= tileSize.x) or (tileCoord.y >= tileSize.y))
	{
		return false;
	}
	TileIdx.x = tileCoord.x;
	TileIdx.y = tileCoord.y;
	return true;
}

void ObTileMap::ResizeTile(Int2 TileSize)
{
	VertexTile* Vertices = new VertexTile[TileSize.x * TileSize.y * 6];
	//Init
	for (int i = 0; i < TileSize.y; i++)
	{

		//가로
		for (int j = 0; j < TileSize.x; j++)
		{
			//타일좌표 ( tileSize.x * y좌표 + x좌표)
			//꼭지점 좌표 ( tileSize.x * y좌표 + x좌표) * 6
			int tileIdx = TileSize.x * i + j;
			//0
			Vertices[tileIdx * 6].position.x = 0.0f + j;
			Vertices[tileIdx * 6].position.y = 0.0f + i;
			Vertices[tileIdx * 6].uv = Vector2(0.0f, 1.0f);
			//1                             
			Vertices[tileIdx * 6 + 1].position.x = 0.0f + j;
			Vertices[tileIdx * 6 + 1].position.y = 1.0f + i;
			Vertices[tileIdx * 6 + 1].uv = Vector2(0.0f, 0.0f);
			//2                             
			Vertices[tileIdx * 6 + 2].position.x = 1.0f + j;
			Vertices[tileIdx * 6 + 2].position.y = 0.0f + i;
			Vertices[tileIdx * 6 + 2].uv = Vector2(1.0f, 1.0f);
			//3
			Vertices[tileIdx * 6 + 3].position.x = 1.0f + j;
			Vertices[tileIdx * 6 + 3].position.y = 1.0f + i;
			Vertices[tileIdx * 6 + 3].uv = Vector2(1.0f, 0.0f);
			//4
			Vertices[tileIdx * 6 + 4].position.x = 1.0f + j;
			Vertices[tileIdx * 6 + 4].position.y = 0.0f + i;
			Vertices[tileIdx * 6 + 4].uv = Vector2(1.0f, 1.0f);
			//5
			Vertices[tileIdx * 6 + 5].position.x = 0.0f + j;
			Vertices[tileIdx * 6 + 5].position.y = 1.0f + i;
			Vertices[tileIdx * 6 + 5].uv = Vector2(0.0f, 0.0f);
		}
	}

	//Copy
	if (vertices)
	{
		Int2 Min = Int2(min(TileSize.x, tileSize.x), min(TileSize.y, tileSize.y));
		for (int i = 0; i < Min.y; i++)
		{
			for (int j = 0; j < Min.x; j++)
			{
				int SrcIdx = tileSize.x * i + j;
				int DestIdx = TileSize.x * i + j;
				for (int k = 0; k < 6; k++)
				{
					Vertices[DestIdx * 6 + k] = vertices[SrcIdx * 6 + k];
				}
			}
		}
	}

	SafeDeleteArray(vertices);
	vertices = Vertices;
	tileSize = TileSize;
	SafeRelease(vertexBuffer);
	//CreateVertexBuffer
	{
		D3D11_BUFFER_DESC desc;
		desc = { 0 };
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(VertexTile) * tileSize.x * tileSize.y * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;
		HRESULT hr = D3D->GetDevice()->CreateBuffer(&desc, &data, &vertexBuffer);
		Check(hr);
	}
}

void ObTileMap::Save()
{
	ofstream fout;
	string path = "../Contents/TileMap/" + file;
	fout.open(path.c_str(), ios::out);
	if (fout.is_open())
	{
		for (int i = 0; i < 4; i++)
		{
			fout << i << " ";
			if (tileImages[i])
			{
				string imgFile = "";
				imgFile.assign(tileImages[i]->file.begin(), tileImages[i]->file.end());
				fout << imgFile << " ";
				fout << tileImages[i]->maxFrame.x << " " << tileImages[i]->maxFrame.y << endl;
			}
			else
			{
				fout << "N" << endl;
			}
		}
		fout << "TileSize " << tileSize.x << " " << tileSize.y << endl;
		fout << "TileScale " << scale.x << " " << scale.y << endl;
		fout << "TilePosition " << GetWorldPos().x << " " << GetWorldPos().y << endl;

		for (int i = 0; i < tileSize.y; i++)
		{
			//가로
			for (int j = 0; j < tileSize.x; j++)
			{
				int tileIdx = tileSize.x * i + j;
				fout << j << " " << i << " "
					<< vertices[tileIdx * 6 + 1].uv.x << " " << vertices[tileIdx * 6 + 1].uv.y << " "
					<< vertices[tileIdx * 6 + 2].uv.x << " " << vertices[tileIdx * 6 + 2].uv.y << " "
					<< vertices[tileIdx * 6].color.x << " " << vertices[tileIdx * 6].color.y << " "
					<< vertices[tileIdx * 6].color.z << " " << vertices[tileIdx * 6].color.w << " "
					<< vertices[tileIdx * 6].tileMapIdx << " " << vertices[tileIdx * 6].tileState << endl;
			}
		}
		fout.close();
	}
}

void ObTileMap::Load()
{
	ifstream fin;
	string path = "../Contents/TileMap/" + file;
	fin.open(path.c_str(), ios::in);
	string temp;
	if (fin.is_open())
	{
		for (int i = 0; i < 4; i++)
		{
			SafeDelete(tileImages[i]);
			int idx; string Imgfile;
			fin >> idx;
			fin >> Imgfile;
			if (Imgfile != "N")
			{
				wstring wImgFile = L"";
				wImgFile.assign(Imgfile.begin(), Imgfile.end());
				tileImages[i] = new ObImage(wImgFile);
				fin >> tileImages[i]->maxFrame.x >> tileImages[i]->maxFrame.y;
			}
		}
		Int2 TileSize;
		fin >> temp >> TileSize.x >> TileSize.y;
		ResizeTile(TileSize);
		fin >> temp >> scale.x >> scale.y;
		Vector2 pos;
		fin >> temp >> pos.x >> pos.y;
		SetWorldPos(pos);

		for (int i = 0; i < tileSize.y; i++)
		{
			//가로
			for (int j = 0; j < tileSize.x; j++)
			{
				int temp; Vector2 MinUV, MaxUV; Color color; float tileMapIdx, tileMapState;
				fin >> temp >> temp >> MinUV.x >> MinUV.y >> MaxUV.x >> MaxUV.y
					>> color.x >> color.y >> color.z >> color.w >> tileMapIdx >> tileMapState;

				int tileIdx = tileSize.x * i + j;

				vertices[tileIdx * 6].uv = Vector2(MinUV.x, MaxUV.y);
				vertices[tileIdx * 6 + 1].uv = Vector2(MinUV.x, MinUV.y);
				vertices[tileIdx * 6 + 2].uv = Vector2(MaxUV.x, MaxUV.y);
				vertices[tileIdx * 6 + 3].uv = Vector2(MaxUV.x, MinUV.y);
				vertices[tileIdx * 6 + 4].uv = Vector2(MaxUV.x, MaxUV.y);
				vertices[tileIdx * 6 + 5].uv = Vector2(MinUV.x, MinUV.y);
				for (int k = 0; k < 6; k++)
				{
					vertices[tileIdx * 6 + k].color = color;
					vertices[tileIdx * 6 + k].tileMapIdx = tileMapIdx;
					vertices[tileIdx * 6 + k].tileState = tileMapState;
				}
			}
		}
		D3D->GetDC()->UpdateSubresource
		(vertexBuffer, 0, NULL, vertices, 0, 0);

		fin.close();
	}
}



void Tile::ClearCost()
{
	//비용을 무한값으로 초기화
	F = G = H = INT_MAX;
	P = nullptr;
	isFind = false;
}

void Tile::ClacH(Int2 DestIdx)
{
	//너의 목적지까지의 예상비용을 계산해라
	int tempX = abs(idx.x - DestIdx.x) * 10;
	int tempY = abs(idx.y - DestIdx.y) * 10;

	H = tempX + tempY;
}

void Tile::ClacF()
{
	F = G + H;
}


void ObTileMap::CreateTileCost()
{
	for (int i = 0; i < Tiles.size(); i++)
	{
		Tiles[i].clear();
	}
	Tiles.clear();


	Tiles.resize(tileSize.x);
	for (int i = 0; i < Tiles.size(); i++)
	{
		Tiles[i].resize(tileSize.y);
	}


	Vector2 half = scale * 0.5f;
	Update();
	for (int i = 0; i < tileSize.x; i++)
	{
		for (int j = 0; j < tileSize.y; j++)
		{
			Tiles[i][j].idx = Int2(i, j);
			Tiles[i][j].state = GetTileState(Tiles[i][j].idx);
			Tiles[i][j].Pos.x = i * scale.x + GetWorldPos().x + half.x;
			Tiles[i][j].Pos.y = j * scale.y + GetWorldPos().y + half.y;
		}
	}
}

bool ObTileMap::PathFinding(Int2 sour, Int2 dest, OUT vector<Tile*>& way)
{
	//둘중에 하나가 벽이면 갈 수 있는길이 없다.
	if (Tiles[dest.x][dest.y].state == TILE_WALL ||
		Tiles[sour.x][sour.y].state == TILE_WALL)
	{
		return false;
	}
	//기존에 있던 길은 전부 비운다.
	way.clear();
	//출발지 목적지 같으면
	if (sour == dest)
	{
		return false;//제자리 멈추기
	}



	//타일 비용 초기화
	for (int i = 0; i < tileSize.x; i++)
	{
		for (int j = 0; j < tileSize.y; j++)
		{
			Tiles[i][j].ClearCost();
		}
	}
	//우선순위 큐

	//F값을 가지고 정렬해주는 리스트
	priority_queue<PTile, vector<PTile>, compare> List;
	//priority_queue<Tile*> List;
	//Tile* a, *b;
	//a > b;

	//리스트에 출발지를 추가
	Tile* pTemp = &Tiles[sour.x][sour.y];
	pTemp->G = 0;       //출발지 현재비용은 0
	pTemp->ClacH(dest); //목적지까지 예상비용 만들기
	pTemp->ClacF();     //총예상비용 만들기
	List.push({ pTemp ,pTemp->F });

	//도착점까지 비용이 생길때 까지 반복
	while (1)
	{
		//꺼내야될 F값이 더이상 없을때
		if (List.empty())
		{
			return false;
		}

		//탐색노드 받아오기
		PTile Temp = List.top();
		//탐색목록에서 제외
		Temp.first->isFind = true;
		//맨윗값 빼버리기
		List.pop();

		//맨윗값이 도착점이면 종료(길찾기 종료조건)
		if (Temp.first->idx == dest)
		{
			break;
		}

		//인접 타일 비용검사
		vector<Int2> LoopIdx;

		//왼쪽타일이 존재할때
		// 대각선 및 수직/수평 이동에 대한 인접 타일 비용검사
		// 왼쪽 타일이 존재할 때
		if (Temp.first->idx.x > 0)
		{
			LoopIdx.push_back(Int2(Temp.first->idx.x - 1, Temp.first->idx.y));
		}
		// 오른쪽 타일이 존재할 때
		if (Temp.first->idx.x < tileSize.x - 1)
		{
			LoopIdx.push_back(Int2(Temp.first->idx.x + 1, Temp.first->idx.y));
		}
		// 위쪽 타일이 존재할 때
		if (Temp.first->idx.y > 0)
		{
			LoopIdx.push_back(Int2(Temp.first->idx.x, Temp.first->idx.y - 1));
		}
		// 아래쪽 타일이 존재할 때
		if (Temp.first->idx.y < tileSize.y - 1)
		{
			LoopIdx.push_back(Int2(Temp.first->idx.x, Temp.first->idx.y + 1));
		}
		// 왼쪽 위 대각선 타일이 존재할 때
		if (Temp.first->idx.x > 0 && Temp.first->idx.y > 0)
		{
			LoopIdx.push_back(Int2(Temp.first->idx.x - 1, Temp.first->idx.y - 1));
		}
		// 오른쪽 위 대각선 타일이 존재할 때
		if (Temp.first->idx.x < tileSize.x - 1 && Temp.first->idx.y > 0)
		{
			LoopIdx.push_back(Int2(Temp.first->idx.x + 1, Temp.first->idx.y - 1));
		}
		// 왼쪽 아래 대각선 타일이 존재할 때
		if (Temp.first->idx.x > 0 && Temp.first->idx.y < tileSize.y - 1)
		{
			LoopIdx.push_back(Int2(Temp.first->idx.x - 1, Temp.first->idx.y + 1));
		}
		// 오른쪽 아래 대각선 타일이 존재할 때
		if (Temp.first->idx.x < tileSize.x - 1 && Temp.first->idx.y < tileSize.y - 1)
		{
			LoopIdx.push_back(Int2(Temp.first->idx.x + 1, Temp.first->idx.y + 1));
		}

		// 수직/수평 이동 비용
		int straightCost = 10;
		// 대각선 이동 비용
		int diagonalCost = 14;

		// 인접 타일 비용 계산
		for (int i = 0; i < LoopIdx.size(); i++)
		{
			Tile* loop = &Tiles[LoopIdx[i].x][LoopIdx[i].y];
			// 벽이 아닐 때
			if (loop->state != TILE_WALL)
			{
				int newCost;
				// 대각선 이동일 경우
				if (LoopIdx[i].x != Temp.first->idx.x && LoopIdx[i].y != Temp.first->idx.y)
				{
					newCost = Temp.first->G + diagonalCost;
				}
				else
				{
					newCost = Temp.first->G + straightCost;
				}
				// 현재 가지고 있는 비용보다 작을 때
				if (newCost < loop->G)
				{
					// 비용 갱신
					loop->G = newCost;
					loop->ClacF();
					// 누구로부터 갱신인지 표시
					loop->P = Temp.first;
					// 이 타일이 찾은 적 없던 타일이면 리스트에 추가
					if (!loop->isFind)
					{
						List.push({ loop, loop->F });
					}
				}
			}
		}



		LoopIdx.clear();


	}
	//도착지가 설정이 되었을때

	Tile* p = &Tiles[dest.x][dest.y];
	//dest 4,1 -> 4,2 -> 4,3 -> 3,3 ->2,3-> 1,3 ->
	while (1)
	{
		way.push_back(p);
		p = p->P;
		if (p == nullptr)
		{
			break;
		}
	}
	return true;
}

bool ObTileMap::PathFinding(Vector2 sour, Vector2 dest, OUT vector<Tile*>& way)
{
	Int2 sourIdx, destIdx;
	if (WorldPosToTileIdx(sour, sourIdx) and
		WorldPosToTileIdx(dest, destIdx))
	{
		return PathFinding(sourIdx, destIdx, way);
	}

	return false;
}

bool ObTileMap::IsInMap(const Int2& pos) {
	return pos.x >= 0 && pos.x < tileSize.x&& pos.y >= 0 && pos.y < tileSize.y;
}

int ObTileMap::FindTilesInRange(const Int2& sour, int Type) {
	// 크기 변수 초기화
	int size = 0;

	// Type에 따라서 해당타일 찾을지 찾지않을지 정함
	if (GetTileState(Int2(sour.x, sour.y)) == Type) {
		return size;
	}
	// 검색하기전에 초기화
	for (int i = 0; i < tileSize.x; i++)
	{
		for (int j = 0; j < tileSize.y; j++)
		{
			Tiles[i][j].ClearCost();
			if (Tiles[i][j].state == TILE_FINDING) {
				SetTile2(Int2(i,j), Int2(), 1, 2, TILE_COLOR);
			}
		}
	}

	// BFS를 이용하여 탐색
	std::queue<Int2> q;
	q.push(sour);
	size++; // 시작 타일도 크기에 포함

	const int dx[] = { -1, 0, 0, 1, };
	const int dy[] = { 0, -1, 1,  0, };

	while (!q.empty()) {
		Int2 current = q.front();
		q.pop();

		for (int i = 0; i < 4; i++) {
			Int2 next(current.x + dx[i], current.y + dy[i]);

			// 이동한 위치가 타일 맵 내에 있고, 아직 검사하지 않은 타일인 경우
			if (IsInMap(next) && !Tiles[next.x][next.y].isFind && GetTileState(next) != Type) {
				q.push(next);
				size++; // 크기 증가
				Tiles[next.x][next.y].isFind = true;
				if (Type == 1)
					SetTile2(next, Int2(), 1, 2, FIND_COLOR);
				if (Type == 2)
					SetTile2(next, Int2(), 1, 1, FIND_COLOR);
			}
		}
	}

	return size;
}


