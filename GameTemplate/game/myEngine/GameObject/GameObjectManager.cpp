#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{

}

GameObjectManager::~GameObjectManager()
{
	gameObjects.clear();
}

void GameObjectManager::Update()
{
	for (GameObject* obj : gameObjects) {
		if (obj->IsStart() == false) {
			obj->Start();
			obj->SetStart();
		}
		if (!obj->GetisDead()) {
			obj->PreUpdate();
		}
	}
	for (GameObject* obj : gameObjects) {
		if (obj->IsStart() == false) {
			obj->Start();
			obj->SetStart();
		}
		if (!obj->GetisDead()) {
			obj->Update();
		}
	}

	for (GameObject* obj : gameObjects) {

		obj->PostUpdate();
	}
}

void GameObjectManager::PreRender()
{
	for (GameObject* obj : gameObjects) {
		if (!obj->GetisDead()) {
			obj->PreRender();
		}
	}
}

void GameObjectManager::Render()
{
	for (GameObject* obj : gameObjects) {
		if (!obj->GetisDead()) {
			obj->Render();
		}
	}
}

void GameObjectManager::PostRender()
{
	for (GameObject* obj : gameObjects) {
		if (!obj->GetisDead()) {
			obj->PostRender();
		}
	}
}

void GameObjectManager::RenderToShadow(D3DXMATRIX* viewMatrix, D3DXMATRIX* projMatrix, bool isDrawShadowMap, bool isRecieveShadow)
{
	for (GameObject* obj : gameObjects) {
		if (obj->GetShadowToRender()){
			obj->RenderShadow(viewMatrix, projMatrix, isDrawShadowMap, isRecieveShadow);
		}
	}
}

void GameObjectManager::RenderDepthValue()
{
	for (GameObject* obj : gameObjects) {
		obj->RenderDepthValue();
	}
}

void GameObjectManager::DeleteGameObject()
{
	std::list<GameObject*>::iterator it;

	it = gameObjects.begin();

	while (it != gameObjects.end()) {
		if ((*it)->GetIsChangeState()) {
			it = gameObjects.erase(it);
		}
		else {
			it++;
		}
	}

	it = gameObjects.begin();

	while (it != gameObjects.end()) {
		if ((*it)->GetisDead()) {
			GameObject *deleteObject = *it;
			it = gameObjects.erase(it);
			delete deleteObject;
		}
		else {
			it++;
		}
	}
}