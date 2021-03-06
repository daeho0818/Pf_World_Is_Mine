#include "DXUT.h"
#include "cMainGame.h"
#include "cLoadingScene.h"

cMainGame::cMainGame()
{
}

cMainGame::~cMainGame()
{
}

void cMainGame::Init()
{
	SCENE->AddScene("cLoadingScene", new cLoadingScene);
	SCENE->ChangeScene("cLoadingScene");
}

void cMainGame::Update()
{
	MOUSE->Update();
	INPUT->Update();
	PART->Update();
	SCENE->Update();
	SOUND->Update();
	CAM->Update();
	SOUND->Update();
}

void cMainGame::Render()
{
	if (!BG->isLoadScene)
		BG->Render();
	PART->Render();
	SCENE->Render();
	UI->Begin();
	SCENE->UIRender();
	UI->End();
	CAM->Render();
}

void cMainGame::Release()
{
	cInputManager::ReleaseInstance();
	cParticleManager::ReleaseInstance();
	cRenderManager::ReleaseInstance();
	cSceneManager::ReleaseInstance();
	cUIManager::ReleaseInstance();
	cSoundManager::ReleaseInstance();
	cMouseManager::ReleaseInstance();
	cButtonManager::ReleaseInstance();
	cImageManager::ReleaseInstance();
	cBGManager::ReleaseInstance();
	cCameraManager::ReleaseInstance();
	cMouseManager::ReleaseInstance();
}

void cMainGame::ResetDevice()
{
	UI->Reset();
}

void cMainGame::LostDevice()
{
	UI->Lost();
}
