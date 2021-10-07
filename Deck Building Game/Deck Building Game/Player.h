#pragma once
#include <vector>
#include <algorithm>

#include "Character.h"
#include "Cards.h"
#include "Input.h"

class Player : public Character
{
public:
	Player();
	~Player();
	void DrawCards();
	void DrawHand();
	void DiscardCardsFromBack(unsigned int num_discard_cards);
	void DiscardHand();
	void DiscardCard(int index);
	float Turn(float dt);
	void EndTurn();
	void Render();

	void SetPositionOfCards();

private:
	float ResetAndReturnDamage();
	void LoadCards();
	void AddCardToHand(Cards* card);

	unsigned int start_turn_draw_num_ = 5;
	unsigned int num_draw_cards_ = 0;
	const unsigned int MAX_HAND_SIZE_ = 10;

	std::vector<Cards> Cards_;

	std::vector<Cards*> Hand_;
	std::vector<Cards*> Draw_Pile_;
	std::vector<Cards*> Discard_Pile_;

	float damage = 0;
	uint16_t num_blank_played = 0;

};

