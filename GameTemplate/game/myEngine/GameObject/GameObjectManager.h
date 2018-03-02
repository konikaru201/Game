#pragma once
#include "GameObject.h"

class GameObjectManager
{
public:
	//�R���X�g���N�^
	GameObjectManager();

	//�f�X�g���N�^
	~GameObjectManager();

	//�X�V
	void Update();

	//�`��
	void Render();

	//�e�̕`��
	void RenderToShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

	//�C���X�^���X���Q�[���I�u�W�F�N�g�ɒǉ�
	template<class T>
	T* NewGameObject()
	{
		T* newObject = new T();

		gameObjects.push_back(newObject);
		//objectList.push_back(newObject);


		return newObject;
	}

	void AddGameObject(GameObject* go)
	{
		if (!go->GetIsRegist()) {
			gameObjects.push_back(go);
			go->SetIsRegist(true);
		}
	}

	//�C���X�^���X���Q�[���I�u�W�F�N�g����폜
	void DeleteGameObject();

private:
	std::list<GameObject*>	gameObjects;	//�Q�[���I�u�W�F�N�g�̔z��
	//typedef std::list<GameObject*>	GameObjectList;
	//std::vector<GameObjectList>		objectList;
};

extern GameObjectManager* goMgr;