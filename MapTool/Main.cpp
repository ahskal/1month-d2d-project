#include "stdafx.h"
#include "Main.h"

Main::Main()
{
	for (int i = 0; i < MAXLAYER; i++) {
		map[i] = new ObTileMap();
	}

	map[0]->file = "Map1.txt";
	map[1]->file = "Map2.txt";
	map[2]->file = "Map3.txt";
	map[3]->file = "Map4.txt";
	//map[0]->Load();
	//map[1]->Load();
	//map[2]->Load();
	//map[3]->Load();

	//map = new ObTileMap();
	////map->file = "map2.txt";
	////map->Load();
	//map->color = Color(0.5f, 0.5f, 0.5f, 0.5f);
	tileSize = Int2(50, 50);

	LineX = new ObRect();
	LineX->color = Color(1.0f, 0.0f, 0.0f, 1.0f);
	LineX->pivot = OFFSET_N;
	LineX->scale.x = 20000.0f;
	LineX->scale.y = 5.0f;

	LineY = new ObRect();
	LineY->color = Color(0.0f, 1.0f, 0.0f, 1.0f);
	LineY->pivot = OFFSET_N;
	LineY->scale.x = 5.0f;
	LineY->scale.y = 20000.0f;



	brushImgIdx = 0;
	brushFrame.x = 0;
	brushFrame.y = 0;
	brushColor = Color(0.5f, 0.5f, 0.5f, 0.5f);
	brushState = 0;

	SelectLayerIdx = 0;

	CAM->scale = Vector2(1, 1);

}

Main::~Main()
{
}

void Main::Init()
{
}

void Main::Release()
{

}

