//------------------------------------------------------------------------------
//
//デモ用のプレイヤー処理  [player_demo.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "player_demo.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "sound.h"
#include "gauge_2D.h"
#include "effectanimation3D.h"
#include "game.h"
#include "sphere_explosion.h"
#include "enemy.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define TARGET_LENGTH (200.0f)
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CPlayer_Demo::CPlayer_Demo()
{
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CPlayer_Demo::~CPlayer_Demo()
{
	m_pTargetEnemy.reset();
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CPlayer_Demo::Init()
{
	CCharacter::Init();

	//成功
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CPlayer_Demo::Uninit()
{
	CCharacter::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CPlayer_Demo::Update()
{
	//生きてる時
	if (GetAlive())
	{
		switch (GetNowMotion())
		{
		case CMotion::PLAYER_NEUTRAL:
		case CMotion::PLAYER_WALK:
		case CMotion::PLAYER_DASH:
			if (GetJump())
			{
				ChangeMotion(CMotion::PLAYER_AIR_NEUTRAL);
			}
			SetChainThunder(false);
			SetAttack(false);
			break;
		}

		//ダメージ受けてない時
		if (CCharacter::GetNowMotion() != CMotion::PLAYER_HIT)
		{
			//移動の入力処理
			MoveAI();

			//モーション切り替え
			MoveMotionCheck();
		}

		//雷発生状態
		if (GetChainThunder())
		{
			//雷のエフェクト
			ChainThunder();
		}
	}

	//更新
	CCharacter::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CPlayer_Demo::Draw()
{
	CCharacter::Draw();
}

//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CPlayer_Demo::ShowDebugInfo()
{
#ifdef _DEBUG


#endif //DEBUG
}

//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
std::shared_ptr<CPlayer_Demo> CPlayer_Demo::Create(D3DXVECTOR3 pos)
{
	//変数宣言
	std::shared_ptr<CPlayer_Demo> pPlayer_Demo = std::make_shared<CPlayer_Demo>();

	if (pPlayer_Demo)
	{
		//初期化7
		pPlayer_Demo->Init();

		//座標設定
		pPlayer_Demo->SetPos(pos);

		//パラメータ設定
		pPlayer_Demo->SetParameter(MODEL_TYPE::MODEL_PLAYER,CCharacter::PARAM_PLAYER, pPlayer_Demo);

		//オブジェクトタイプ設定
		pPlayer_Demo->SetObjType(OBJTYPE_PLAYER);

		//リストに追加
		pPlayer_Demo->AddSharedList(pPlayer_Demo);

		return pPlayer_Demo;
	}

	//生成した情報
	return nullptr;
}

//------------------------------------------------------------------------------
//移動の入力
//------------------------------------------------------------------------------
void CPlayer_Demo::MoveAI()
{
	D3DXVECTOR3 &rMove = GetMove();			//移動情報取得
	D3DXVECTOR3 &rRotdest = GetRotDest();	//回転情報取得
	D3DXVECTOR3 posDif = ZeroVector3;
	float fAngle = 0.0f;
	float fLength = 0.0f;

	//敵の情報が入ってるかどうか
	if (m_pTargetEnemy._Get())
	{
		//現在ターゲット中の敵がスタン中のとき
		if (m_pTargetEnemy._Get()->GetStan())
		{
			//ターゲッティング
			SetTargetEnemy();
		}
	}
	else
	{
		//ターゲッティング
		SetTargetEnemy();
	}

	//敵ターゲットの敵がいるとき
	if (m_pTargetEnemy._Get())
	{
		//敵との距離計測
		posDif = m_pTargetEnemy._Get()->GetPos() - GetPos();
		fAngle = atan2f(posDif.x, posDif.z);
		fLength = D3DXVec3Length(&posDif);
	}
	else
	{
		return;
	}

	//敵が全てスタンしてまだ連鎖爆発してない時
	if (CEnemy::GetEnemyNum() == CEnemy::GetStanEnemyNum() && !GetChainThunder())
	{
		ChangeMotion(CMotion::PLAYER_ATTACK_THUNDER);
		StartChainThunder();
		SetAirAttack(true);
		m_pTargetEnemy.reset();
	}

	//攻撃してない時
	if (!GetAttack())
	{
		//移動速度
		float fMoveSpeed;

		//移動速度設定
		//ジャンプ状態の時は空中の移動速度
		//それ以外の場合はダッシュの移動速度
		fMoveSpeed = GetJump() ?
			fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetAirSpeeed():
			fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetDashSpeed();

		//移動
		//敵の方角 * 移動速度
		rMove.x += sinf(fAngle) * fMoveSpeed;
		rMove.z += cosf(fAngle) * fMoveSpeed;

		//体の回転の向き設定
		rRotdest.y = D3DX_PI + fAngle;

		//3.14の範囲に抑える
		CHossoLibrary::CalcRotation(rRotdest.y);
	}

	//ターゲットの敵との距離が一定以下になった時
	if (fLength < TARGET_LENGTH)
	{
		//乱数
		int nAttackRand = rand() % 5;

		if (nAttackRand <= 3)
		{
			//Xの入力
			GetAttackInptut() = CPlayer::ATTACK_INPUT::INPUT_X;
		}
		else
		{
			//Yの入力
			GetAttackInptut() = CPlayer::ATTACK_INPUT::INPUT_Y;
		}

		//攻撃の入力
		if (Attack())
		{
			//回転
			rRotdest.y = fAngle + D3DX_PI;
			SetAttack(true);
		}
	}
}

//------------------------------------------------------------------------------
//敵のターゲット設定
//------------------------------------------------------------------------------
void CPlayer_Demo::SetTargetEnemy()
{
	//シーンのリスト
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//シーン情報取得
	CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);

	//配列に入ってるか
	if (!pSceneList.empty())
	{
		//要素分
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//ポインタ取得 CEnemy型にダウンキャスト
			std::shared_ptr<CEnemy> pEnemy = std::static_pointer_cast<CEnemy>(pSceneList[nCnt]);
			//nullcheck
			if (pEnemy)
			{
				//スタン状態じゃないやつ
				if (!pEnemy->GetStan())
				{
					//ターゲット設定
					m_pTargetEnemy = pEnemy;
					return;
				}
			}
		}
	}
}


