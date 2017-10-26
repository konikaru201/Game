/*!
 * @brief	�Q�[��
 */
#include "stdafx.h"
#include "game.h"

SMapInfo mapLocInfo[] = {
#include "Map/locationinfo.h"
};

/*!
 * @brief	�R���X�g���N�^�B
 */
Game::Game()
{
}
/*!
 * @brief	�f�X�g���N�^�B
 */
Game::~Game()
{
	delete g_physicsWorld;
	g_physicsWorld = NULL;
	delete gameCamera;
	gameCamera = NULL;
	delete player;
	player = NULL;
	delete map;
	map = NULL;
	delete pad;
	pad = NULL;
}
/*!
 * @brief	�Q�[�����N�����Ă����x�����Ă΂��֐��B
 */
bool Game::Start()
{
	//���C�g��������
	light.SetDiffuseLightDirection(0, D3DXVECTOR4(0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(1, D3DXVECTOR4(-0.707f, 0.0f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(2, D3DXVECTOR4(0.0f, 0.707f, -0.707f, 1.0f));
	light.SetDiffuseLightDirection(3, D3DXVECTOR4(0.0f, -0.707f, -0.707f, 1.0f));

	light.SetDiffuseLightColor(0, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(1, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetDiffuseLightColor(2, D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));
	light.SetDiffuseLightColor(3, D3DXVECTOR4(0.2f, 0.2f, 0.2f, 1.0f));
	light.SetAmbientLight(D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f));

	goMgr = new GameObjectManager;

	g_physicsWorld = new PhysicsWorld;
	g_physicsWorld->Init();

	titleScene = new TitleScene;
	gameCamera = new GameCamera;	//�J��������
	player = new Player;	//�v���C���[����
	map = new Map;		//�}�b�v����
	pad = new Pad;

	titleScene->Initialize();

	//�Q�[���I�u�W�F�N�g�ɓo�^
	goMgr->AddGameObject(titleScene);
	goMgr->AddGameObject(gameCamera);
	goMgr->AddGameObject(player);
	goMgr->AddGameObject(map);
	goMgr->AddGameObject(pad);

	//�z�u����Ă���I�u�W�F�N�g�̐����v�Z
	int numObject = sizeof(mapLocInfo) / sizeof(mapLocInfo[0]);
	map->Create(mapLocInfo, numObject);

	return true;
}
/*!
 * @brief	�X�V�B
 */
void Game::Update()
{
	goMgr->Update();
}
/*!
 * @brief	�`��B
 */
void Game::Render()
{
	goMgr->Render();
}
