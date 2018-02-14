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

		obj->PreUpdate();
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

void GameObjectManager::Render()
{
	for (GameObject* obj : gameObjects) {
		if (!obj->GetisDead()) {
			obj->Render();
		}
	}
}

void GameObjectManager::DeleteGameObject()
{
	std::list<GameObject*>::iterator it;

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