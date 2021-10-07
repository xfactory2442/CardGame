#include "Cards.h"

Cards::Cards(std::string texture, uint32_t attack, uint32_t defence)
{
	texture_.loadFromFile(texture);
	SetUp(&texture_, attack, defence);
}

Cards::Cards(const sf::Texture* texture, uint32_t attack, uint32_t defence)
{
	SetUp(texture, attack, defence);
}


Cards::~Cards()
{
}

bool Cards::Collision(sf::Vector2f mouse_position)
{
	if (hitbox_.contains(mouse_position)) {
		return true;
	}
	return false;
}

void Cards::MoveCard(sf::Vector2f card_position)
{
	setPosition(card_position);
	hitbox_.left = card_position.x;
	hitbox_.top = card_position.y;
}

uint32_t Cards::GetAttack()
{
	return attack_;
}

uint32_t Cards::GetDefence()
{
	return defence_;
}

sf::Texture* Cards::GetStoredTexture()
{
	return &texture_;
}

void Cards::SetUp(const sf::Texture* texture, uint32_t attack, uint32_t defence)
{
	setSize(sf::Vector2f(150, 200));
	setPosition(400, 500);

	setTexture(texture);
	attack_ = attack;
	defence_ = defence;

	hitbox_.left = getPosition().x;
	hitbox_.top = getPosition().y;
	hitbox_.width = getSize().x;
	hitbox_.height = getSize().y;
}
