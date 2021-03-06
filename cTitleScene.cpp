#include "DXUT.h"
#include "cTitleScene.h"

cTitleScene::cTitleScene()
{
}

cTitleScene::~cTitleScene()
{
}

void cTitleScene::Init()
{
	BUTTON->AddButton("start_button", Vec2(600, 250), 0.6);
	BUTTON->AddButton("guide_button", Vec2(600, 650), 0.6);
	BUTTON->AddButton("adven_button", Vec2(600, 1050), 0.6);
	BUTTON->AddButton("develop_button", Vec2(600, 1450), 0.6);
	BUTTON->AddButton("quit_button", Vec2(600, 1850), 0.6);

	BUTTON->AddButton("guide_close", Vec2(3000, WINSIZEY / 2 - 1000));
	BUTTON->AddButton("X", Vec2(3330, WINSIZEY / 2 - 1023), 0.6);

	BUTTON->AddButton("Arrow", Vec2(500, 2100), 1.5);

	guideUI = false;
	advenUI = false;
	developUI = false;
	buttonsMoved = false;
	movedEnd = true;
	temp = 0;
	count = 0;
	logoPos = { WINSIZEX / 2, 500 };
	arrowKey = "Arrow";
	memset(move, false, sizeof(move));
	move[0] = true;
	speed = 1;

	tempFunc = [&](int index) -> void {
		switch (index)
		{
		case 0:
			RENDER->CenterRender(IMAGE->FindImage("start_button"), Vec2(600, 250 - temp), 0.6);
			RENDER->CenterRender(IMAGE->FindImage("start_note"), { 170, 250 - temp });
			break;
		case 1:
			RENDER->CenterRender(IMAGE->FindImage("guide_button"), Vec2(600, 650 - temp), 0.6);
			RENDER->CenterRender(IMAGE->FindImage("guide_note"), { 170, 650 - temp });
			break;
		case 2:
			RENDER->CenterRender(IMAGE->FindImage("adven_button"), Vec2(600, 1050 - temp), 0.6);
			RENDER->CenterRender(IMAGE->FindImage("adven_note"), { 170, 1050 - temp });
			break;
		case 3:
			RENDER->CenterRender(IMAGE->FindImage("develop_button"), Vec2(600, 1450 - temp), 0.6);
			RENDER->CenterRender(IMAGE->FindImage("develop_note"), { 170, 1450 - temp });
			break;
		case 4:
			RENDER->CenterRender(IMAGE->FindImage("quit_button"), Vec2(600, 1850 - temp), 0.6);
			RENDER->CenterRender(IMAGE->FindImage("quit_note"), { 170, 1850 - temp });
			break;
		}
	};

	BUTTON->ChangeBtnInfo("Arrow", { 500, 2100 }, 1.5f);
}

void cTitleScene::Update()
{
	if (t_Delay != nullptr) t_Delay->Update();
	if (guideUI) if (INPUT->KeyDown(VK_ESCAPE)) guideUI = false;
	if (advenUI) if (INPUT->KeyDown(VK_ESCAPE)) advenUI = false;
	if (developUI) if (INPUT->KeyDown(VK_ESCAPE)) developUI = false;

	speed += 0.5;
	logoPos.y += sin(0.1 * speed);

	if (buttonsMoved)
	{
		if (t_Delay == nullptr && count <= 19)
		{
			t_Delay = new cTimer(0.01, [&]()->void {
				for (auto iter : BUTTON->m_buttons)
				{
					if (movedEnd)
						iter->m_pos -= Vec2(0, 100);
					else
						iter->m_pos += Vec2(0, 100);
				}
				if (movedEnd)
					temp += 100;
				else
					temp -= 100;

				count++;
				t_Delay = nullptr;
				});
		}
		else if (count > 19)
		{
			if (movedEnd)
				BUTTON->ChangeBtnInfo("Arrow", { 500, 100 }, 1.5f);
			else
				BUTTON->ChangeBtnInfo("Arrow", { 500, 2100 }, 1.5f);
			movedEnd = !movedEnd;
			if (movedEnd)
				arrowKey = "Arrow";
			else
				arrowKey = "_Arrow";
			buttonsMoved = false;
			count = 0;
		}
	}
	if (MOUSE->lUp)
	{
		if (!buttonsMoved && movedEnd)
		{
			if (!guideUI && !advenUI && !developUI)
			{
				if (MOUSE->LButtonClick("start_button"))
				{
					SCENE->ChangeScene("cSelectStageScene");
				}
				else if (MOUSE->LButtonClick("guide_button"))
				{
					guideUI = true;
				}
				else if (MOUSE->LButtonClick("adven_button"))
				{
					advenUI = true;
				}
				else if (MOUSE->LButtonClick("quit_button"))
				{
					PostQuitMessage(0);
				}
				else if (MOUSE->LButtonClick("develop_button"))
				{
					developUI = true;
				}
			}
			else if (guideUI)
			{
				if (MOUSE->LButtonClick("guide_close"))
				{
					guideUI = false;
				}
			}
		}
		if (MOUSE->LButtonClick("X"))
		{
			if (advenUI)
			{
				advenUI = false;
			}
			if (developUI)
			{
				developUI = false;
			}
		}
		if (MOUSE->LButtonClick("Arrow") && !buttonsMoved)
		{
			if (!guideUI && !advenUI && !developUI)
				buttonsMoved = true;
		}
		MOUSE->lUp = false;
	}
}

