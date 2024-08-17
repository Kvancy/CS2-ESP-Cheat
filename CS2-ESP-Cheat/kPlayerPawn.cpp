#include "kPlayerPawn.h"

kPlayerPawn::kPlayerPawn()
{

}

kPlayerPawn::~kPlayerPawn()
{

}

int kPlayerPawn::getHealth()
{
	return m_iHealth;
}

point3D kPlayerPawn::getPos()
{
	return m_pPos;
}

point3D kPlayerPawn::getPosHead()
{
	return m_pHead;
}

int kPlayerPawn::getTeamNum()
{
	return m_iTeamNum;
}

bool kPlayerPawn::isAlive()
{
	return m_iHealth != 0;
}
