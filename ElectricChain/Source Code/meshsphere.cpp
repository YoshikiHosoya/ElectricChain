//------------------------------------------------------------------------------
//
//���b�V���X�t�B�A����  [meshsphere.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "renderer.h"
#include "manager.h"
#include "meshsphere.h"
#include "sphere_explosion.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CMeshSphere::CMeshSphere()
{
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CMeshSphere::~CMeshSphere()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CMeshSphere::Init()
{
	CMesh::Init();

	return S_OK;

}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CMeshSphere::Uninit()
{
	CMesh::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CMeshSphere::Update()
{
	CMesh::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CMeshSphere::Draw()
{
	CHossoLibrary::CalcMatrix(GetMtx(), GetPos(), GetRot());

	CMesh::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CMeshSphere::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
std::shared_ptr<CMeshSphere> CMeshSphere::Create(D3DXVECTOR3 const pos,float const fRadius, INTEGER2 const BlockNum)
{
	//�������m��
	std::shared_ptr<CMeshSphere> pMesh(new CMeshSphere);

	//nullcheck
	if (pMesh)
	{
		//������
		pMesh->Init();

		//���ݒ�
		pMesh->SetPos(pos);
		pMesh->m_fRadius = fRadius;
		pMesh->SetBlockNum(BlockNum);

		//���_����
		pMesh->MakeVertex();
		pMesh->SetNormal();

		//Scene�ɒǉ�
		pMesh->SetObjType(OBJTYPE_MESHSPHERE);
		pMesh->AddSharedList(pMesh);

	}
	//return
	return pMesh;
}


//------------------------------------------------------------------------------
//���_�ݒ�
//------------------------------------------------------------------------------
D3DXVECTOR3 CMeshSphere::SetVtx(INTEGER2 nCnt, INTEGER2 BlockNum)
{
	//�p�x�����ꂼ��v�Z
	float fRotH = (D3DX_PI * 2) / BlockNum.x;
	float fRotV = (D3DX_PI * 2) / BlockNum.y;

	//���W�v�Z
	return D3DXVECTOR3(sinf(fRotH * nCnt.x) * sinf(fRotV * nCnt.y * 0.5f) * m_fRadius,
						-cosf(fRotV * nCnt.y * 0.5f) * m_fRadius,
						cosf(fRotH * nCnt.x) * sinf(fRotV * nCnt.y * 0.5f) * m_fRadius);

}