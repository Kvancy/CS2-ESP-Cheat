#pragma once
struct point3D
{
	float x, y, z;
};
struct Matrix4x4 {
	float m[4][4];
};
struct point2D {
	float x, y;
};
class kPlayerPawn
{
public:
	kPlayerPawn();
	~kPlayerPawn();
	int getHealth();
	point3D getPos();
	point3D getPosHead();
	int getTeamNum();
	bool isAlive();

	friend class kGame;
private:
	int m_iHealth = 0;
	point3D m_pPos = { 0 };
	int m_iTeamNum = 0;
	bool m_bPawnIsAlive = 0;
	point3D m_pHead = { 0 };
	


};




