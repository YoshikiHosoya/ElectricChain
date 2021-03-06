//------------------------------------------------------------------------------
//
//シーン3D処理  [scene3D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "scene3D.h"
#include "renderer.h"
#include "manager.h"
#include "keyboard.h"

//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
int CScene3D::m_nNumScene3D = 0;
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CScene3D::CScene3D()
{
	//初期化
	m_pos = ZeroVector3;
	m_size = ZeroVector3;
	m_rot = ZeroVector3;
	m_col = WhiteColor;
	m_bBboard = false;
	m_bDisp = true;

	//総数加算
	m_nNumScene3D++;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CScene3D::~CScene3D()
{
	//頂点バッファの開放
	if (m_pVtxBuff)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	//総数減算
	m_nNumScene3D--;
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CScene3D::Init()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の座標
	m_Vtx3D[0].pos = pVtx[0].pos =ZeroVector3;
	m_Vtx3D[1].pos = pVtx[1].pos =ZeroVector3;
	m_Vtx3D[2].pos = pVtx[2].pos =ZeroVector3;
	m_Vtx3D[3].pos = pVtx[3].pos =ZeroVector3;

	//頂点の同次座標
	m_Vtx3D[0].nor = pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vtx3D[1].nor = pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vtx3D[2].nor = pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Vtx3D[3].nor = pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//頂点の色
	m_Vtx3D[0].col = pVtx[0].col = m_col;
	m_Vtx3D[1].col = pVtx[1].col = m_col;
	m_Vtx3D[2].col = pVtx[2].col = m_col;
	m_Vtx3D[3].col = pVtx[3].col = m_col;

	//テクスチャ座標
	m_Vtx3D[0].tex = pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	m_Vtx3D[1].tex = pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	m_Vtx3D[2].tex = pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	m_Vtx3D[3].tex = pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CScene3D::Uninit()
{

}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CScene3D::Update()
{

}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CScene3D::Draw()
{
	//ワールドマトリックス計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	if (m_bBboard)
	{
		CHossoLibrary::SetBillboard(&m_mtxWorld);
	}

	//ポリゴン描画
	DrawPolygon();
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CScene3D::ShowDebugInfo()
{
#ifdef _DEBUG
	//3D情報
	if (ImGui::TreeNode("Scene3DInfo"))
	{
		//座標
		if (ImGui::TreeNode("pos"))
		{
			if (ImGui::InputFloat3("pos", m_pos))
			{
				//座標設定
				SetPos(m_pos);
			}
			ImGui::TreePop();
		}

		//色
		if (ImGui::TreeNode("col"))
		{
			if (ImGui::ColorEdit4("col", m_col))
			{
				//色設定
				SetVtxCol(m_col);
			}
			//tree終了
			ImGui::TreePop();
		}

		//頂点情報
		if (ImGui::TreeNode("VtxInfo"))
		{
			//頂点座標
			if (ImGui::TreeNode("VtxPos"))
			{
				if (ImGui::SliderFloat3("pos[0]", m_Vtx3D[0].pos, -300.0f, 300.0f) ||
					ImGui::SliderFloat3("pos[1]", m_Vtx3D[1].pos, -300.0f, 300.0f) ||
					ImGui::SliderFloat3("pos[2]", m_Vtx3D[2].pos, -300.0f, 300.0f) ||
					ImGui::SliderFloat3("pos[3]", m_Vtx3D[3].pos, -300.0f, 300.0f))
				{
					//頂点情報へのポインタ
					VERTEX_3D *pVtx;

					//頂点データの範囲をロックし、頂点バッファへのポインタを取得
					m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

					//頂点更新
					pVtx[0].pos = m_Vtx3D[0].pos;
					pVtx[1].pos = m_Vtx3D[1].pos;
					pVtx[2].pos = m_Vtx3D[2].pos;
					pVtx[3].pos = m_Vtx3D[3].pos;

					//頂点データをアンロック
					m_pVtxBuff->Unlock();

					//法線計算
					SetNormal();
				}
				//ツリーノード終了
				ImGui::TreePop();
			}
			//頂点法線
			if (ImGui::TreeNode("VtxNor"))
			{
				//法線
				ImGui::InputFloat3("nor[0]", m_Vtx3D[0].nor);
				ImGui::InputFloat3("nor[1]", m_Vtx3D[1].nor);
				ImGui::InputFloat3("nor[2]", m_Vtx3D[2].nor);
				ImGui::InputFloat3("nor[3]", m_Vtx3D[3].nor);

				//ツリーノード終了
				ImGui::TreePop();
			}
			//tree終了
			ImGui::TreePop();
		}
		//tree終了
		ImGui::TreePop();
	}
#endif //DEBUG
}
//------------------------------------------------------------------------------
//設定処理
//------------------------------------------------------------------------------
void CScene3D::DrawSettingMtx(D3DXMATRIX const &Mtx)
{
	//引数のmtxを利用
	m_mtxWorld = Mtx;

	//ポリゴン描画
	DrawPolygon();
}
//------------------------------------------------------------------------------
//設定処理
//------------------------------------------------------------------------------
void CScene3D::DrawPolygon()
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
							0,					//開始するインデックス(頂点)
							2);					//ポリゴンの枚数

}

//------------------------------------------------------------------------------
//設定処理
//------------------------------------------------------------------------------
void CScene3D::SetPos(D3DXVECTOR3 pos)
{
	//座標
	m_pos = pos;
}

//------------------------------------------------------------------------------
//サイズの設定
//------------------------------------------------------------------------------
void CScene3D::SetSize(D3DXVECTOR3 size)
{
	//値代入
	m_size = size;

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の座標
	m_Vtx3D[0].pos = pVtx[0].pos = D3DXVECTOR3(-m_size.x * 0.5f, m_size.y * 0.5f, m_size.z * 0.5f);
	m_Vtx3D[1].pos = pVtx[1].pos = D3DXVECTOR3(m_size.x * 0.5f, m_size.y * 0.5f, m_size.z * 0.5f);
	m_Vtx3D[2].pos = pVtx[2].pos = D3DXVECTOR3(-m_size.x * 0.5f, -m_size.y * 0.5f, -m_size.z * 0.5f);
	m_Vtx3D[3].pos = pVtx[3].pos = D3DXVECTOR3(m_size.x * 0.5f, -m_size.y * 0.5f, -m_size.z * 0.5f);

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------------------------
//回転の設定
//------------------------------------------------------------------------------
void CScene3D::SetRot(D3DXVECTOR3 rot)
{
	//回転
	m_rot = rot;
}

//------------------------------------------------------------------------------
//色の設定
//------------------------------------------------------------------------------
void CScene3D::SetVtxCol(D3DXCOLOR col)
{
	//色設定
	m_col = col;

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}
//------------------------------------------------------------------------------
//テクスチャアニメーションの更新
//------------------------------------------------------------------------------
void CScene3D::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 size)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
	pVtx[1].tex = D3DXVECTOR2(UV.x + size.x, UV.y);
	pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + size.y);
	pVtx[3].tex = D3DXVECTOR2(UV.x + size.x, UV.y + size.y);

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------------------------
//法線設定
//------------------------------------------------------------------------------
void CScene3D::SetNormal()
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点から頂点へのベクトル
	D3DXVECTOR3 VecA = m_Vtx3D[1].pos - m_Vtx3D[0].pos;
	D3DXVECTOR3 VecB = m_Vtx3D[2].pos - m_Vtx3D[1].pos;
	D3DXVECTOR3 VecC = m_Vtx3D[3].pos - m_Vtx3D[2].pos;

	//ポリゴン面の法線
	D3DXVECTOR3 normal1, normal2, normal3;
	D3DXVec3Cross(&normal1, &VecA, &VecB);
	D3DXVec3Cross(&normal2, &-VecB, &VecC);

	//正規化
	D3DXVec3Normalize(&normal1, &normal1);
	D3DXVec3Normalize(&normal2, &normal2);
	D3DXVec3Normalize(&normal3, &(normal1 + normal2));

	//頂点の法線設定
	m_Vtx3D[0].nor = pVtx[0].nor = normal1;
	m_Vtx3D[1].nor = pVtx[1].nor = normal3;
	m_Vtx3D[2].nor = pVtx[2].nor = normal3;
	m_Vtx3D[3].nor = pVtx[3].nor = normal2;

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}
//------------------------------------------------------------------------------
//ゲージの更新
//------------------------------------------------------------------------------
void CScene3D::UpdateGauge(float fMag)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点の座標
	pVtx[0].pos = D3DXVECTOR3(-m_size.x * 0.5f, m_size.y * 0.5f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x * 0.5f - fMag * m_size.x, m_size.y * 0.5f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x * 0.5f, -m_size.y * 0.5f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x * 0.5f - fMag * m_size.x, -m_size.y * 0.5f, 0.0f);

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------------------------
//生成処理　共有管理用
//------------------------------------------------------------------------------
std::shared_ptr<CScene3D> CScene3D::Create_Shared(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype)
{
	//メモリ確保
	std::shared_ptr<CScene3D> pScene3D = std::make_shared<CScene3D>();

	//初期化
	pScene3D->Init();

	//座標とサイズ設定
	pScene3D->SetPos(pos);
	pScene3D->SetSize(size);

	//Scene側で管理
	pScene3D->SetObjType(objtype);
	pScene3D->AddSharedList(pScene3D);

	return pScene3D;
}
//------------------------------------------------------------------------------
//生成処理　Csceneで管理用
//------------------------------------------------------------------------------
void CScene3D::Create_SceneManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype)
{
	//メモリ確保
	std::unique_ptr<CScene3D> pScene3D(new CScene3D);

	//初期化
	pScene3D->Init();

	//座標とサイズ設定
	pScene3D->SetPos(pos);
	pScene3D->SetSize(size);

	//Sceneで管理
	pScene3D->SetObjType(objtype);
	pScene3D->AddUniqueList(std::move(pScene3D));
}
//------------------------------------------------------------------------------
//生成処理　Return先で管理用
//------------------------------------------------------------------------------
std::unique_ptr<CScene3D> CScene3D::Create_SelfManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//メモリ確保
	std::unique_ptr<CScene3D> pScene3D(new CScene3D);

	//初期化
	pScene3D->Init();

	//座標とサイズ設定
	pScene3D->SetPos(pos);
	pScene3D->SetSize(size);

	//return
	return std::move(pScene3D);
}
