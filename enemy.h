#pragma once

#include "Vec2.h"

class SceneMain;

class Enemy
{
public:
	// 敵グラフィックサイズ
	static constexpr int kEnemyGraphicSizeX = 64;
	static constexpr int kEnemyGraphicSizeY = 80;
public:
	Enemy();
	virtual ~Enemy();

	// グラフィックデータ設定
	void setHandle(int handle) { m_handle = handle; }

	// プレイヤーの初期化
	void init();

	//SceneMainクラスのポインタ設定
	void setMain(SceneMain* pMain) { m_pMain = pMain; }

	// 処理
	void update();
	// 描画
	void draw();

	// 情報の取得
	Vec2 getPos() const { return m_pos; }

	// 動きの取得
	void MoveNormal();
	void MoveCircle();
//	void Move();

private:
	int m_handle;

	// グラフィックの幅と高さ
	Vec2 m_graphSize;

	//SceneMainのポインタ
	SceneMain* m_pMain;

	// 表示位置
	Vec2 m_pos;
	// 移動
	Vec2 m_vec;

	int m_shotInterval;
	int m_waitFrame;
	int m_randMove;
	int m_Center;
	float m_rotAngle1;
	float m_rotAngle2;
	float m_PI;
};