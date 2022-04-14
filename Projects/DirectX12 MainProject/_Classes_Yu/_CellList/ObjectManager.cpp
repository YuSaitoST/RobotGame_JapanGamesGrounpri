#include "ObjectManager.h"

CellList cellList = CellList{};
EnemyManager* ObjectManager::m_enemy_;

ObjectManager::ObjectManager() {
	m_enemy_ = new EnemyManager(1);

	m_enemy_->PushList(Vector3(0.0f, 0.0f, 250.0f), 1.0f);
}

ObjectManager::~ObjectManager() {
	delete m_enemy_;
}

void ObjectManager::Initialize() {
	m_enemy_->Initialize();
}

void ObjectManager::LoadAssets() {
	m_enemy_->LoadAssets();
}

void ObjectManager::Update(const float deltaTime) {
	m_enemy_->Update(deltaTime);
}

void ObjectManager::RenderModels() {
	m_enemy_->Render();
}

void ObjectManager::RenderSprites() {

}