#include "DXUT.h"
#include "cOceanMob1.h"
#include "cReflexBullet.h"

cOceanMob1::cOceanMob1(Vec2 pos, vector<cBullet*>& bullets, float size)
	:cMob(pos, size), m_bullets(bullets)
{
	m_image = IMAGE->MakeVecImg("ocean_mob1");
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
	speed = 2;
}

cOceanMob1::~cOceanMob1()
{
}

void cOceanMob1::Update()
{
	if (t_Pattern1 != nullptr) t_Pattern1->Update();
	if (p1Count < 5)
	{
		if (t_Pattern1 == nullptr)
		{
			t_Pattern1 = new cTimer(0.4, [&]()->void {
				Vec2 dir;
				for (int i = -5; i <= 5; i++)
				{
					if (i != 0)
					{
						dir = { 1 * (float)i, 0 };
						D3DXVec2Normalize(&dir, &dir);
						m_bullets.push_back(new cReflexBullet(m_pos, dir, "bullet_ocean_mob1", "ocean_mob1_effect", "mob",m_damage, 0.5, 400, true));
					}
				}
				p1Count++;
				t_Pattern1 = nullptr;
				});
		}
	}
	else
	{
		if (t_Pattern1 == nullptr)
			t_Pattern1 = new cTimer(5, [&]() -> void { p1Count = 0; t_Pattern1 = nullptr; });
	}

	if (ChkOut() == "Left" || ChkOut() == "Right")
	{
		dir_x *= -1;
	}
	if (ChkOut() == "Up" || ChkOut() == "Down")
	{
		dir_y *= -1;
	}
	m_pos += {speed * dir_x, speed * dir_y};
}

void cOceanMob1::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, m_size);
}
