//------------------------------------------------------------------------------
//
//Xファイルモデル処理  [SceneX.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "sceneX.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"
#include "light.h"

//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
int CSceneX::m_nNumSceneX = 0;

std::vector<D3DMATERIAL9> CSceneX::m_MaterialColor[CSceneX::MAT_MAX] ={};

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define SHADOW_COLOR (D3DXCOLOR(0.0f,0.0f,0.0f,0.5f))

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CSceneX::CSceneX()
{
	//初期化
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
	m_SceneXInfo = nullptr;
	m_MatCol = MAT_NORMAL;

	//総数加算
	m_nNumSceneX++;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CSceneX::~CSceneX()
{
	//ポインタの開放
	m_SceneXInfo = nullptr;

	//総数減算
	m_nNumSceneX--;
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CSceneX::Init()
{
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CSceneX::Uninit()
{
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CSceneX::Update()
{
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CSceneX::Draw()
{
	//マトリックス計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	//メッシュ描画
	DrawMesh();
}

//------------------------------------------------------------------------------
//頂点情報を元にメッシュの描画
//------------------------------------------------------------------------------
void CSceneX::DrawMesh()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL		*pMat;
	D3DMATERIAL9		matDef;
	D3DMATERIAL9		DrawMat;

	//テクスチャの設定
	pDevice->SetTexture(0, NULL);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_SceneXInfo->matBuff->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_SceneXInfo->matNum; nCntMat++)
	{
		//描画用のマテリアル取得
		DrawMat = pMat[nCntMat].MatD3D;

		// マテリアルの設定
		pDevice->SetMaterial(&DrawMat);

		// 描画
		m_SceneXInfo->mesh->DrawSubset(nCntMat);
	}
	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}
//------------------------------------------------------------------------------
//影のマトリックス描画
//------------------------------------------------------------------------------
void CSceneX::DrawShadow()
{
	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATERIAL		*pMat;
	D3DMATERIAL9		matDef;
	D3DMATERIAL9		matBlack;

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	//初期化
	matBlack = matDef;

	//黒設定
	matBlack.Diffuse = SHADOW_COLOR;

	// マテリアル情報に対するポインタを取得
	pMat = (D3DXMATERIAL*)m_SceneXInfo->matBuff->GetBufferPointer();

	//ステンシル有効　0のところにのみ描画可能
	pDevice->SetRenderState(D3DRS_STENCILREF, 0);					//ステンシルの条件の値
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);		//ステンシルの条件 ==
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);				//ステンシル･バッファ有効

	for (int nCntMat = 0; nCntMat < (int)m_SceneXInfo->matNum; nCntMat++)
	{
		//ステンシル設定
		pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

		// マテリアルの設定
		pDevice->SetMaterial(&matBlack);

		// 描画
		m_SceneXInfo->mesh->DrawSubset(nCntMat);
	}

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);	// ステンシル･バッファ無効

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CSceneX::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}


//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
CSceneX * CSceneX::Create(D3DXVECTOR3 pos, OBJTYPE objtype)
{
	//変数宣言
	CSceneX *pSceneX;

	//メモリ確保
	pSceneX = new CSceneX();

	//初期化
	pSceneX->Init();

	//座標とサイズ設定
	pSceneX->SetPos(pos);

	//オブジェクトタイプ設定
	pSceneX->SetObjType(objtype);

	//生成した情報
	return pSceneX;
}
