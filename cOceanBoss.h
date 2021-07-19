#pragma once
#include "cMob.h"
class cOceanBoss
	:public cMob
{
public:
	cOceanBoss(Vec2 pos, vector<cBullet*>& bullet, float size = 1);
	~cOceanBoss();

	float angle = 0;
	float rad = D3DX_PI * 2 / 25;

	int dirIndex = 0;

	vector<cBullet*>& m_bullets;

	// cMob을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;
};