#include "EnemyManager.h"
#include "GeneralVariables.h"

EnemyManager::EnemyManager()
{
	enemy_texture_.loadFromFile("gfx/slime_dude.png");
	CreateNewEnemy();
}

EnemyManager::~EnemyManager()
{
	delete current_enemy_;
}

void EnemyManager::AttackEnemy(float damage)
{
	if (!current_enemy_ || current_enemy_->ChangeHealth(damage)) {
		delete current_enemy_;
		CreateNewEnemy();
	}
}

float EnemyManager::EnemyTurn(float dt)
{
	current_enemy_->ResetDefence();
	return current_enemy_->Turn(dt);
}

void EnemyManager::CreateNewEnemy()
{
	current_enemy_ = new Enemy(20.0f, "Enemy", &enemy_texture_, sf::Vector2f(400.0f, 500.0f),
		enemy_position_, 2.0f);
}

void EnemyManager::RenderEnemy()
{
	GeneralVariables::window_->draw(*current_enemy_);
	current_enemy_->RenderHealthText();
}
