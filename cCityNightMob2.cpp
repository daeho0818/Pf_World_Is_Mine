#include "DXUT.h"
#include "cCityNightMob2.h"
#include "cReflexBullet.h"

cCityNightMob2::cCityNightMob2(Vec2 pos, vector<cBullet*>& bullets, float size)
	:cMob(pos, size), m_bullets(bullets)
{
	m_image = IMAGE->MakeVecImg("city(night)_mob2");
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
}

cCityNightMob2::~cCityNightMob2()
{
}

void cCityNightMob2::Update()
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
						dir = { 0, 1 * (float)i };
						D3DXVec2Normalize(&dir, &dir);
						m_bullets.push_back(new cReflexBullet(m_pos, dir, "bullet_city(night)_mob2", "city(night)_mob2_effect", "mob", m_damage, 0.5, 400, true));
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
	m_pos += {2 * dir_x, 2 * dir_y};
}

void cCityNightMob2::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, m_size);
}