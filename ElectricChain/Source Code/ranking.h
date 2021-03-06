//------------------------------------------------------------------------------
//
//ランキング処理  [ranking.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _RANKING_H_
#define _RANKING_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "basemode.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
//前方宣言
class CMultiNumber;
class CRanking : public CBaseMode
{
public:
	CRanking();
	~CRanking();

	HRESULT Init(HWND hWnd);			//初期化
	void Uninit();						//終了
	void Update();						//更新
	void Draw();						//描画
	void ShowDebugInfo() {};			//デバッグ情報表記

	CPlayer* GetPlayer() { return nullptr; };		//プレイヤーの情報取得　オーバーライドのやつ

private:
	int m_nCntFadeTitle;							//タイトルにフェードするまでのカウント
	std::vector<std::shared_ptr<CMultiNumber>> m_pMultiNumberList;		//数値のリスト
	void CreateRank();
};

#endif