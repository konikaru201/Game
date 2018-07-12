/*!
*@brief	�Q�[���I�u�W�F�N�g�}�l�[�W���[�N���X
*/
#pragma once
#include "GameObject.h"

class GameObjectManager
{
public:
	/*!
	*@brief	�R���X�g���N�^
	*/
	GameObjectManager();
	/*!
	*@brief	�f�X�g���N�^
	*/
	~GameObjectManager();
	/*!
	*@brief	�X�V
	*/
	void Update();
	/*!
	*@brief	��ɕ`��
	*/
	void PreRender();
	/*!
	*@brief	�`��
	*/
	void Render();
	/*!
	*@brief	�ォ��`��
	*/
	void PostRender();
	/*!
	* @brief	�e��`��
	* @param[in]	viewMatrix		�r���[�s��
	* @param[in]	projMatrix		�v���W�F�N�V�����s��
	* @param[in]	isDrawShadowMap	�V���h�E�}�b�v��`���t���O
	* @param[in]	isRecieveShadow	�V���h�E���V�[�o�[���ǂ���
	*/
	void RenderToShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
	/*!
	*@brief	�[�x�l��`��
	*/
	void RenderDepthValue();
	/*!
	*@brief	�C���X�^���X���Q�[���I�u�W�F�N�g�ɒǉ�
	*@return	�N���X�̃C���X�^���X
	*/
	template<class T>
	T* NewGameObject()
	{
		T* newObject = new T();

		gameObjects.push_back(newObject);

		return newObject;
	}
	/*!
	*@brief	�C���X�^���X���Q�[���I�u�W�F�N�g�ɒǉ�
	*@param[in]		go		�N���X�̃C���X�^���X
	*@detail	�����̓Q�[���I�u�W�F�N�g���p�����Ă�����̂��g�p����
	*			���̊֐����g�p���ēo�^�����ꍇ�́A�o�^�����N���X��ێ����Ă���N���X�͍Ō�ɍ폜����
	*/
	void AddGameObject(GameObject* go)
	{
		gameObjects.push_back(go);
	}
	/*!
	*@brief	�C���X�^���X���Q�[���I�u�W�F�N�g����폜
	*/
	void DeleteGameObject();

private:
	std::list<GameObject*>	gameObjects;	//�Q�[���I�u�W�F�N�g�̔z��
};

extern GameObjectManager* goMgr;