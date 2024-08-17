#include "kGame.h"

kGame::kGame(const TCHAR* proc_name, RECT rect)
{
	mem::Process* proc = new mem::Process(proc_name);
	this->cs2 = proc;
	this->m_rect = rect;
}

kGame::~kGame()
{

}

bool kGame::refreshData()
{
	auto client = cs2->get_module_handle(TEXT("client.dll"));
	DWORD64 entityListEntry = 0;
	cs2->read<DWORD64>(client + cs2_dumper::offsets::client_dll::dwEntityList, entityListEntry);
	int loopIndex = 0;
	int playerIndex = -1;
	while (1)
	{
		loopIndex++;
		playerIndex++;
		if (playerIndex == 10)
			break;

		DWORD64 list_entry = 0;
		if (!cs2->read<DWORD64>(entityListEntry + (8 * (loopIndex & 0x7FFF) >> 9) + 0x10, list_entry))
			continue;
		if (!list_entry) break;

		DWORD64 entity = 0;
		if (!cs2->read<DWORD64>(list_entry + 0x78 * (loopIndex & 0x1FF), entity))
			continue;
		if (!entity) continue;

		DWORD64 playerPawn = 0;
		if (!cs2->read<DWORD64>(entity + cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn, playerPawn))
			continue;

		DWORD64 list_entry2 = 0;
		if (!cs2->read<DWORD64>(entityListEntry + 0x8 * ((playerPawn & 0x7FFF) >> 9) + 16, list_entry2))
			continue;
		if (!list_entry2) continue;

		DWORD64 pCSPlayerPawn = 0;
		if (!cs2->read<DWORD64>(list_entry2 + 0x78 * (playerPawn & 0x1FF), pCSPlayerPawn))
			continue;
		if (!pCSPlayerPawn) continue;
		//读取每个角色位置
		if (!cs2->read<point3D>(pCSPlayerPawn + cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin, m_playPawn[playerIndex].m_pPos))
			continue;
		m_playPawn[playerIndex].m_pHead = { m_playPawn[playerIndex].m_pPos.x,m_playPawn[playerIndex].m_pPos.y,m_playPawn[playerIndex].m_pPos.z + 75.f };
		//读取每个角色的血量
		if (!cs2->read<int>(pCSPlayerPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth, m_playPawn[playerIndex].m_iHealth))
			continue;
		//读取每个角色的队伍值
		if (!cs2->read<int>(pCSPlayerPawn + cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum, m_playPawn[playerIndex].m_iTeamNum))
			continue;
		//读取每个角色是否存活
		if (!cs2->read<bool>(entity + cs2_dumper::schemas::client_dll::CCSPlayerController::m_bPawnIsAlive, m_playPawn[playerIndex].m_bPawnIsAlive))
			continue;
		//读取视图矩阵
		if (!cs2->read<Matrix4x4>(client + cs2_dumper::offsets::client_dll::dwViewMatrix, m_mViewMatrix))
			continue;
	}
	if (playerIndex == 10) return true;
	else return false;
}

void kGame::showAllPlayer()
{
	system("cls");
	for (size_t i = 0; i < 10; i++)
	{
		if (!m_playPawn[i].isAlive()) continue;
		if (m_playPawn[i].getHealth() == 0) continue;
		std::cout << i << " health = " << m_playPawn[i].getHealth() << std::endl;
		std::cout << i << " x:" << m_playPawn[i].getPos().x << " y:" << m_playPawn[i].getPos().y << " z:" << m_playPawn[i].getPos().z << std::endl;
		std::cout << i << " teamNum = " << m_playPawn[i].getTeamNum() << std::endl;
		std::cout << i << " isAlive = " << m_playPawn[i].isAlive() << std::endl;
	}
}

Matrix4x4 kGame::getMatrix()
{
	return m_mViewMatrix;
}


point3D kGame::getPlayerPawnPos(int indexPlayer)
{
	return m_playPawn[indexPlayer].getPos();
}

point2D kGame::world2screen(const point3D& point, const Matrix4x4& matrix) {

	float _x = matrix.m[0][0] * point.x + matrix.m[0][1] * point.y + matrix.m[0][2] * point.z + matrix.m[0][3];
	float _y = matrix.m[1][0] * point.x + matrix.m[1][1] * point.y + matrix.m[1][2] * point.z + matrix.m[1][3];

	float w = matrix.m[3][0] * point.x + matrix.m[3][1] * point.y + matrix.m[3][2] * point.z + matrix.m[3][3];

	float inv_w = 1.f / w;
	_x *= inv_w;
	_y *= inv_w;

	float x = m_rect.right * .5f;
	float y = m_rect.bottom * .5f;

	x += 0.5f * _x * m_rect.right + 0.5f;
	y -= 0.5f * _y * m_rect.bottom + 0.5f;

	return { x,y };
}
