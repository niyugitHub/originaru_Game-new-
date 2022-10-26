#pragma once

#include "ShotBase.h"

//#include "SceneMain.h"

class SceneMain;

class ShotNormal : public ShotBase
{
public:
	ShotNormal()
	{
	}
	virtual ~ShotNormal()
	{
	}

	// SceneMainを設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	//ショット開始
	virtual void start(Vec2 pos);

	// 更新
	virtual void update();
private:

	SceneMain* m_pMain;
	// プレイヤーの位置を保存するメンバ関数
	Vec2 m_PlayerPos;

	Vec2 m_vec;
};