/*!
*@brief	��ʊE�[�x�N���X
*/
#pragma once

#include "RenderTarget.h"

class DepthOfField {
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	DepthOfField();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~DepthOfField();
	/*!
	*@brief	�`��
	*/
	void Render();
	/*!
	*@brief	�d�݂��v�Z
	*@param[in]	dispersion		�d�݂̊���
	*/
	void UpdateWeight(float dispersion);
	/*!
	*@brief	��ʊE�[�x�����邩�ǂ���
	*/
	void SetDepthOfField(bool isDepthOfField)
	{
		m_isDepthOfField = isDepthOfField;
	}
private:
	static const int	NUM_WEIGHTS = 8;			//�K�E�X�u���[�̏d��
	LPD3DXEFFECT		m_effect;					//�V�F�[�_�[�G�t�F�N�g
	CRenderTarget		m_depthValueRenderTarget;
	CRenderTarget		m_blurRenderTarget[2][2];
	CRenderTarget		m_combineRenderTarget[2];	//�ڂ��������p�̃����_�����O�^�[�Q�b�g
	float				m_weights[NUM_WEIGHTS];		//�K�E�X�u���[�Ŏg���d�݃e�[�u��
	bool				m_isDepthOfField = false;
};

extern DepthOfField* depthOfField;