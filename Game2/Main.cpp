#include "stdafx.h"
#include "Scene1.h"

#include "Scene3.h"
#include "Main.h"

Main::Main()
{
	for (int i = 0; i < SoundSize; i++) {
		Sound[i] = 0.5;
	}
	Sound[0] = 0.35f;
	Sound[1] = 0.2f;
	Sound[2] = 1.0f;



}

Main::~Main()
{

}
void Main::Init()
{
	// 공격타워
	SOUND->AddSound("FX_UNI_MachineGunEffect_Cast_01.ogg", "GunFire1", false);
	SOUND->AddSound("FX_UNI_MachineGunEffect_Cast_02.ogg", "GunFire2", false);
	SOUND->AddSound("FX_UNI_MachineGunEffect_Cast_03.ogg", "GunFire3", false);
	SOUND->AddSound("FX_UNI_MachineGunEffect_Cast_04.ogg", "GunFire4", false);
	SOUND->AddSound("FX_UNI_MachineGunEffect_Cast_05.ogg", "GunFire5", false);
	
	// 건물 지을때
	SOUND->AddSound("ui_garrison_start_building.ogg", "BuildTrue", false);
	// 건물 중복된 위치에 지을려고할때
	SOUND->AddSound("Error.ogg", "BuildError", false);
	// 건물 파괴
	SOUND->AddSound("Ulduar_Kologarn_FocusedEyeBeam_Impact_1.ogg", "break1", false);
	SOUND->AddSound("Ulduar_Kologarn_FocusedEyeBeam_Impact_2.ogg", "break2", false);
	SOUND->AddSound("Ulduar_Kologarn_FocusedEyeBeam_Impact_3.ogg", "break3", false);

	// 수리타워
	SOUND->AddSound("BlackSmithCraftingA.ogg", "RePairTower1", false);
	SOUND->AddSound("BlackSmithCraftingB.ogg", "RePairTower2", false);
	SOUND->AddSound("BlackSmithCraftingC.ogg", "RePairTower3", false);

	// 플레이어 벽 부실때
	SOUND->AddSound("FX_Rock_Large_Impact_01.ogg", "BreakGround1", false);
	SOUND->AddSound("FX_Rock_Large_Impact_02.ogg", "BreakGround2", false);
	SOUND->AddSound("FX_Rock_Large_Impact_03.ogg", "BreakGround3", false);
	SOUND->AddSound("FX_Rock_Large_Impact_04.ogg", "BreakGround4", false);

	// 코뿔소 사운드
	SOUND->AddSound("FX_RockImpact_Heavy_Short_01.ogg", "Heavy_Short1", false);
	SOUND->AddSound("FX_RockImpact_Heavy_Short_02.ogg", "Heavy_Short2", false);
	SOUND->AddSound("FX_RockImpact_Heavy_Short_03.ogg", "Heavy_Short3", false);
	SOUND->AddSound("FX_RockImpact_Heavy_Short_04.ogg", "Heavy_Short4", false);
	// 코뿔소 죽는소리
	SOUND->AddSound("FelGolemDeath.ogg", "Heavy_Death", false);


	// 벌레 죽는소리
	SOUND->AddSound("FX_PA_Antique_Bugsprayer_Fire_01.ogg", "Bugsprayer_Death1", false);
	SOUND->AddSound("FX_PA_Antique_Bugsprayer_Fire_02.ogg", "Bugsprayer_Death2", false);
	SOUND->AddSound("FX_PA_Antique_Bugsprayer_Fire_03.ogg", "Bugsprayer_Death3", false);

	// 새 사운드
	SOUND->AddSound("BlackRockV2_Drake_WingFlap_01.ogg", "WingFlap1", false);
	SOUND->AddSound("BlackRockV2_Drake_WingFlap_02.ogg", "WingFlap2", false);
	SOUND->AddSound("BlackRockV2_Drake_WingFlap_03.ogg", "WingFlap3", false);
	SOUND->AddSound("BlackRockV2_Drake_WingFlap_04.ogg", "WingFlap4", false);
	SOUND->AddSound("BlackRockV2_Drake_WingFlap_05.ogg", "WingFlap5", false);
	SOUND->AddSound("BlackRockV2_Drake_WingFlap_06.ogg", "WingFlap6", false);

	// 벌래 사운드
	SOUND->AddSound("Spell_83_NZothRaid_BugDuo_HivemindSwap_Periodic_01.ogg", "BugDuo1", false);
	SOUND->AddSound("Spell_83_NZothRaid_BugDuo_HivemindSwap_Periodic_02.ogg", "BugDuo2", false);
	SOUND->AddSound("Spell_83_NZothRaid_BugDuo_HivemindSwap_Periodic_03.ogg", "BugDuo3", false);
	SOUND->AddSound("Spell_83_NZothRaid_BugDuo_HivemindSwap_Periodic_04.ogg", "BugDuo4", false);

	// 타이틀
	SOUND->AddSound("Title  CrossCode Original Game Soundtrack.mp3", "Title", true);

	// 레벨업
	SOUND->AddSound("inn4.ogg", "LevelUp", false);
	// 종료
	SOUND->AddSound("item2.ogg", "Exit", false);
	// 메뉴 오픈
	SOUND->AddSound("[SE]MenuOpen.ogg", "MenuOpen", false);
	// 확인
	SOUND->AddSound("[SE]Enter.ogg", "Enter", false);
	// 취소
	SOUND->AddSound("[SE]Cancel.ogg", "Cancel", false);

	SOUND->AddSound("Progenitorjellyfish_attack_ (1)", "fish1", false);
	SOUND->AddSound("Progenitorjellyfish_attack_ (2)", "fish2", false);
	SOUND->AddSound("Progenitorjellyfish_attack_ (3)", "fish3", false);
	SOUND->AddSound("Progenitorjellyfish_attack_ (4)", "fish4", false);
	SOUND->AddSound("Progenitorjellyfish_attack_ (5)", "fish5", false);
	SOUND->AddSound("Progenitorjellyfish_attack_ (6)", "fish6", false);
	SOUND->AddSound("Progenitorjellyfish_attack_ (7)", "fish7", false);
	SOUND->AddSound("Progenitorjellyfish_attack_ (8)", "fish8", false);
	SOUND->AddSound("Progenitorjellyfish_attack_ (9)", "fish9", false);
	SOUND->AddSound("Progenitorjellyfish_attack_ (10)", "fish10", false);
	SOUND->AddSound("Progenitorjellyfish_attack_ (11)", "fish11", false);


	Scene1* sc1 = new Scene1();
	SCENE->AddScene("SC1", sc1);



	Scene3* sc3 = new Scene3();
	SCENE->AddScene("SC3", sc3);


	SCENE->ChangeScene("SC3");
}

