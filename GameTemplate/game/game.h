/*!
 * @brief	�Q�[���N���X�B
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
 * @brief	�Q�[���N���X�B
 */
class Game : public GameObject {
public:
	/*!
	 * @brief	�R���X�g���N�^�B
	 */
	Game();
	/*!
	 * @brief	�f�X�g���N�^�B
	 */
	~Game();
	/*!
	 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
	 */
	bool Start();
	/*!
	 * @brief	�X�V�B
	 */
	void Update();
	/*!
	 * @brief	�`��B
	 */
	void Render();

	//�J�����̃C���X�^���X���擾
	GameCamera* GetGameCamera()
	{
		return gameCamera;
	}
	//�v���C���[�̃C���X�^���X�擾
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