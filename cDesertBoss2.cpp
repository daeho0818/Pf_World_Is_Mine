#include  "DXUT.h"
#include "cDesertBoss2.h"
#include "cMBullet.h"

cDesertBoss2::cDesertBoss2(Vec2 pos, vector<cBullet*>& bullet, float size)
	: cMob(pos, size), m_bullets(bullet)
{
	m_image = IMAGE->MakeVecImg("desert_boss2");
	mobName = "silver";
	mobType = "Boss";

	m_damage = 1;
	speed = 1;

	isStop = false;
	rand() % 2 == 1 ? dir_x = 1 : dir_x = -1;
	rand() % 2 == 1 ? dir_y = 1 : dir_y = -1;
	pattern1 = false;
	pattern2 = true;
	pattern3 = false;
}

cDesertBoss2::~cDesertBoss2()
{
	SAFE_DELETE(t_Pattern2);
}

void cDesertBoss2::CircleBullet(float interval, bool random)
{
	float angle = 0;
	float rad = D3DX_PI * 2 / 25;

	for (int i = 0; i < 365; i++, angle += rad)
	{
		if (random)
		{
			if (i == rand() % 365)
			{
				Vec2 direction = Vec2(m_pos.x + (cosf(angle) * 5), m_pos.y + (sinf(angle) * 5));
				direction = direction - m_pos;
				D3DXVec2Normalize(&direction, &direction);
				m_bullets.push_back(new cMBullet(m_pos, direction, "bullet_desert_boss2", "desert_boss2_effect", "boss", m_damage, 0.5, 400));
			}
		}
		else
		{
			Vec2 direction = Vec2(m_pos.x + (cosf(angle) * (5 + interval)), m_pos.y + (sinf(angle) * (5 + interval)));
			direction = direction - m_pos;
			D3DXVec2Normalize(&direction, &direction);
			m_bullets.push_back(new cMBullet(m_pos, direction, "bullet_desert_boss2", "desert_boss2_effect", "boss", m_damage, 0.5, 400));
		}
	}
}

void cDesertBoss2::Update()
{
	if (t_Pattern1 != nullptr) t_Pattern1->Update();
	if (t_Pattern2 != nullptr) t_Pattern2->Update();
	if (t_Pattern3 != nullptr) t_Pattern3->Update();

	if (pattern1)
	{
		if (p1Count < 10)
		{
			if (t_Pattern1 == nullptr) t_Pattern1 = new cTimer(0.5, [&]()->void {
				isStop = true;
				p1Count++;
				t_Pattern1 = nullptr;
				});
		}
		else
		{
			p1Count = 0;
			pattern1 = false;
			isStop = false;
			pattern3 = true;
		}
	}
	else
	{
		if (pattern2)
		{
			if (t_Pattern2 == nullptr) t_Pattern2 = new cTimer(10, [&]()->void {
				pattern1 = true;
				t_Pattern2 = nullptr;
				isStop = true;
				});
		}
	}
	if (pattern3)
	{
		if (p3Count < 3)
		{
			if (t_Pattern3 == nullptr) t_Pattern3 = new cTimer(1, [&]()->void {
				float temp = 5;
				p3Count++;
				CircleBullet(temp * p3Count);
				t_Pattern3 = nullptr;
				});
		}
		else
		{
			pattern3 = false;
			p3Count = 0;
		}
	}

	if (isStop) { CircleBullet(0, true); }

	if (ChkOut() == "Left" || ChkOut() == "Right")
	{
		dir_x *= -1;
	}
	if (ChkOut() == "Up" || ChkOut() == "Down")
	{
		dir_y *= -1;
	}
	if (!isStop)
		m_pos += {speed * dir_x, speed * dir_y};
}

void cDesertBoss2::Render()
{
	RENDER->CenterRender(m_image[index], m_pos, m_size);
}