void Main::Release()
{
}

void Main::Update()
{
	// 0.7
	SOUND->SetVolume("Title", 0.7);
	// 0.35
	SOUND->SetVolume("GunFire1", 0.25);
	SOUND->SetVolume("GunFire2", 0.25);
	SOUND->SetVolume("GunFire3", 0.25);
	SOUND->SetVolume("GunFire4", 0.25);
	SOUND->SetVolume("GunFire5", 0.25);
	// 0.2
	SOUND->SetVolume("BuildTrue", 0.2);
	// 1.0
	SOUND->SetVolume("BuildError", 1.0);
	// 0.2
	SOUND->SetVolume("RePairTower1", 0.2);
	SOUND->SetVolume("RePairTower2", 0.2);
	SOUND->SetVolume("RePairTower3", 0.2);
	// 0.5
	SOUND->SetVolume("BreakGround1", 0.5);
	SOUND->SetVolume("BreakGround2", 0.5);
	SOUND->SetVolume("BreakGround3", 0.5);
	SOUND->SetVolume("BreakGround4", 0.5);
	// 0.5
	SOUND->SetVolume("Heavy_Short1", 0.6);
	SOUND->SetVolume("Heavy_Short2", 0.6);
	SOUND->SetVolume("Heavy_Short3", 0.6);
	SOUND->SetVolume("Heavy_Short4", 0.6);
	// 0.5
	SOUND->SetVolume("Bugsprayer_Death1", 0.5);
	SOUND->SetVolume("Bugsprayer_Death2", 0.5);
	SOUND->SetVolume("Bugsprayer_Death3", 0.5);
	// 0.5
	SOUND->SetVolume("WingFlap1", 0.5);
	SOUND->SetVolume("WingFlap2", 0.5);
	SOUND->SetVolume("WingFlap3", 0.5);
	SOUND->SetVolume("WingFlap4", 0.5);
	SOUND->SetVolume("WingFlap5", 0.5);
	SOUND->SetVolume("WingFlap6", 0.5);
	// 0.5
	SOUND->SetVolume("BugDuo1", 0.2);
	SOUND->SetVolume("BugDuo2", 0.2);
	SOUND->SetVolume("BugDuo3", 0.2);
	SOUND->SetVolume("BugDuo4", 0.2);

	for (int i = 0; i < SoundSize; i++) {
		if (Sound[i] < 0.0f) {
			Sound[i] = 0.0f;
			break;
		}
		if (Sound[i] > 1.0f) {
			Sound[i] = 1.0f;
			break;
		}
	}

	SCENE->Update();
}

void Main::LateUpdate()
{
	SCENE->LateUpdate();
}

void Main::Render()
{
	SCENE->Render();
}

void Main::ResizeScreen()
{
	SCENE->ResizeScreen();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	app.SetAppName(L"Game2");
	app.SetInstance(instance);
	app.InitWidthHeight(1600, 900);

	app.fixFrame = 60;
	WIN->Create();
	Main* main = new Main();
	int wParam = (int)WIN->Run(main);
	SafeDelete(main);
	WIN->Destroy();
	WIN->DeleteSingleton();

	return wParam;
}