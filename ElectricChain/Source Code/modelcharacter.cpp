//------------------------------------------------------------------------------
//
//�L�����N�^�[�p���f������  [modelcharacter.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "modelcharacter.h"
#include "modelparts.h"
#include "modelparts_weapon.h"
#include "manager.h"
#include "keyboard.h"
#include "game.h"
#include "sceneX.h"
#include "game.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
std::vector<std::unique_ptr<CModelCharacterInfo>> CModelCharacter::m_pModelCharacterList;
char *CModelCharacter::m_aFileName[MODEL_MAX]
{
	{ "data/SAVEDATA/Woman/Woman.txt" },
	{ "data/SAVEDATA/Armor/Armor.txt" },

};
//------------------------------------------------------------------------------
// �}�N��
//------------------------------------------------------------------------------
#define OFFSET_SAVE_TEXT ("data/SAVEDATA/Offset.txt")
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CModelCharacter::CModelCharacter()
{
	m_pModelPartsList.clear();
	m_CharacterMtx = nullptr;
	m_nFrame = 0;
	m_nKey = 0;
	m_type = MODEL_TYPE::MODEL_PLAYER;
	m_motion = CMotion::MOTION_NONE;
	m_motionOld = CMotion::MOTION_NONE;
	m_bMotionStop = false;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CModelCharacter::~CModelCharacter()
{
	m_pModelPartsList.clear();
	m_pModelPartsWeaponList.clear();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CModelCharacter::Init()
{
	//���f�������J��Ԃ�
	for (size_t nCnt = 0; nCnt < m_pModelCharacterList[m_type]->pModelInfoList.size(); nCnt++)
	{
		//����ID��������Ȃ������ꍇ
		if (m_pModelCharacterList[m_type]->nWeaponID.end() == std::find(m_pModelCharacterList[m_type]->nWeaponID.begin(), m_pModelCharacterList[m_type]->nWeaponID.end(), nCnt))
		{
			//�������m��+�z��ɒǉ�
			m_pModelPartsList.emplace_back(std::move(CModelParts::Create(m_pModelCharacterList[m_type]->pModelInfoList[nCnt])));

		}
		//����ID�����������ꍇ
		else
		{
			//�������m��+�z��ɒǉ�
			m_pModelPartsWeaponList.emplace_back(std::move(CModelParts_Weapon::Create(m_pModelCharacterList[m_type]->pModelInfoList[nCnt])));
		}
	}
	//�p�[�c�̑��΍��W�擾
	LoadModelRelativeValue(m_type);

	//�������[�V�����Z�b�g
	SetDefaultMotion();

	//�����I�Ƀ��[�V�����̏��܂ŉ�]
	ForcedUpdate(m_motion, m_nKey);

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CModelCharacter::Uninit()
{
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CModelCharacter::Update()
{
	//1F�O�̃��[�V�����ۑ�
	m_motionOld = m_motion;

	//�t���[�����Z
	m_nFrame++;

	//�t���[�����ő傢�������ǂ���
	FrameCheck();

	if (!m_bMotionStop)
	{
		//nullcheck
		if (!m_pModelPartsList.empty())
		{
			//���f�������J��Ԃ�
			for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
			{
				//�X�V
				m_pModelPartsList[nCnt]->Update();
			}
		}
		//����
		//nullcheck
		if (!m_pModelPartsWeaponList.empty())
		{
			//���f�������J��Ԃ�
			for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
			{
				//�X�V
				m_pModelPartsWeaponList[nCnt]->Update();
			}
		}
	}
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CModelCharacter::Draw()
{
	//nullcheck
	if (!m_pModelPartsList.empty())
	{
		//���f�������J��Ԃ�
		for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
		{
			//�`��
			m_pModelPartsList[nCnt]->Draw();
		}
	}
	//����
	//nullcheck
	if (!m_pModelPartsWeaponList.empty())
	{
		//���f�������J��Ԃ�
		for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
		{
			//�`��
			m_pModelPartsWeaponList[nCnt]->Draw();
		}
	}
}
//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
std::unique_ptr<CModelCharacter> CModelCharacter::Create(MODEL_TYPE const modeltype)
{
	//�������m��
	std::unique_ptr<CModelCharacter>  pModelCharacter(new CModelCharacter);

	//�^�C�v
	pModelCharacter->m_type = modeltype;

	//������
	pModelCharacter->Init();

	//return
	return pModelCharacter;
}

//------------------------------------------------------------------------------
//�ǂݍ���
//------------------------------------------------------------------------------
HRESULT CModelCharacter::Load()
{
	for (int nCntModel = 0; nCntModel < MODEL_MAX; nCntModel++)
	{
		//���f���L�����N�^�p�̃������m��
		std::unique_ptr<CModelCharacterInfo> pModelCharacter(new CModelCharacterInfo);

		m_pModelCharacterList.emplace_back(std::move(pModelCharacter));

		std::cout << "new MODELCHARACTER : " << nCntModel << NEWLINE;


		//���f�����擾
		SUCCEEDED(LoadModelName((MODEL_TYPE)nCntModel)) ?
			std::cout << "LoadModelName [Success] : " << nCntModel << NEWLINE :		//����
			std::cout << "LoadModelName [Failed] : " << nCntModel << NEWLINE;			//���s

		//���f������
		for (size_t nCnt = 0; nCnt < m_pModelCharacterList[nCntModel]->pModelInfoList.size(); nCnt++)
		{
			CHossoLibrary::CreateModelInfo(m_pModelCharacterList[nCntModel]->pModelInfoList[nCnt].get());
		}
		std::cout << NEWLINE;
	}

	return S_OK;
}
//------------------------------------------------------------------------------
//�J��
//------------------------------------------------------------------------------
void CModelCharacter::UnLoad()
{
	if (m_pModelCharacterList.empty())
	{
		m_pModelCharacterList.clear();
	}
}
//------------------------------------------------------------------------------
//�L�����N�^�[�̃}�g���b�N�X�ݒ�
//------------------------------------------------------------------------------
void CModelCharacter::SetCharacterMtx(D3DXMATRIX *mtx)
{
	//���f��������
	for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
	{
		//�e�����Ȃ���
		if (m_pModelPartsList[nCnt]->GetParent() == -1)
		{
			//�匳�̃}�g���b�N�X�ݒ�
			m_pModelPartsList[nCnt]->SetParentMtx(mtx);
		}
		else
		{
			//�e�p�[�c�̃}�g���b�N�X�ݒ�
			m_pModelPartsList[nCnt]->SetParentMtx(m_pModelPartsList[m_pModelPartsList[nCnt]->GetParent()]->GetMtx());
		}
	}
	//���f��������
	for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
	{
		//�e�����Ȃ���
		if (m_pModelPartsWeaponList[nCnt]->GetParent() == -1)
		{
			//�匳�̃}�g���b�N�X�ݒ�
			m_pModelPartsWeaponList[nCnt]->SetParentMtx(mtx);
		}
		else
		{
			//�e�p�[�c�̃}�g���b�N�X�ݒ�
			m_pModelPartsWeaponList[nCnt]->SetParentMtx(m_pModelPartsList[m_pModelPartsWeaponList[nCnt]->GetParent()]->GetMtx());
		}
	}
}

//------------------------------------------------------------------------------
//���[�V�����Z�b�g
//------------------------------------------------------------------------------
void CModelCharacter::SetMotion(CMotion::MOTION_TYPE motiontype)
{
	//nullcheck
	if (m_pModelCharacterList[m_type])
	{
		//���[�V�������؂�ւ������
		if (m_motionOld != motiontype)
		{
			//�_�b�V���A�łƂ������A�łƂ�����Ă��������݂ɏo��悤��
			switch (m_motionOld)
			{
			case CMotion::PLAYER_WALK:
				m_nKey <= 1 ? m_bWalkMoveKey = true : m_bWalkMoveKey = false;

				break;
			case CMotion::PLAYER_DASH:
				m_nKey <= 1 ? m_bDashMoveKey = true : m_bDashMoveKey = false;
				break;

			}
			//�t���[���ƃL�[���Z�b�g
			ResetMotion();

			//�_�b�V���A�łƂ������A�łƂ�����Ă��������݂ɏo��悤��
			switch (motiontype)
			{
			case CMotion::PLAYER_WALK:
				m_nKey = m_bWalkMoveKey * 2;
				break;

			case CMotion::PLAYER_DASH:
				m_nKey = m_bDashMoveKey * 2;
				break;
			}

			//���[�V�����Đ�
			SetMotionStop(false);
		}

		//���[�V�����̐؂�ւ�
		m_motion = motiontype;

		//nullcheck
		if (!m_pModelPartsList.empty())
		{
			m_pModelPartsList[0]->SetMotionPosDest(motiontype, m_nKey);

			//���f�������J��Ԃ�
			for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
			{
				//���[�V�����̉�]�̌����擾
				m_pModelPartsList[nCnt]->SetMotionRotDest(motiontype, m_nKey);
			}
		}

		//nullcheck
		if (!m_pModelPartsWeaponList.empty())
		{
			//���f�������J��Ԃ�
			for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
			{
				//���[�V�������؂�ւ����0Key�ڂ̎�&&bAttack��true�̎�
				if (m_nKey == 0 && CMotion::CheckAttack(motiontype))
				{
					//�G�̖��G���ԃ��Z�b�g
					m_pModelPartsWeaponList[nCnt]->ResetEnemyInvincible();
				}

				//���[�V�����̉�]�̌����擾
				m_pModelPartsWeaponList[nCnt]->SetMotionRotDest(motiontype, m_nKey);

				//�U��������ꍇ
				if (CMotion::CheckAttackKey(motiontype, m_nKey))
				{
					//�U���ݒ�
					m_pModelPartsWeaponList[nCnt]->StartAttack();
					m_pModelPartsWeaponList[nCnt]->SetAttackInfo(motiontype);
				}
				else
				{
					//�U���I��
					m_pModelPartsWeaponList[nCnt]->EndAttack();
				}

			}
		}
	}
}
//------------------------------------------------------------------------------
//�f�t�H���g�̃��[�V�����Z�b�g
//------------------------------------------------------------------------------
void CModelCharacter::SetDefaultMotion()
{
	switch (m_type)
	{
	case MODEL_TYPE::MODEL_PLAYER:
		//�j���[�g�����ɖ߂�
		m_motion = CMotion::PLAYER_NEUTRAL;
		break;

	case MODEL_TYPE::MODEL_ENEMY:
		//�j���[�g�����ɖ߂�
		m_motion = CMotion::ENEMY_ARMOR_NEUTRAL;

		break;

	default:
		break;
	}
}

//------------------------------------------------------------------------------
//imgui�p
//------------------------------------------------------------------------------
void CModelCharacter::ShowModelCharacterInfo()
{
#ifdef _DEBUG

	//�L�����N�^�[�����
	if (ImGui::TreeNode("ModelCharacterInfo"))
	{
		ImGui::Text("Motion ; %d", m_motion);
		ImGui::Text("Key ; %d", m_nKey);
		ImGui::Text("Frame ; %d", m_nFrame);

		ImGui::TreePop();
	}
#endif //DEBUG
}

//------------------------------------------------------------------------------
// �p�[�c���ǂݍ���
//------------------------------------------------------------------------------
HRESULT CModelCharacter::LoadModelRelativeValue(MODEL_TYPE type)
{
	//�ϐ��錾
	FILE *pFile;			//�t�@�C���̃|�C���^
	char cReadText[MAX_TEXT];
	char cHeadText[MAX_TEXT];
	char cDieText[MAX_TEXT];
	int nCntParts = 0;			//�p�[�c��
	int nCntWeaponParts = 0;	//����p�[�c��
	bool bOrbit = false;

	D3DXVECTOR3 pos = ZeroVector3;
	D3DXVECTOR3 rot = ZeroVector3;
	D3DXVECTOR3 OrbitOffset = ZeroVector3;
	int nParent = 0;
	int nIndex = 0;

	//�t�@�C�����J��
	pFile = fopen(m_aFileName[type], "r");

	//�t�@�C�����������ꍇ
	if (pFile)
	{
		//�X�N���v�g������܂�
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
		}
		//�X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//�G���h�X�N���v�g������O���[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
				//���s
				if (strcmp(cHeadText, "\n") == 0)
				{
				}
				//�L�����N�^�[�Z�b�g��������
				else if (strcmp(cHeadText, "CHARACTERSET") == 0)
				{
					//�G���h�L�����N�^�[�Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_CHARACTERSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);
						//���s
						if (strcmp(cHeadText, "\n") == 0)
						{
						}
						//�p�[�c�Z�b�g��������
						else if (strcmp(cHeadText, "PARTSSET") == 0)
						{
							bOrbit = false;
							OrbitOffset = ZeroVector3;

							//�G���h�p�[�c�Z�b�g������܂Ń��[�v
							while (strcmp(cHeadText, "END_PARTSSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile);
								sscanf(cReadText, "%s", &cHeadText);

								//�O�Օ`�悷�邩�ǂ���
								if (strcmp(cHeadText, "ORBIT") == 0)
								{
									int nOrbit = 0;
									sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nOrbit);
									nOrbit ? bOrbit = true : bOrbit = false;
								}
								//�O�Ղ̃I�t�Z�b�g���W
								if (strcmp(cHeadText, "ORBIT_OFFSET") == 0)
								{
									sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &OrbitOffset.x, &OrbitOffset.y, &OrbitOffset.z);
								}
								//�C���f�b�N�X
								if (strcmp(cHeadText, "INDEX") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nIndex);
								}
								//�e�ԍ�
								if (strcmp(cHeadText, "PARENT") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nParent);
								}
								//�|�W�V����
								if (strcmp(cHeadText, "POS") == 0)
								{
									sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &pos.x, &pos.y, &pos.z);
								}
								//��]��
								if (strcmp(cHeadText, "ROT") == 0)
								{
									sscanf(cReadText, "%s %s %f %f %f", &cDieText, &cDieText, &rot.x, &rot.y, &rot.z);
								}

								if (strcmp(cHeadText, "END_PARTSSET") == 0)
								{
									if (!bOrbit)
									{
										m_pModelPartsList[nCntParts]->SetPartsInfo(nIndex, nParent, pos, rot);

										//�J�E���g�A�b�v
										nCntParts++;
									}
									else
									{
										m_pModelPartsWeaponList[nCntWeaponParts]->SetPartsInfo(nIndex, nParent, pos, rot);
										nCntWeaponParts++;
									}
								}
							}
						}
					}
				}
			}
		}
		fclose(pFile);
	}

	//�J���Ȃ�������
	else
	{
		std::cout << "�e�L�X�g�ǂݍ��ݎ��s" << "LoadModelRelativeValue()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
// ���f�����ǂݍ���
//------------------------------------------------------------------------------
HRESULT CModelCharacter::LoadModelName(MODEL_TYPE type)
{
	//�ϐ��錾
	FILE *pFile;					//�t�@�C���̃|�C���^
	char cReadText[MAX_TEXT];
	char cHeadText[MAX_TEXT];
	char cDieText[MAX_TEXT];
	int nBool = 0;
	int nNumModel = 0;		//���f����
	int nCntModel = 0;		//���f�����̃J�E���g
	int nWeaponID = 0;		//����ԍ�

							//�t�@�C�����J��
	pFile = fopen(m_aFileName[type], "r");

	//�t�@�C�����������ꍇ
	if (pFile != NULL)
	{
		//�X�N���v�g������܂�
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
		}
		//�X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//�G���h�X�N���v�g������O���[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
				//���s
				if (strcmp(cHeadText, "\n") == 0)
				{
				}
				//���f���ԍ���������
				else if (strcmp(cHeadText, "NUM_MODEL") == 0)
				{
					//���f����
					sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nNumModel);

					while (1)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);
						//�t�@�C���l�[���̓ǂݍ���
						if (strcmp(cHeadText, "MODEL_FILENAME") == 0)
						{
							//�������m��
							std::unique_ptr<CModelInfo> pModelInfo(new CModelInfo);

							//�z��ɒǉ�
							m_pModelCharacterList[type]->pModelInfoList.emplace_back(std::move(pModelInfo));

							//debug
							std::cout << "new ModelCharacter->pModelInfo : " << type << "-" << nCntModel << "-";

							char aName[128] = {};

							//���f�������
							sscanf(cReadText, "%s %s %s %s %s", &cDieText, &cDieText, &aName, &cDieText, &cDieText);

							m_pModelCharacterList[type]->pModelInfoList[nCntModel]->aName = aName;

							//debug ���f�����o��
							std::cout << "Name >> " << m_pModelCharacterList[type]->pModelInfoList[nCntModel]->aName.data() << NEWLINE;

							//���f�����J�E���g�A�b�v
							nCntModel++;

							//�ŏ��ɐ錾���ꂽ���f�����ɂȂ�����
							if (nCntModel == nNumModel)
							{
								//���[�v�𔲂���
								break;
							}
						}
					}
				}
				//���f���ԍ���������
				else if (strcmp(cHeadText, "WEAPON_ID") == 0)
				{
					//����ԍ��擾
					sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nWeaponID);

					//�z��ɒǉ�
					m_pModelCharacterList[type]->nWeaponID.emplace_back(nWeaponID);

					//debug ���f�����o��
					std::cout << "WeaponID >> " << nWeaponID << NEWLINE;

				}

			}
		}
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		//���s
		std::cout << "�e�L�X�g�ǂݍ��ݎ��s" << "LoadModelName()" << NEWLINE;

		return E_FAIL;
	}

	return S_OK;
}