void cTitleScene::Render()
{
	RENDER->CenterRender(IMAGE->FindImage("TitleBG"), { WINSIZEX / 2, WINSIZEY / 2 });
	RENDER->CenterRender(IMAGE->FindImage("Logo"), { logoPos.x, logoPos.y - temp }, 0.5);
	RENDER->CenterRender(IMAGE->FindImage("pattern"), { 500, 1000 - temp });

	RENDER->CenterRender(IMAGE->FindImage(arrowKey), Vec2(500, 2100 - temp), 1.5);

	if (!guideUI && !advenUI && !developUI)
	{
		MOUSE->Collider("start_button") ?
			MOUSE->lStay && MOUSE->Collider("start_button", MOUSE->lDownPos) ?
			RENDER->CenterRender(IMAGE->FindImage("click_Start"), Vec2(600, 250 - temp)) :
			RENDER->CenterRender(IMAGE->FindImage("over_Start"), Vec2(600, 250 - temp)) :
			tempFunc(0);

		MOUSE->Collider("guide_button") ?
			MOUSE->lStay && MOUSE->Collider("guide_button", MOUSE->lDownPos) ?
			RENDER->CenterRender(IMAGE->FindImage("click_Guide"), Vec2(600, 650 - temp)) :
			RENDER->CenterRender(IMAGE->FindImage("over_Guide"), Vec2(600, 650 - temp)) :
			tempFunc(1);

		MOUSE->Collider("adven_button") ?
			MOUSE->lStay && MOUSE->Collider("adven_button", MOUSE->lDownPos) ?
			RENDER->CenterRender(IMAGE->FindImage("click_Adven"), Vec2(600, 1050 - temp)) :
			RENDER->CenterRender(IMAGE->FindImage("over_Adven"), Vec2(600, 1050 - temp)) :
			tempFunc(2);

		MOUSE->Collider("develop_button") ?
			MOUSE->lStay && MOUSE->Collider("develop_button", MOUSE->lDownPos) ?
			RENDER->CenterRender(IMAGE->FindImage("click_Develop"), Vec2(600, 1450 - temp)) :
			RENDER->CenterRender(IMAGE->FindImage("over_Develop"), Vec2(600, 1450 - temp)) :
			tempFunc(3);

		MOUSE->Collider("quit_button") ?
			MOUSE->lStay && MOUSE->Collider("quit_button", MOUSE->lDownPos) ?
			RENDER->CenterRender(IMAGE->FindImage("click_Quit"), Vec2(600, 1850 - temp)) :
			RENDER->CenterRender(IMAGE->FindImage("over_Quit"), Vec2(600, 1850 - temp)) :
			tempFunc(4);
	}
	else
	{
		for (int i = 0; i < 5; i++)
			tempFunc(i);
	}


	if (guideUI)
	{
		RENDER->CenterRender(IMAGE->FindImage("Blur"), Vec2{ WINSIZEX / 2, WINSIZEY / 2 });
		RENDER->CenterRender(IMAGE->FindImage("guide_BG"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.8);
		RENDER->CenterRender(IMAGE->FindImage("guide_text1"), Vec2(WINSIZEX / 2, WINSIZEY / 2), 0.8);
		RENDER->CenterRender(IMAGE->FindImage("guide_close"), Vec2(3000, WINSIZEY / 2 - 1000));
	}
	else if (advenUI)
	{
		RENDER->CenterRender(IMAGE->FindImage("Blur"), Vec2{ WINSIZEX / 2, WINSIZEY / 2 });
		RENDER->CenterRender(IMAGE->FindImage("adven_BG"), Vec2(WINSIZEX / 2 + 25, WINSIZEY / 2), 0.8);

		if (SCENE->a_rewards[0] != 1)
		{
			RENDER->CenterRender(IMAGE->FindImage("adven_Chain"), Vec2(920, 500), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_DontClear"), Vec2(1450, 500), 0.25);
		}
		else
		{
			RENDER->CenterRender(IMAGE->FindImage("church_item"), Vec2(920, 500), 0.4);
			RENDER->CenterRender(IMAGE->FindImage("church_con"), Vec2(1450, 500), 0.4);
		}

		if (SCENE->a_rewards[1] != 1)
		{
			RENDER->CenterRender(IMAGE->FindImage("adven_Chain"), Vec2(920, 912), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_DontClear"), Vec2(1450, 912), 0.25);
		}
		else
		{
			RENDER->CenterRender(IMAGE->FindImage("city_item"), Vec2(920, 912), 0.4);
			RENDER->CenterRender(IMAGE->FindImage("city_con"), Vec2(1450, 912), 0.4);
		}

		if (SCENE->a_rewards[2] != 1)
		{
			RENDER->CenterRender(IMAGE->FindImage("adven_Chain"), Vec2(920, 1330), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_DontClear"), Vec2(1450, 1330), 0.25);
		}
		else
		{
			RENDER->CenterRender(IMAGE->FindImage("city(night)_item"), Vec2(920, 1330), 0.4);
			RENDER->CenterRender(IMAGE->FindImage("city(night)_con"), Vec2(1450, 1330), 0.4);
		}

		if (SCENE->a_rewards[3] != 1)
		{
			RENDER->CenterRender(IMAGE->FindImage("adven_Chain"), Vec2(920, 1748), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_DontClear"), Vec2(1450, 1748), 0.25);
		}
		else
		{
			RENDER->CenterRender(IMAGE->FindImage("desert_item"), Vec2(920, 1748), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("desert_con"), Vec2(1450, 1748), 0.4);
		}

		if (SCENE->a_rewards[4] != 1)
		{
			RENDER->CenterRender(IMAGE->FindImage("adven_Chain"), Vec2(2220, 500), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_DontClear"), Vec2(2725, 500), 0.25);
		}
		else
		{
			RENDER->CenterRender(IMAGE->FindImage("jungle_item"), Vec2(2220, 500), 0.4);
			RENDER->CenterRender(IMAGE->FindImage("jungle_con"), Vec2(2725, 500), 0.4);
		}

		if (SCENE->a_rewards[5] != 1)
		{
			RENDER->CenterRender(IMAGE->FindImage("adven_Chain"), Vec2(2220, 912), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_DontClear"), Vec2(2725, 912), 0.25);
		}
		else
		{
			RENDER->CenterRender(IMAGE->FindImage("ice_item"), Vec2(2220, 912), 0.35);
			RENDER->CenterRender(IMAGE->FindImage("ice_con"), Vec2(2725, 912), 0.4);
		}

		if (SCENE->a_rewards[6] != 1)
		{
			RENDER->CenterRender(IMAGE->FindImage("adven_Chain"), Vec2(2220, 1330), 0.3);
			RENDER->CenterRender(IMAGE->FindImage("adven_DontClear"), Vec2(2725, 1330), 0.25);
		}
		else
		{
			RENDER->CenterRender(IMAGE->FindImage("ocean_item"), Vec2(2220, 1330), 0.35);
			RENDER->CenterRender(IMAGE->FindImage("ocean_con"), Vec2(2725, 1330), 0.4);
		}

		RENDER->CenterRender(IMAGE->FindImage("symbol_church"), Vec2(1850, 460), 0.2);
		RENDER->CenterRender(IMAGE->FindImage("symbol_church_name"), Vec2(1850, 580), 0.25);

		RENDER->CenterRender(IMAGE->FindImage("symbol_city"), Vec2(1850, 880), 0.2);
		RENDER->CenterRender(IMAGE->FindImage("symbol_city_name"), Vec2(1850, 990), 0.25);

		RENDER->CenterRender(IMAGE->FindImage("symbol_city(night)"), Vec2(1850, 1290), 0.2);
		RENDER->CenterRender(IMAGE->FindImage("symbol_city(night)_name"), Vec2(1850, 1400), 0.25);

		RENDER->CenterRender(IMAGE->FindImage("symbol_desert"), Vec2(1850, 1720), 0.2);
		RENDER->CenterRender(IMAGE->FindImage("symbol_desert_name"), Vec2(1850, 1820), 0.25);

		RENDER->CenterRender(IMAGE->FindImage("symbol_jungle"), Vec2(3140, 450), 0.25);
		RENDER->CenterRender(IMAGE->FindImage("symbol_jungle_name"), Vec2(3140, 560), 0.25);

		RENDER->CenterRender(IMAGE->FindImage("symbol_ice"), Vec2(3140, 890), 0.2);
		RENDER->CenterRender(IMAGE->FindImage("symbol_ice_name"), Vec2(3140, 1000), 0.25);

		RENDER->CenterRender(IMAGE->FindImage("symbol_ocean"), Vec2(3140, 1300), 0.2);
		RENDER->CenterRender(IMAGE->FindImage("symbol_ocean_name"), Vec2(3140, 1410), 0.25);

		//RENDER->CenterRender(IMAGE->FindImage("adven_CollectionPerBG"), Vec2(350, WINSIZEY - 420), 0.5);
		//RENDER->CenterRender(IMAGE->FindImage("adven_CollectionPer"), Vec2(350, WINSIZEY - 420), 0.7);

		RENDER->CenterRender(IMAGE->FindImage("X"), Vec2(3330, WINSIZEY / 2 - 1023), 0.6);
		BUTTON->ChangeBtnInfo("X", Vec2(3330, WINSIZEY / 2 - 1023), 0.6);
	}
	else if (developUI)
	{
		RENDER->CenterRender(IMAGE->FindImage("Credit"), Vec2(WINSIZEX / 2, WINSIZEY / 2));
		RENDER->CenterRender(IMAGE->FindImage("X"), Vec2(3900, WINSIZEY / 2 - 1023), 0.6);
		BUTTON->ChangeBtnInfo("X", Vec2(3900, WINSIZEY / 2 - 1023), 0.6);
	}
}

void cTitleScene::UIRender()
{

}

void cTitleScene::Release()
{
}
