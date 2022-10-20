#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"
#include "SceneBase.h"
#include "enemy.h"
#include "Vec2.h"

class SceneMain : public SceneBase
{
public:
	// 定数定義

	// プレイヤーグラフィック分割数
	static constexpr int kDeadGraphicDivX = 3;
	static constexpr int kDeadGraphicDivY = 3;
	static constexpr int kDeadGraphicDivNum = kDeadGraphicDivX * kDeadGraphicDivY;

	// プレイヤーグラフィックサイズ
	static constexpr int kDeadGraphicSizeX = 75;
	static constexpr int kDeadGraphicSizeY = 75;

public:
	SceneMain();
	virtual ~SceneMain();

	// 初期化
	virtual void init();

	// 終了処理
	virtual void end();

	// 毎フレームの処理
	virtual SceneBase* update();
	// 毎フレームの描画
	virtual void draw();

	// 情報の取得
	Vec2 getPos() const { return m_pos; }

	//弾の生成
	virtual bool createShotPlayer(Vec2 pos);
	virtual bool createShotNormal(Vec2 pos);
	virtual bool createShotFall(Vec2 pos);
	virtual bool createShotBound(Vec2 pos);

	// 当たり判定
	virtual bool Col_ShotPlayer();
	virtual bool Col_EnemyPlayer();
	virtual bool Col_ShotEnemy();

private:

	// キャラクターのアニメーション
	int m_animeNo;	// 表示する番号
	int m_animeFrame;

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic[Player::kPlayerGraphicDivNum];
	int m_hDeadGraphic[kDeadGraphicDivNum];
	int m_hEnemyGraphic;
	int m_hShotGraphic;

	// サウンドハンドル
	 int m_hTestSound;
	 // 敵体力
	 int m_EnemyHP;
	 // 敵体力
	 //プレイヤーが死んだ回数
	 int m_DeadPlayerCount;
	 //敵が死んだ回数
	 int m_DeadEnemyCount;
	// プレイヤー
	Player m_player;
	// 敵
	Enemy m_enemy;
	// 表示位置
	Vec2 m_pos;
	// ショット
	//ShotBase* m_pShot[kShotMax];
	std::vector<ShotBase*> m_pShotVt;
	/*ShotBound* m_pShotBound[kShotMax];
	ShotNormal* m_pShotNormal[kShotMax];
	ShotFall* m_pShotFall[kShotMax];*/
};