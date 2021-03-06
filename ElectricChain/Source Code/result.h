//------------------------------------------------------------------------------
//
//リザルト処理  [result.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _RESULT_H_
#define _RESULT_H_
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
class CMultiNumber;

class CResult : public CBaseMode
{
public:
	CResult();
	~CResult();

	enum RESULT_ITEM
	{
		RESULT_COMBO = 0,
		REUSLT_KILL,
		RESULT_TOTAL
	};

	HRESULT Init(HWND hWnd);			//初期化
	void Uninit();						//終了
	void Update();						//更新
	void Draw();						//描画
	void ShowDebugInfo() {};			//デバッグ情報表記

	CPlayer* GetPlayer() { return nullptr; };		//プレイヤー取得処理

private:
	int m_nCntResult;												//カウンタ
	std::vector<std::shared_ptr<CMultiNumber>>	m_pNumberList;		//数値のリスト
	void PopResultItem();											//カウンタに応じてリザルトの項目出現
};

#endif