#include "ObjectManager.h"
#include "_Classes_Yu/_Enemys/_EneParamsLoad/EneParamsLoad.h"

CellList cellList = CellList{};
EnemyManager* ObjectManager::m_enemy_;

ObjectManager::ObjectManager() {
	EneParamsLoad::GetInstance().LoadParams();

	m_enemy_	= new EnemyManager(1);
	m_bullet_	= new BulletManager();
}

ObjectManager::~ObjectManager() {
	delete m_bullet_;
	delete m_enemy_;
}

void ObjectManager::Initialize() {
	m_enemy_->Initialize();
}

void ObjectManager::LoadAssets() {
	m_enemy_->LoadAssets();
	m_bullet_->LoadAssets();
}

void ObjectManager::Update(const float deltaTime) {
	m_enemy_->Update(deltaTime);
	m_bullet_->Update(deltaTime);
}

void ObjectManager::RenderModels() {
	m_enemy_->Render();
	m_bullet_->Render();
}

void ObjectManager::RenderSprites() {

}