#include "DXUT.h"
#include "cOceanMob1.h"

cOceanMob1::cOceanMob1(Vec2 pos)
	:cMob(pos)
{
	m_image = IMAGE->MakeVecImg("ocean_mob1");
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
}

cOceanMob1::~cOceanMob1()
{
}

void cOceanMob1::Update()
{
	if (m_Ani != nullptr) m_Ani->Update();

	if (m_Ani == nullptr)
	{
		m_Ani = new cTimer(0.1, [&]()->void {
			index++;
			if (index == m_image.size()) index = 0;
			m_Ani = nullptr;
			});
	}

	if (ChkOut() == "Left" || ChkOut() == "Right")
	{
		dir_x *= -1;
	}
	if (ChkOut() == "Up" || ChkOut() == "Down")
	{
		dir_y *= -1;
	}
	m_pos += {1 * dir_x, 1 * dir_y};
}

void cOceanMob1::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, 1.5);
}


string cOceanMob1::ChkOut()
{
	if (SCENE->Array[(int)m_pos.y][(int)m_pos.x + 1] == 2)
		return "Right";
	if (SCENE->Array[(int)m_pos.y][(int)m_pos.x - 1] == 2)
		return "Left";
	if (SCENE->Array[(int)m_pos.y + 1][(int)m_pos.x] == 2)
		return "Down";
	if (SCENE->Array[(int)m_pos.y - 1][(int)m_pos.x] == 2)
		return "Up";
	return "";
}