//------------------------------------------------------------------------------
// �I�t�Z�b�g���ۑ�
//------------------------------------------------------------------------------
HRESULT CModelCharacter::SaveModelOffset()
{
	FILE *pFile;

	int nRotNum = 0;
	char cHeadtext[128];
	char cWriteText[128];

	//�t�@�C���ǂݍ���
	pFile = fopen(OFFSET_SAVE_TEXT, "w");

	//nullcheck
	if (pFile != nullptr)
	{
		//�u���b�N�R�����g
		fputs(COMMENT02, pFile);
		fputs(COMMENT01, pFile);

		strcpy(cHeadtext, "//Offset\n");
		strcpy(cHeadtext, "//�e�L�X�g�ɃR�s�y���Ă�������\n");

		fputs(cHeadtext, pFile);

		strcpy(cHeadtext, "//Author:Yoshiki Hosoya\n");
		fputs(cHeadtext, pFile);

		fputs(COMMENT01, pFile);
		fputs(COMMENT02, pFile);
		fputs(NEWLINE, pFile);

		//�u���b�N�R�����g�I��//

			//�L�����N�^�[�Z�b�g
			fputs("CHARACTERSET", pFile);
			fputs(NEWLINE, pFile);

			//nullcheck
			if (!m_pModelPartsList.empty())
			{
				for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
				{

					//�p�[�c�Z�b�g
					fputs("	PARTSSET", pFile);
					fputs(NEWLINE, pFile);

					//�C���f�b�N�X
					sprintf(cWriteText, "		%s %s %d", "INDEX", &EQUAL, m_pModelPartsList[nCnt]->GetIndex());
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//�e�ԍ�
					sprintf(cWriteText, "		%s %s %d", "PARENT", &EQUAL, m_pModelPartsList[nCnt]->GetParent());
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//���W
					sprintf(cWriteText, "		%s %s %.1f %.1f %.1f", "POS", &EQUAL,
						m_pModelPartsList[nCnt]->GetPos().x,
						m_pModelPartsList[nCnt]->GetPos().y,
						m_pModelPartsList[nCnt]->GetPos().z);
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//��]
					sprintf(cWriteText, "		%s %s %.1f %.1f %.1f", "ROT", &EQUAL,
						m_pModelPartsList[nCnt]->GetRot().x,
						m_pModelPartsList[nCnt]->GetRot().y,
						m_pModelPartsList[nCnt]->GetRot().z);
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//�p�[�c�Z�b�g�I��
					fputs("	END_PARTSSET", pFile);
					fputs(NEWLINE, pFile);
					fputs(NEWLINE, pFile);

				}
			}

			//nullcheck
			if (!m_pModelPartsWeaponList.empty())
			{
				for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
				{

					//�p�[�c�Z�b�g
					fputs("	PARTSSET", pFile);
					fputs(NEWLINE, pFile);

					//�O��on
					sprintf(cWriteText, "		%s %s %d", "ORBIT", &EQUAL, 1);
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//�C���f�b�N�X
					sprintf(cWriteText, "		%s %s %d", "INDEX", &EQUAL, m_pModelPartsWeaponList[nCnt]->GetIndex());
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//�e�ԍ�
					sprintf(cWriteText, "		%s %s %d", "PARENT", &EQUAL, m_pModelPartsWeaponList[nCnt]->GetParent());
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//���W
					sprintf(cWriteText, "		%s %s %.1f %.1f %.1f", "POS", &EQUAL,
						m_pModelPartsWeaponList[nCnt]->GetPos().x,
						m_pModelPartsWeaponList[nCnt]->GetPos().y,
						m_pModelPartsWeaponList[nCnt]->GetPos().z);
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//��]
					sprintf(cWriteText, "		%s %s %.1f %.1f %.1f", "ROT", &EQUAL,
						m_pModelPartsWeaponList[nCnt]->GetRot().x,
						m_pModelPartsWeaponList[nCnt]->GetRot().y,
						m_pModelPartsWeaponList[nCnt]->GetRot().z);
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

					//�p�[�c�Z�b�g�I��
					fputs("	END_PARTSSET", pFile);
					fputs(NEWLINE, pFile);
					fputs(NEWLINE, pFile);

				}
			}
			//�A�^�b�N�Z�b�g�I��
			fputs("END_CHARACTERSET", pFile);
			fputs(NEWLINE, pFile);
			fputs(NEWLINE, pFile);


		std::cout << "Save Succsess!!  SaveModelOffset()" << NEWLINE;

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		//�t�@�C�����J���܂���ł���
		std::cout << "Save FAILED!!  Can't Open File. SaveModelOffset()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
// �t���[�����Ō�܂ōs�������m�F
//------------------------------------------------------------------------------
void CModelCharacter::FrameCheck()
{
	//�t���[�������l�܂ŗ�����
	if (m_nFrame >= CMotion::GetFrame(m_motion, m_nKey))
	{
		//�t���[��������
		m_nFrame = 0;

		//�L�[���Z
		m_nKey++;

		//�L�[���Ō�܂ōs������
		KeyCheck();

		//���̃��[�V���������Z�b�g
		SetMotion(m_motion);
	}
}

//------------------------------------------------------------------------------
// �����I�Ƀ��[�V�����؂�ւ��@�OF�ڂ̉�]�̂Ƃ��ɂ����Ă�
//------------------------------------------------------------------------------
void CModelCharacter::ForcedUpdate(CMotion::MOTION_TYPE motiontype, int nKey)
{
	m_pModelPartsList[0]->SetForcedPos(motiontype, m_nKey);

	//���f�������J��Ԃ�
	for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
	{
		//���[�V�����̉�]�̌����擾
		m_pModelPartsList[nCnt]->SetForcedRot(motiontype, m_nKey);
	}
	//���f�������J��Ԃ�
	for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
	{
		//���[�V�����̉�]�̌����擾
		m_pModelPartsWeaponList[nCnt]->SetForcedRot(motiontype, m_nKey);
	}
}
//------------------------------------------------------------------------------
// �U���Ɋւ�����̍X�V
//------------------------------------------------------------------------------
void CModelCharacter::UpdateAttackInfo()
{
	//nullcheck
	if (!m_pModelPartsWeaponList.empty())
	{
		//���f�������J��Ԃ�
		for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
		{
			//�U��������ꍇ
			if (CMotion::CheckAttackKey(m_motion,m_nKey))
			{
				//�U���̐ݒ�ύX
				m_pModelPartsWeaponList[nCnt]->SetAttackInfo(m_motion);
			}
		}
	}
}
//------------------------------------------------------------------------------
// �ړ�����L�[���m�F
//------------------------------------------------------------------------------
bool CModelCharacter::CheckMoveKey()
{
	//�t���[�����O�̎�
	if (m_nFrame == 0)
	{
		//nullcheck
		if (CMotion::GetAttackInfo(m_motion))
		{
			//�L�[���w�肳�ꂽ�L�[�̎�
			if (CMotion::GetAttackInfo(m_motion)->nMoveKey == m_nKey)
			{
				return true;
			}
		}
	}
	return false;
}
//------------------------------------------------------------------------------
// �L�����N�^�[�̃|�C���^
//------------------------------------------------------------------------------
void CModelCharacter::SetCharacterPtr(std::shared_ptr<CCharacter> pCharacter)
{
	if (!m_pModelPartsWeaponList.empty())
	{
		//���탂�f������
		for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
		{
			//�L�����N�^�[�̃|�C���^
			m_pModelPartsWeaponList[nCnt]->SetHasCharacterPtr(pCharacter);
		}
	}
}
//------------------------------------------------------------------------------
//���̍����擾
//------------------------------------------------------------------------------
float CModelCharacter::GetWaistHeight()
{
	return m_pModelPartsList[0]->GetPos().y;
}
//------------------------------------------------------------------------------
//���ꂼ��̃p�[�c�փ}�e���A���J���[�ݒ�
//------------------------------------------------------------------------------
void CModelCharacter::SetPartsMaterialCol(CSceneX::MATERIAL_COL matCol)
{
	//nullcheck
	if (!m_pModelPartsList.empty())
	{
		//���f��������
		for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
		{
			m_pModelPartsList[nCnt]->SetMaterialCol(matCol);
		}
	}
	//nullcheck
	if (!m_pModelPartsWeaponList.empty())
	{
		//���f��������
		for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
		{
			m_pModelPartsWeaponList[nCnt]->SetMaterialCol(matCol);
		}
	}
}
//------------------------------------------------------------------------------
// �p�[�c�̃C���f�b�N�X���擾
//------------------------------------------------------------------------------
CModelParts * CModelCharacter::GetPartsPtr(int nIndex)
{
	//���f��������
	for (size_t nCnt = 0; nCnt < m_pModelPartsList.size(); nCnt++)
	{
		//�C���f�b�N�X�������Ă邩
		if (m_pModelPartsList[nCnt]->GetIndex() == nIndex)
		{
			//return
			return m_pModelPartsList[nCnt].get();
		}

	}
	//���f��������
	for (size_t nCnt = 0; nCnt < m_pModelPartsWeaponList.size(); nCnt++)
	{
		//�C���f�b�N�X�������Ă邩
		if (m_pModelPartsWeaponList[nCnt]->GetIndex() == nIndex)
		{
			//return
			return m_pModelPartsWeaponList[nCnt].get();
		}
	}

	return nullptr;
}

//------------------------------------------------------------------------------
// �L�[���Ō�܂ł������̂��m�F
//------------------------------------------------------------------------------
void CModelCharacter::KeyCheck()
{
	//�L�[�����l�܂ŗ�����
	if (m_nKey >= CMotion::GetNumKey(m_motion))
	{
		//�t���[���ƃL�[������
		ResetMotion();

		//���[�v���Ȃ���
		if (!CMotion::CheckLoop(m_motion))
		{
			if (CManager::GetMode() != CManager::MODE_DEBUG_MOTION_VIEWER)
			{
				//�f�t�H���g���[�V�����Z�b�g
				SetDefaultMotion();
			}
			else
			{
				//�f�o�b�O���͓������~�߂�
				SetMotionStop(true);
			}
		}
	}
}