/*!
*@brief	�R�C���N���X
*/
#pragma once

#include "myEngine/GameObject/GameObject.h"

struct CoinInfo {
	D3DXVECTOR3 position;		//���W
	D3DXQUATERNION rotation;	//��]
};

class Coin : public GameObject {
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	Coin();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~Coin();
	/*!
	*@brief	������
	* @param[in]	numInstancing	�C���X�^���X�̐�
	*/
	void Init(int numInstancing);
	/*!
	*@brief	�X�V����O�Ɉ�x�����Ă΂��
	*/
	bool Start();
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	�`��
	*/
	void Render();
	/*!
	* @brief	�e��`��
	* @param[in]	viewMatrix		�r���[�s��
	* @param[in]	projMatrix		�v���W�F�N�V�����s��
	* @param[in]	isDrawShadowMap	�V���h�E�}�b�v��`���t���O
	* @param[in]	isRecieveShadow	�V���h�E���V�[�o�[���ǂ���
	*/
	void RenderShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
	/*!
	*@brief	�C���X�^���V���O�`��p�̃��[���h�s���������
	*/
	void InitInstancingWorldMatrix();
	/*!
	*@brief	�C���X�^���V���O�`��p�̃��[���h�s����X�V
	*/
	void UpdateInstancingWorldMatrix();
	/*!
	*@brief	�R�C���̍��W�Ɖ�]��ۑ�
	*@param[in]		coinInfoList	�R�C���̃��X�g
	*/
	void SetCoinInfoList(std::list<CoinInfo> coinInfoList)
	{
		m_coinInfoList = coinInfoList;
	}

private:
	SkinModel			m_model;				//�X�L�����f��
	SkinModelData		m_modelData;			//�X�L�����f���f�[�^
	Light				m_light;				//���C�g
	D3DXVECTOR3			m_scale;				//�g�嗦
	D3DXVECTOR3			m_initPosition;			//�������W
	bool				m_flag = false;			//�R�C���l���t���O
	float				m_moveSpeed = 0.05f;	//�ړ����x
	int					m_numInstancing = 0;	//�C���X�^���V���O�`�悷�鐔
	std::list<CoinInfo> m_coinInfoList;			//�R�C���̃��X�g
};