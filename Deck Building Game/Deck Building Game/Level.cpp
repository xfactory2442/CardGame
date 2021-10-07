#include "Level.h"
#include "GeneralVariables.h"


Level::Level()
{
	/* initialize random seed: */
	srand(time(NULL));

	enemy_manager_ = new EnemyManager();

	player_.DrawHand();
}


Level::~Level()
{
}

bool Level::Update(float dt)
{
	//If players turn.
	if (turn_) {
		enemy_manager_->AttackEnemy(player_.Turn(dt));
		if (GeneralVariables::input_->isKeyDown(sf::Keyboard::R)) {
			GeneralVariables::input_->setKeyUp(sf::Keyboard::R);
			player_.EndTurn();
			turn_ = !turn_;
		}
	}
	else {
		turn_ = !turn_;
		if (player_.ChangeHealth(enemy_manager_->EnemyTurn(dt))) {
			return false;
		}
		player_.ResetDefence();
	}
	return true;
}

void Level::Render()
{
	Begin_Draw();
	player_.Render();
	enemy_manager_->RenderEnemy();
	End_Draw();
}

void Level::Begin_Draw()
{
	GeneralVariables::window_->clear(sf::Color::Black);
}

void Level::End_Draw()
{
	GeneralVariables::window_->display();
}
