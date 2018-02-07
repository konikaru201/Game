#pragma once

#include "RenderTarget.h"

class Bloom {
public:
	//�R���X�g���N�^
	Bloom();

	//�f�X�g���N�^
	~Bloom();

	//�`��
	void Render();

	//�d�݂��v�Z
	void UpdateWeight(float dispersion);
private:
	static const int NUM_WEIGHTS = 8;				//�K�E�X�u���[�̏d��
	static const int NUM_DOWN_SAMPLING_COUNT = 5;	//�_�E���T���v�����O�����
	LPD3DXEFFECT m_effect;							//�V�F�[�_�[�G�t�F�N�g
	CRenderTarget m_luminanceRenderTarget;			//�P�x�𒊏o���邽�߂̃����_�����O�^�[�Q�b�g
	CRenderTarget m_combineRenderTarget;			//�ڂ��������p�̃����_�����O�^�[�Q�b�g
	CRenderTarget m_downSamplingRenderTarget[NUM_DOWN_SAMPLING_COUNT][2]; //�_�E���T���v�����O�p�̃����_�����O�^�[�Q�b�g
	float m_weights[NUM_WEIGHTS];					//�K�E�X�u���[�Ŏg���d�݃e�[�u��
};