void Main::Update()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGui::Text("FPS : %d", (int)TIMER->GetFramePerSecond());

	ImGui::Text("CAM Scale %f, %f", CAM->scale.x, CAM->scale.y);
	ImGui::Text("screen Pos %f %f", ImGui::GetCursorScreenPos().x, ImGui::GetCursorScreenPos().y);
	
	ImVec2 mousePos = ImGui::GetIO().MousePos;

	// 화면 크기를 얻어옴
	ImVec2 screenSize = ImGui::GetIO().DisplaySize;

	// 마우스 커서가 화면 밖으로 나갔는지 확인
	bool isMouseOutside = (mousePos.x < 0 || mousePos.y < 0 || mousePos.x >= screenSize.x || mousePos.y >= screenSize.y);

	// 마우스가 나갔다 
	if (isMouseOutside)
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

	


	if (INPUT->KeyPress('W'))
	{
		CAM->position += UP * 300.0f * DELTA;
	}
	if (INPUT->KeyPress('S'))
	{
		CAM->position += DOWN * 300.0f * DELTA;
	}
	if (INPUT->KeyPress('A'))
	{
		CAM->position += LEFT * 300.0f * DELTA;
	}
	if (INPUT->KeyPress('D'))
	{
		CAM->position += RIGHT * 300.0f * DELTA;
	}

	//TileSize
	if (ImGui::SliderInt2("TileSize", (int*)&tileSize, 1, 100))
	{
		for (int i = 0; i < MAXLAYER; i++) {
			map[i]->ResizeTile(tileSize);
		}
	}


	//TileScale
	//ImGui::SliderFloat2("TileScale", (float*)&map->scale, 1.0f, 200.0f);
	if (ImGui::InputFloat("TileScale", (float*)&map[0]->scale.x, 1.0f, 200.0f))
	{
		for (int i = 0; i < MAXLAYER; i++) {
			map[i]->scale.y = map[i]->scale.x = map[0]->scale.x;
		}
	}


	//TilePos
	Vector2 pos = map[0]->GetWorldPos();
	if (ImGui::SliderFloat2("TilePos", (float*)&pos, -1000.0f, 1000.0f))
	{
		for (int i = 0; i < MAXLAYER; i++) {
			map[i]->SetWorldPos(pos);
		}
	}ImGui::SameLine();
	if (ImGui::Button("ReSet")) {
		for (int i = 0; i < MAXLAYER; i++) {
			map[i]->SetWorldPosX(0);
			map[i]->SetWorldPosY(0);
		}
	}

	if (ImGui::TreeNode("Textuer Load")) {
		for (int j = 0; j < MAXLAYER; j++) {
			for (int i = 0; i < 4; i++)
			{
				string str = "Texture" + to_string(j) + "_" + to_string(i);
				if (GUI->FileImGui(str.c_str(), str.c_str(),
					".png,.jpg,.bmp,.dds,.tga", "../Contents/Images"))
				{
					string path = ImGuiFileDialog::Instance()->GetFilePathName();
					Utility::Replace(&path, "\\", "/");
					size_t tok = path.find_last_of("/") + 1;
					path = path.substr(tok, path.length() - tok);
					SafeDelete(map[j]->tileImages[i]);
					wstring wImgFile = L"";
					wImgFile.assign(path.begin(), path.end());
					map[j]->tileImages[i] = new ObImage(wImgFile);

					break;
				}
				if (i < 3)
				{
					ImGui::SameLine();
				}
			}
		}
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Layer")) {
		for (int i = 0; i < MAXLAYER; i++) {
			if (ImGui::Selectable(("Layer " + std::to_string(i)).c_str(), SelectLayerIdx == i)) {
				SelectLayerIdx = i;
			}
			if (ImGui::Button(("Draw" + to_string(i)).c_str())) {
				map[i]->isVisible = !map[i]->isVisible;
			}
			ImGui::SameLine();
			if (GUI->FileImGui(("Save" + to_string(i)).c_str(), "Save Map", ".txt", "../Contents/TileMap"))
			{
				string path = ImGuiFileDialog::Instance()->GetFilePathName();
				Utility::Replace(&path, "\\", "/");
				size_t tok = path.find_last_of("/") + 1;
				path = path.substr(tok, path.length() - tok);
				map[i]->file = path;
				map[i]->Save();
			}
			ImGui::SameLine();
			if (GUI->FileImGui(("Load" + to_string(i)).c_str(), "Load Map", ".txt", "../Contents/TileMap"))
			{
				string path = ImGuiFileDialog::Instance()->GetFilePathName();
				Utility::Replace(&path, "\\", "/");
				size_t tok = path.find_last_of("/") + 1;
				path = path.substr(tok, path.length() - tok);
				map[i]->file = path;
				map[i]->Load();
				tileSize = map[i]->GetTileSize();
			}
		}
		if (ImGui::Button("Save All")) {
			map[0]->file = "map1.txt";
			map[0]->Save();
			map[1]->file = "map2.txt";
			map[1]->Save();
			map[2]->file = "map3.txt";
			map[2]->Save();
			map[3]->file = "map4.txt";
			map[3]->Save();
		}
		
		ImGui::TreePop();
	}

	//"감바스";
	//L"감바스";
	//ImgIdx
	if (ImGui::InputInt("ImgIdx", &brushImgIdx))
	{
		brushImgIdx = Utility::Saturate(brushImgIdx, 0, 3);
		if (not map[0]->tileImages[brushImgIdx])
		{
			brushImgIdx = 0;
		}
	}
	//maxFrame
	if (ImGui::InputInt2("maxFrame", (int*)&map[SelectLayerIdx]->tileImages[brushImgIdx]->maxFrame)) {
		map[SelectLayerIdx]->tileImages[brushImgIdx]->maxFrame = map[SelectLayerIdx]->tileImages[brushImgIdx]->maxFrame;
	}

	if (brushImgIdx != 0) {
		Int2 MF = map[SelectLayerIdx]->tileImages[brushImgIdx]->maxFrame;
		ImVec2 size;
		size.x = 400.0f / (float)MF.x;
		size.y = 400.0f / (float)MF.y;
		ImVec2 LT, RB;
		int index = 0;
		for (UINT i = 0; i < MF.y; i++)
		{
			for (UINT j = 0; j < MF.x; j++)
			{
				if (j != 0)
				{
					//같은줄에 배치
					ImGui::SameLine();
				}
				//텍스쳐 좌표
				LT.x = 1.0f / MF.x * j;
				LT.y = 1.0f / MF.y * i;
				RB.x = 1.0f / MF.x * (j + 1);
				RB.y = 1.0f / MF.y * (i + 1);

				ImGui::PushID(index);
				if (ImGui::ImageButton((void*)map[SelectLayerIdx]->tileImages[brushImgIdx]->GetSRV()
					, size, LT, RB))
				{
					brushFrame.x = j;
					brushFrame.y = i;
				}
				index++;
				ImGui::PopID();
			}
		}
	}

	//TileState
	ImGui::SliderInt("TileState", &brushState, TILE_NONE, TILE_SIZE - 1);
	//TileColor
	ImGui::ColorEdit4("TileColor", (float*)&brushColor, ImGuiColorEditFlags_PickerHueWheel);

	//{
	//	if (GUI->FileImGui("Save", "Save Map",
	//		".txt", "../Contents/TileMap"))
	//	{
	//		string path = ImGuiFileDialog::Instance()->GetFilePathName();
	//		Utility::Replace(&path, "\\", "/");
	//		size_t tok = path.find_last_of("/") + 1;
	//		path = path.substr(tok, path.length() - tok);
	//		map->file = path;
	//		map->Save();
	//	}
	//	ImGui::SameLine();

	//	if (GUI->FileImGui("Load", "Load Map", ".txt", "../Contents/TileMap"))
	//	{
	//		string path = ImGuiFileDialog::Instance()->GetFilePathName();
	//		Utility::Replace(&path, "\\", "/");
	//		size_t tok = path.find_last_of("/") + 1;
	//		path = path.substr(tok, path.length() - tok);
	//		map->file = path;
	//		map->Load();
	//		tileSize = map->GetTileSize();
	//	}
	//}


	if (INPUT->KeyPress(VK_LBUTTON) && isApiScreen)
	{
		Int2 Idx;
		if (map[SelectLayerIdx]->WorldPosToTileIdx(INPUT->GetWorldMousePos(), Idx))
		{
			map[SelectLayerIdx]->SetTile(Idx, brushFrame, brushImgIdx, brushState, brushColor);
		}

	}
	if (INPUT->KeyPress(VK_RBUTTON) && isApiScreen)
	{
		Int2 Idx;
		//?
		if (map[SelectLayerIdx]->WorldPosToTileIdx(INPUT->GetWorldMousePos(), Idx))
		{
			map[SelectLayerIdx]->SetTile(Idx, brushFrame, 0, 0, brushColor);
		}

	}

	
	for (int i = 0; i < MAXLAYER; i++) {
		map[i]->Update();
	}
	LineX->Update();
	LineY->Update();
}

void Main::LateUpdate()
{
}

void Main::Render()
{
	for (int i = 0; i < MAXLAYER; i++) {
		map[i]->Render();
	}

	LineX->Render();
	LineY->Render();
}

void Main::ResizeScreen()
{
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"MapTool");
	app.SetInstance(instance);
	app.InitWidthHeight(1400.f, 700.0f);
	app.background = Color(0.3, 0.3, 0.3);
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}