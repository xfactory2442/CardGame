#include "SFML/Graphics.hpp"

#include "ScreenManager.h"
#include "Input.h"
#include "GeneralVariables.h"

#include "Level.h"

//Initalise GeneralVariables static variables.
sf::Font GeneralVariables::font_;
sf::RenderWindow* GeneralVariables::window_;
Input* GeneralVariables::input_;
ScreenManager* GeneralVariables::screen_manager_;

void main()
{
	// Create window
	sf::Vector2u window_size(800, 800);
	GeneralVariables::window_ = new sf::RenderWindow(sf::VideoMode(window_size.x, window_size.y), "Deck Building Game");
	
	//Initialise General Variables.
	GeneralVariables::font_.loadFromFile("fonts/consola.ttf");
	GeneralVariables::input_ = new Input();
	GeneralVariables::screen_manager_ = new ScreenManager();

	//Initialise Clock Object.
	sf::Clock clock;

	//Initialise Screens.
	Level level;

	// Game Loop
	while (GeneralVariables::window_->isOpen())
	{
		sf::Event event;
		while (GeneralVariables::window_->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				GeneralVariables::window_->close();
				break;
			case sf::Event::Resized:
				GeneralVariables::window_->setSize(window_size);
				GeneralVariables::window_->setView(sf::View(sf::FloatRect(0.f, 0.f,
					(float)event.size.width, (float)event.size.height)));
				break;
			case sf::Event::KeyPressed:
				// update input class
				GeneralVariables::input_->setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				GeneralVariables::input_->setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				GeneralVariables::input_->setMousePosition(event.mouseMove.x,
					event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					GeneralVariables::input_->setMouseLeftDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					GeneralVariables::input_->setMouseLeftDown(false);
				}
				break;
			default:
				// don't Hand_le other events
				break;
			}
		}

		float dt = clock.restart().asSeconds();

		switch (GeneralVariables::screen_manager_->getCurrentScreen()) {
		case GeneralVariables::screen_manager_->LEVEL:
			if (!level.Update(dt)) {
				return;
			}
			level.Render();
			break;
		}
	}
}