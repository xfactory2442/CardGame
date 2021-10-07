#pragma once
#include <SFML/Graphics.hpp>

class Cards : public sf::RectangleShape
{
public:
	Cards(std::string texture, uint32_t attack, uint32_t defence);
	Cards(const sf::Texture* texture, uint32_t attack, uint32_t defence);
	~Cards();
	bool Collision(sf::Vector2f mouse_position);
	void MoveCard(sf::Vector2f card_position);
	uint32_t GetAttack();
	uint32_t GetDefence();

	sf::Texture* GetStoredTexture();

private:
	void SetUp(const sf::Texture* texture, uint32_t attack, uint32_t defence);
	sf::FloatRect hitbox_;
	sf::Texture texture_;
	uint32_t attack_ = 0;
	uint32_t defence_ = 0;
};

