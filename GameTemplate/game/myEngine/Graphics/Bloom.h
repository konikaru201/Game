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
	LPD3DXEFFECT effect;												//�V�F�[�_�[�G�t�F�N�g
	CRenderTarget luminanceRenderTarget;								//�P�x�𒊏o���邽�߂̃����_�����O�^�[�Q�b�g
	CRenderTarget downSamplingRenderTarget[2];
	static const int NUM_WEIGHTS = 8;									//�K�E�X�u���[�̏d��
	float weights[NUM_WEIGHTS];											//�K�E�X�u���[�Ŏg���d�݃e�[�u��
};