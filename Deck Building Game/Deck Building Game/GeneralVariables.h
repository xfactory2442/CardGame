#pragma once
#include <SFML/Graphics.hpp>
#include "Input.h"
#include "ScreenManager.h"

class GeneralVariables
{
public:
	static sf::Font font_;
	static sf::RenderWindow* window_;
	static Input* input_;
	static ScreenManager* screen_manager_;
};

