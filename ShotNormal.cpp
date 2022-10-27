#include "ShotNormal.h"
#include "game.h"
#include "SceneMain.h"
#include "Dxlib.h"

namespace
{
	constexpr float kShotSpeed = 8.0f;
	constexpr float kChaseSpeed = 2.0f;
}

ShotNormal::ShotNormal() :
	m_PlayerPos(0,0)
{

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
	if (!m_isExist)
	{
		delete m_pMain;
		return;
	}
	if (m_pos.x < m_PlayerPos.x)
	{
		m_pos.x += m_vec.x;
	}

	else if (m_pos.x > m_PlayerPos.x)
	{
		m_pos.x -= m_vec.x;
	}

	delete m_pMain;

	m_pos.y += m_vec.y;

	if (m_pos.y > Game::kScreenHeight)
	{
		m_isExist = false;
	}

}