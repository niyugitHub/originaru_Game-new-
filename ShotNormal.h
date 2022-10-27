#pragma once

#include "ShotBase.h"

//#include "SceneMain.h"

class SceneMain;

class ShotNormal : public ShotBase
{
public:
	ShotNormal();

	virtual ~ShotNormal()
	{
	}

	
	virtual void setPos(Vec2 pos) { m_PlayerPos = pos; }

	//ショット開始
	virtual void start(Vec2 pos);

	// 更新
	virtual void update();
private:

	SceneMain* m_pMain;
	// プレイヤーの位置を保存するメンバ変数
	Vec2 m_PlayerPos;

	Vec2 m_vec;
};