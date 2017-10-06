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

	//インスタンスをゲームオブジェクトに追加
	template<class T>
	T* NewGameObject()
	{
		T* newObject = new T();

		gameObjects.push_back(newObject);
		//objectList.push_back(newObject);


		return newObject;
	}

	//インスタンスをゲームオブジェクトから削除
	void DeleteGameObject();
private:
	std::list<GameObject*>	gameObjects;	//ゲームオブジェクトの配列
	//typedef std::list<GameObject*>	GameObjectList;
	//std::vector<GameObjectList>		objectList;
};

extern GameObjectManager* goMgr;