#include "DXUT.h"
#include "cCityNightScene.h"

cCityNightScene::cCityNightScene()
{
}

cCityNightScene::~cCityNightScene()
{
	Release();
}

void cCityNightScene::Init()
{
	cParentScene::Init("cCityNightScene");

	srand(time(NULL));
	left = false; right = true; pos_x = 0;
	isStop = false;
	IMAGE->DeleteImage("city(night)_High");
	IMAGE->DeleteImage("city(night)_Under");
	IMAGE->AddImage("city(night)_High", "Ingame/City(night)/high");
	IMAGE->AddImage("city(night)_Under", "Ingame/City(night)/under");
	cTexture* ptr[2] = {IMAGE->FindImage("city(night)_High"), IMAGE->FindImage("city(night)_Under") };
	player = new cPlayer(ptr);
	bullet = new cBulletAdmin();
	mob = new cMobAdmin(bullet->m_bullets);
	item = new cItemAdmin(player);
	coll = new cCollision(mob->m_bullets, mob->m_mobs, player, item);
}

void cCityNightScene::Update()
{
	if (player->timer <= 0)
	{
		isFail = true;
		cParentScene::SetPercent(player->coloring_per);
		//cParentScene::SetScore(player->score);
	}

	if (player->coloring_per >= 80)
	{
		isClear = true;
		cParentScene::SetPercent(player->coloring_per);
		//cParentScene::SetScore(player->score);
	}

	if (isStart && !isStop && !isClear && !isFail)
	{
		player->Update(mob->bossPos);
		bullet->Update();
		mob->Update();
		item->Update();
		coll->Update();
	}

	if (INPUT->KeyDown(VK_ESCAPE)) isStop = !isStop;

	cParentScene::Update();
}

void cCityNightScene::Render()
{
	player->Render();
	if (isStart && !isStop && !isClear && !isFail)
	{
		bullet->Render();
		mob->Render();
		item->Render();
	}
	cParentScene::Render();
}

void cCityNightScene::UIRender()
{
	player->UIRender();
	mob->UIRender();
}

void cCityNightScene::Release()
{
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(mob);
	SAFE_DELETE(item);
	SAFE_DELETE(coll);
}