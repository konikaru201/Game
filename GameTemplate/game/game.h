/*!
 * @brief	ゲームクラス。
 */

#pragma once

#include "Map/Map.h"
#include "Player/Player.h"
#include "Camera/GameCamera.h"
#include "Scene/TitleScene.h"
#include "myEngine/Physics/Physics.h"
#include "myEngine/GameObject/GameObject.h"
#include "myEngine/GameObject/GameObjectManager.h"
#include "myEngine/HID/Pad.h"
/*!
 * @brief	ゲームクラス。
 */
class Game : public GameObject {
public:
	/*!
	 * @brief	コンストラクタ。
	 */
	Game();
	/*!
	 * @brief	デストラクタ。
	 */
	~Game();
	/*!
	 * @brief	ゲームが起動してから一度だけ呼ばれる関数。
	 */
	bool Start();
	/*!
	 * @brief	更新。
	 */
	void Update();
	/*!
	 * @brief	描画。
	 */
	void Render();

	//カメラのインスタンスを取得
	GameCamera* GetGameCamera()
	{
		return gameCamera;
	}
	//プレイヤーのインスタンス取得
	Player* GetPlayer()
	{
		return player;
	}
	Pad* GetPad()
	{
		return pad;
	}
	GameObjectManager* GetGameObjectManajer()
	{
		return goMgr;
	}
	Light& GetLight()
	{
		return light;
	}
private:
	GameObjectManager*	goMgr;
	Light light;
	Map* map;
	Player* player;
	GameCamera* gameCamera;
	Pad* pad;
	TitleScene* titleScene;

	D3DXVECTOR3 toCameraPos;
};

extern Game* game;