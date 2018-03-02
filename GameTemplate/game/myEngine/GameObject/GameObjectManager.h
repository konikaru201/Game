#pragma once
#include "GameObject.h"

class GameObjectManager
{
public:
	//コンストラクタ
	GameObjectManager();

	//デストラクタ
	~GameObjectManager();

	//更新
	void Update();

	//描画
	void Render();

	//影の描画
	void RenderToShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);

	//インスタンスをゲームオブジェクトに追加
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

	//インスタンスをゲームオブジェクトから削除
	void DeleteGameObject();

private:
	std::list<GameObject*>	gameObjects;	//ゲームオブジェクトの配列
	//typedef std::list<GameObject*>	GameObjectList;
	//std::vector<GameObjectList>		objectList;
};

extern GameObjectManager* goMgr;