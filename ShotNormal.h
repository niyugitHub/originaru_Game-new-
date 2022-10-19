#pragma once

#include "ShotBase.h"
#include "SceneMain.h"
class ShotNormal : public ShotBase
{
public:
	ShotNormal()
	{
	}
	virtual ~ShotNormal()
	{
	}

	//ショット開始
	virtual void start(Vec2 pos);
	// メンバ変数に座標を設定するための関数
	void setPlayerPos();
	// 更新
	virtual void update();
private:
	// プレイヤーの位置を保存するメンバ関数
	Vec2 m_PlayerPos;
};