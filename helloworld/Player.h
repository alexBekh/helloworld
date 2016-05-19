#pragma once
#include "F:\coding\SFML-2.3.2\include\SFML\Graphics\Drawable.hpp"
#include "Options.h"

class Player :
	public sf::Drawable
{
public:
	Player();
	~Player();
	void createRacket();
	void update();
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	sf::RectangleShape  racket;
	int missCount = 0;
	float speed;

	struct Options: options::Options
	{
		enum class Side {LEFT, RIGHT} side = Side::LEFT;

		struct Controls
		{
			sf::Keyboard::Key 
					up = sf::Keyboard::Up
				, down = sf::Keyboard::Down;
		} 
		controls;

		std::string name = "Player";
	} 
	options;
};

