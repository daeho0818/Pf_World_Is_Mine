#pragma once
class cReflexBullet
	:public cBullet
{
public:
	cReflexBullet(Vec2 pos, Vec2 dir, cTexture* ptr, float damage, float size, float speed, bool dead = false);
	~cReflexBullet();

	bool dead;
	float m_speed;

	cTimer* t_Dead = nullptr;

	cTexture* ptr = nullptr;

	// cBullet을(를) 통해 상속됨
	virtual void Update() override;
	virtual void Render() override;

	string ChkOut();
};