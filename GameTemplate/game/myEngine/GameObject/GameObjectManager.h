/*!
*@brief	ゲームオブジェクトマネージャークラス
*/
#pragma once
#include "GameObject.h"

class GameObjectManager
{
public:
	/*!
	*@brief	コンストラクタ
	*/
	GameObjectManager();
	/*!
	*@brief	デストラクタ
	*/
	~GameObjectManager();
	/*!
	*@brief	更新
	*/
	void Update();
	/*!
	*@brief	先に描画
	*/
	void PreRender();
	/*!
	*@brief	描画
	*/
	void Render();
	/*!
	*@brief	後から描画
	*/
	void PostRender();
	/*!
	* @brief	影を描画
	* @param[in]	viewMatrix		ビュー行列
	* @param[in]	projMatrix		プロジェクション行列
	* @param[in]	isDrawShadowMap	シャドウマップを描くフラグ
	* @param[in]	isRecieveShadow	シャドウレシーバーかどうか
	*/
	void RenderToShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow);
	/*!
	*@brief	深度値を描画
	*/
	void RenderDepthValue();
	/*!
	*@brief	インスタンスをゲームオブジェクトに追加
	*@return	クラスのインスタンス
	*/
	template<class T>
	T* NewGameObject()
	{
		T* newObject = new T();

		gameObjects.push_back(newObject);

		return newObject;
	}
	/*!
	*@brief	インスタンスをゲームオブジェクトに追加
	*@param[in]		go		クラスのインスタンス
	*@detail	引数はゲームオブジェクトを継承しているものを使用する
	*			この関数を使用して登録した場合は、登録したクラスを保持しているクラスは最後に削除する
	*/
	void AddGameObject(GameObject* go)
	{
		gameObjects.push_back(go);
	}
	/*!
	*@brief	インスタンスをゲームオブジェクトから削除
	*/
	void DeleteGameObject();

private:
	std::list<GameObject*>	gameObjects;	//ゲームオブジェクトの配列
};

extern GameObjectManager* goMgr;