#pragma once

#include <vector>
#include "player.h"
#include "ShotBase.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// 初期化
	void init();
	// 終了処理
	void end();

	// 毎フレームの処理
	void update();
	// 毎フレームの描画
	void draw();

	//弾の生成
	bool createShotNormal(Vec2 pos);
	bool createShotFall(Vec2 pos);
	bool createShotBound(Vec2 pos);

private:

	// プレイヤーのグラフィックハンドル
	int m_hPlayerGraphic[Player::kPlayerGraphicDivNum];
	int m_hShotGraphic;

	// サウンドハンドル
	 int m_hTestSound;
	// プレイヤー
	Player m_player;
	// ショット
	//ShotBase* m_pShot[kShotMax];
	std::vector<ShotBase*> m_pShotVt;
	/*ShotBound* m_pShotBound[kShotMax];
	ShotNormal* m_pShotNormal[kShotMax];
	ShotFall* m_pShotFall[kShotMax];*/
};