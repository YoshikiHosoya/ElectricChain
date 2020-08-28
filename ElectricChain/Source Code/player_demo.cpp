//------------------------------------------------------------------------------
//
//�f���p�̃v���C���[����  [player_demo.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
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
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define TARGET_LENGTH (200.0f)
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CPlayer_Demo::CPlayer_Demo()
{
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CPlayer_Demo::~CPlayer_Demo()
{
	m_pTargetEnemy.reset();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CPlayer_Demo::Init()
{
	CCharacter::Init();

	//����
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CPlayer_Demo::Uninit()
{
	CCharacter::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CPlayer_Demo::Update()
{
	//�����Ă鎞
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

		//�_���[�W�󂯂ĂȂ���
		if (CCharacter::GetNowMotion() != CMotion::PLAYER_HIT)
		{
			//�ړ��̓��͏���
			MoveAI();

			//���[�V�����؂�ւ�
			MoveMotionCheck();
		}

		//���������
		if (GetChainThunder())
		{
			//���̃G�t�F�N�g
			ChainThunder();
		}
	}

	//�X�V
	CCharacter::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CPlayer_Demo::Draw()
{
	CCharacter::Draw();
}

//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CPlayer_Demo::ShowDebugInfo()
{
#ifdef _DEBUG


#endif //DEBUG
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::shared_ptr<CPlayer_Demo> CPlayer_Demo::Create(D3DXVECTOR3 pos)
{
	//�ϐ��錾
	std::shared_ptr<CPlayer_Demo> pPlayer_Demo = std::make_shared<CPlayer_Demo>();

	if (pPlayer_Demo)
	{
		//������7
		pPlayer_Demo->Init();

		//���W�ݒ�
		pPlayer_Demo->SetPos(pos);

		//�p�����[�^�ݒ�
		pPlayer_Demo->SetParameter(MODEL_TYPE::MODEL_PLAYER,CCharacter::PARAM_PLAYER, pPlayer_Demo);

		//�I�u�W�F�N�g�^�C�v�ݒ�
		pPlayer_Demo->SetObjType(OBJTYPE_PLAYER);

		//���X�g�ɒǉ�
		pPlayer_Demo->AddSharedList(pPlayer_Demo);

		return pPlayer_Demo;
	}

	//�����������
	return nullptr;
}

//------------------------------------------------------------------------------
//�ړ��̓���
//------------------------------------------------------------------------------
void CPlayer_Demo::MoveAI()
{
	D3DXVECTOR3 &rMove = GetMove();			//�ړ����擾
	D3DXVECTOR3 &rRotdest = GetRotDest();	//��]���擾
	D3DXVECTOR3 posDif = ZeroVector3;
	float fAngle = 0.0f;
	float fLength = 0.0f;

	//�G�̏�񂪓����Ă邩�ǂ���
	if (m_pTargetEnemy._Get())
	{
		//���݃^�[�Q�b�g���̓G���X�^�����̂Ƃ�
		if (m_pTargetEnemy._Get()->GetStan())
		{
			//�^�[�Q�b�e�B���O
			SetTargetEnemy();
		}
	}
	else
	{
		//�^�[�Q�b�e�B���O
		SetTargetEnemy();
	}

	//�G�^�[�Q�b�g�̓G������Ƃ�
	if (m_pTargetEnemy._Get())
	{
		//�G�Ƃ̋����v��
		posDif = m_pTargetEnemy._Get()->GetPos() - GetPos();
		fAngle = atan2f(posDif.x, posDif.z);
		fLength = D3DXVec3Length(&posDif);
	}
	else
	{
		return;
	}

	//�G���S�ăX�^�����Ă܂��A���������ĂȂ���
	if (CEnemy::GetEnemyNum() == CEnemy::GetStanEnemyNum() && !GetChainThunder())
	{
		ChangeMotion(CMotion::PLAYER_ATTACK_THUNDER);
		StartChainThunder();
		SetAirAttack(true);
		m_pTargetEnemy.reset();
	}

	//�U�����ĂȂ���
	if (!GetAttack())
	{
		//�ړ����x
		float fMoveSpeed;

		//�ړ����x�ݒ�
		//�W�����v��Ԃ̎��͋󒆂̈ړ����x
		//����ȊO�̏ꍇ�̓_�b�V���̈ړ����x
		fMoveSpeed = GetJump() ?
			fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetAirSpeeed():
			fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetDashSpeed();

		//�ړ�
		//�G�̕��p * �ړ����x
		rMove.x += sinf(fAngle) * fMoveSpeed;
		rMove.z += cosf(fAngle) * fMoveSpeed;

		//�̂̉�]�̌����ݒ�
		rRotdest.y = D3DX_PI + fAngle;

		//3.14�͈̔͂ɗ}����
		CHossoLibrary::CalcRotation(rRotdest.y);
	}

	//�^�[�Q�b�g�̓G�Ƃ̋��������ȉ��ɂȂ�����
	if (fLength < TARGET_LENGTH)
	{
		//����
		int nAttackRand = rand() % 5;

		if (nAttackRand <= 3)
		{
			//X�̓���
			GetAttackInptut() = CPlayer::ATTACK_INPUT::INPUT_X;
		}
		else
		{
			//Y�̓���
			GetAttackInptut() = CPlayer::ATTACK_INPUT::INPUT_Y;
		}

		//�U���̓���
		if (Attack())
		{
			//��]
			rRotdest.y = fAngle + D3DX_PI;
			SetAttack(true);
		}
	}
}

//------------------------------------------------------------------------------
//�G�̃^�[�Q�b�g�ݒ�
//------------------------------------------------------------------------------
void CPlayer_Demo::SetTargetEnemy()
{
	//�V�[���̃��X�g
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//�V�[�����擾
	CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);

	//�z��ɓ����Ă邩
	if (!pSceneList.empty())
	{
		//�v�f��
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//�|�C���^�擾 CEnemy�^�Ƀ_�E���L���X�g
			std::shared_ptr<CEnemy> pEnemy = std::static_pointer_cast<CEnemy>(pSceneList[nCnt]);
			//nullcheck
			if (pEnemy)
			{
				//�X�^����Ԃ���Ȃ����
				if (!pEnemy->GetStan())
				{
					//�^�[�Q�b�g�ݒ�
					m_pTargetEnemy = pEnemy;
					return;
				}
			}
		}
	}
}


