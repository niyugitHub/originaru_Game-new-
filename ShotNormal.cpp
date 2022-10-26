#include "ShotNormal.h"
#include "game.h"
#include "SceneMain.h"
#include "Dxlib.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;
	constexpr float kChaseSpeed = 2.0f;
}

void ShotNormal::start(Vec2 pos)
{
	ShotBase::start(pos);

	/*m_isExist = true;

	m_PlayerPos = getPos();*/
//	m_pMain = nullptr;
	m_vec.x = kChaseSpeed;
	m_vec.y = kShotSpeed;
}

void ShotNormal::update()
{
	if (!m_isExist)return;

	/*if (m_pos.x < m_pMain->getPlayerPos().x)
	{
		m_pos.x += m_vec.x;
	}

	else if (m_pos.x > m_pMain->getPlayerPos().x)
	{
		m_pos.x -= m_vec.x;
	}*/

	m_pos.y += m_vec.y;

	if (m_pos.y > Game::kScreenHeight)
	{
		m_isExist = false;
	}

}