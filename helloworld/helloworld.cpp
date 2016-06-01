// helloworld.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Player.h"
#include "Ball.h"
#include "Score.h"
#include "Game.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(600,400), "thePong", sf::Style::Default^sf::Style::Resize);
	
	Game game;
	if (!game.loadResources())
		return 1;

	Options options;
	options.gameField = sf::FloatRect(10, 10, window.getSize().x - 20.f, window.getSize().y - 20.f);
	game.setOptions(options);

	game.create();
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			else
			{
				game.setEvent(event);
			}
		}

		game.update();

		window.clear(sf::Color::Black);
		window.draw(game);
		window.display();
	}
    return 0;
}

