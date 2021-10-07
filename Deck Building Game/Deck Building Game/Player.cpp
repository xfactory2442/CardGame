#include "Player.h"
#include <iostream>
#include "GeneralVariables.h"
#include <fstream>
#include <sstream> // std::stringstream
#include <string>

Player::Player() 
	: Character(20.0f, "Player", nullptr)
{
	health_text_.setPosition(20.0f, 550.0f);
	health_text_.setCharacterSize(25);
	defence_text_.setPosition(500.0f, 550.0f);
	defence_text_.setCharacterSize(25);

	LoadCards();

	//Initialise the card types.
	for (int i = 0; i < 5; i++) {
		AddCardToHand(&Cards_[1]);
		AddCardToHand(&Cards_[2]);
		for (int j = 0; j < 4; j++) {
			AddCardToHand(&Cards_[0]);
		}
	}

	std::random_shuffle(Draw_Pile_.begin(), Draw_Pile_.end());
}


Player::~Player()
{
}

void Player::DrawCards()
{
	for (size_t i = 0; i < num_draw_cards_; i++) {
		if (Draw_Pile_.empty()) {
			Draw_Pile_ = Discard_Pile_;
			Discard_Pile_.clear();
			std::random_shuffle(Draw_Pile_.begin(), Draw_Pile_.end());
		}
		Hand_.push_back(Draw_Pile_[Draw_Pile_.size()-1]);
		Draw_Pile_.pop_back();
	}
	num_draw_cards_ = 0;
	SetPositionOfCards();
}

void Player::DrawHand()
{
	num_draw_cards_ = start_turn_draw_num_;
	DrawCards();
}

void Player::DiscardCardsFromBack(unsigned int num_discard_cards)
{
	for (size_t i = 0; i < num_discard_cards; i++) {
		if (!Hand_.empty()) {
			Discard_Pile_.push_back(Hand_[Hand_.size() - 1]);
			Hand_.pop_back();
		}
	}
	SetPositionOfCards();
}

void Player::DiscardHand()
{
	DiscardCardsFromBack(Hand_.size());
}

void Player::DiscardCard(int index)
{
	Discard_Pile_.push_back(Hand_[index]);
	Hand_.erase(Hand_.begin() + index);
}

float Player::Turn(float dt)
{ 
	if (GeneralVariables::input_->isMouseLeftDown()) {
		for (int i = Hand_.size() - 1; i >= 0; i--) {
			if (Hand_[i]->Collision(
					GeneralVariables::window_->mapPixelToCoords(
						GeneralVariables::input_->getMouse()
				))) {
				GeneralVariables::input_->setMouseLeftDown(false);
				damage = Hand_[i]->GetAttack();
				AddDefence(Hand_[i]->GetDefence());
				if (damage == 0 && Hand_[i]->GetDefence() == 0) {
					num_blank_played++;
					if (num_blank_played >= 10) {
						num_blank_played = 0;
						ChangeHealth(1.0f);
					}
				}
				DiscardCard(i);
				return ResetAndReturnDamage();
			}
		}
	}
	return ResetAndReturnDamage();
}

void Player::EndTurn()
{
	DiscardHand();
	DrawHand();
}

void Player::Render()
{
	for (int i = 0; i < Hand_.size(); i++) {
		GeneralVariables::window_->draw(*Hand_[i]);
	}
	RenderHealthText();
	RenderDefenceText();
}

void Player::SetPositionOfCards()
{
	for (int i = 0; i < Hand_.size(); i++) {
		float x = 55.0f + (600.0f / Hand_.size()) * i;
		Hand_[i]->MoveCard(sf::Vector2f(x, 600.f));
	}
}

float Player::ResetAndReturnDamage()
{
	float new_damage = damage;
	damage = 0;
	return -new_damage;
}

void Player::LoadCards()
{
	// File pointer
	std::ifstream fin;

	// Open an existing file
	fin.open("csv/cards.csv");

	// Read the Data from the file
	// as String Vector
	std::vector<std::string> row;
	std::string line, word, temp;

	while (getline(fin, line)) {

		row.clear();

		// used for breaking words
		std::stringstream ss(line);

		// read every column data of a row and
		// store it in a string variable, 'word'
		while (std::getline(ss, word, ',')) {
			// add all the column data
			// of a row to a vector
			row.push_back(word);
		}

		Cards_.push_back(Cards("gfx/" + row[0], std::stoi(row[1]), std::stoi(row[2])));
	}

	fin.close();
}

void Player::AddCardToHand(Cards* card)
{
	Draw_Pile_.push_back(new Cards(card->GetStoredTexture(), card->GetAttack(), card->GetDefence()));
}
