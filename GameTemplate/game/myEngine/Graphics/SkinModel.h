/*!
*@brief	�X�L�����f��
*/
#pragma once

#include "myEngine/Graphics/Animation.h"

class SkinModelData;
class RenderContext;
class Light;
/*!
*@brief	�X�L�����f��
*/
class SkinModel {
public:
	SkinModel();
	~SkinModel();
	/*!
	*@brief	������
	*/
	void Init(SkinModelData* modelData);
	/*!
	*@brief	�`��B
	*/
	void Draw(const D3DXMATRIX* viewMatrix, const D3DXMATRIX* projMatrix);
	
	/*!
	*@brief	���[���h�s����X�V�B
	*@param[in]		trans	���s�ړ��B
	*@param[in]		rot		��]�B
	*@param[in]		scale	�g��B
	*/
	void UpdateWorldMatrix( const D3DXVECTOR3& trans, const D3DXQUATERNION& rot, const D3DXVECTOR3& scale );
	/*!
	*@brief	���C�g��ݒ�B
	*/
	void SetLight(Light* light)
	{
		this->light = light;
	}
	//�X�y�L�����}�b�v��ݒ�
	void SetSpecularMap(LPDIRECT3DTEXTURE9 specMap)
	{
		specularMap = specMap;
	}
	//�@���}�b�v��ݒ�
	void SetNormalMap(LPDIRECT3DTEXTURE9 normalMap) 
	{
		this->normalMap = normalMap;
	}
	//�L���[�u�}�b�v��ݒ�
	void SetCubeMap(LPDIRECT3DCUBETEXTURE9 cubeMap)
	{
		this->cubeMap = cubeMap;
	}
	//���[���h���W���擾
	const D3DXMATRIX& GetWorldMatrix()
	{
		return worldMatrix;
	}
	//��]�s����擾
	const D3DXMATRIX& GetRotationMatrix()
	{
		return rotationMatrix;
	}
	//�V���h�E�}�b�v�쐬�t���O��ݒ�
	//DrawShadowMap �V���h�E�}�b�v��`�悷�邩
	//RecieveShadow �V���h�E���V�[�o�[���ǂ���
	void SetDrawShadowMap(bool DrawShadowMap, bool RecieveShadow)
	{
		isDrawShadowMap = DrawShadowMap;
		isRecieveShadow = RecieveShadow;
	}
	//�[�x�e�X�g�����邩�ݒ�
	void SetDepthStencilRender(bool DepthStencilRender)
	{
		isDepthStencilRender = DepthStencilRender;
	}
	/*!
	*@brief	�I���W�i�����b�V���̐擪���擾����B
	*/
	LPD3DXMESH GetOrgMeshFirst();
private:
	D3DXMATRIX			worldMatrix;				//!<���[���h�s��B
	D3DXMATRIX			rotationMatrix;				//!<��]�s��B
	SkinModelData*		skinModelData = nullptr;	//!<�X�L�����f���f�[�^�B
	ID3DXEffect*		pEffect = nullptr;			//!<�G�t�F�N�g�B
	Animation			animation;					//!<�A�j���[�V�����B
	Light*				light = nullptr;			//!<���C�g�B

	LPDIRECT3DTEXTURE9 specularMap = NULL;			//!<�X�y�L�����}�b�v�B
	LPDIRECT3DTEXTURE9 normalMap = NULL;			//!<�@���}�b�v
	LPDIRECT3DCUBETEXTURE9 cubeMap = NULL;			//!<�L���[�u�}�b�v
	bool isDrawShadowMap = false;
	bool isRecieveShadow = false;
	bool isDepthStencilRender = false;
};
