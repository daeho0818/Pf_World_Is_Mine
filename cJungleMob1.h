#pragma once
class cJungleMob1
	:public cMob
{
public:
	cJungleMob1(Vec2 pos);
	~cJungleMob1();
	
	float dir_x = 1;
	float dir_y = 1;

	// cMob��(��) ���� ��ӵ�
	virtual void Update() override;
	virtual void Render() override;

	string ChkOut();
};
