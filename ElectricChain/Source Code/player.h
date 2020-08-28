//------------------------------------------------------------------------------
//
//プレイヤー処理  [player.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _PLAYER_H_
#define _PLAYER_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "character.h"

//------------------------------------------------------------------------------
//前方宣言
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CGauge_2D;

class CPlayer : public CCharacter
{
public:
	//ボタンの入力
	//先行入力用
	enum class ATTACK_INPUT
	{
		INPUT_NONE,			//入力無し
		INPUT_X,			//Xボタン
		INPUT_Y,			//Yボタン
		INPUT_B,			//Bボタン
	};

	CPlayer();															//コンストラクタ
	~CPlayer();															//デストラクタ

	virtual HRESULT Init();												//初期化
	virtual void Uninit();												//終了
	virtual void Update();												//更新
	virtual void Draw();												//描画
	virtual void ShowDebugInfo();										//デバッグ情報表記
	void DamageAction();												//ダメージ時のリアクション
	void DeathAction();													//死亡時のリアクション
	void AttackTurning();												//攻撃時の旋回
	void SetState(STATE nextstate);										//ステート変更処理
	void StartChainThunder();											//連鎖開始
	static std::shared_ptr<CPlayer> Create(D3DXVECTOR3 pos);			//生成

	void SetChainThunder(bool bChain) { m_bChainThunder = bChain; };	//雷発発生状態設定
	void SetAttackInput(ATTACK_INPUT input) { m_AttackInput = input; };	//入力の設定

	bool GetChainThunder() { return m_bChainThunder; };					//雷発生状態か取得
	ATTACK_INPUT &GetAttackInptut() { return m_AttackInput; };			//入力の取得

protected:
	void ChainThunder();												//連鎖
	void MoveMotionCheck();												//移動系のモーションチェック
	bool Attack();													//攻撃の入力処理

private:
	static bool m_bClearedAlive;										//ゲームクリア時に生きていたか
	ATTACK_INPUT m_AttackInput;											//攻撃の入力
	int m_nCntAttackInput;												//攻撃の入力の経過時間
	bool m_bChainThunder;												//連鎖雷状態
	int m_nCntChainThunder;												//連鎖雷の経過時間
	std::shared_ptr<CGauge_2D> m_pGauge;								//ゲージのポインタ

	void ActionInput();													//入力処理
	void MoveInput();													//移動の入力
private:
};
#endif