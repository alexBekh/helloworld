#pragma once
#include <SFML\Graphics.hpp>
#include "base.h"

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

	struct Options: base::PlayableOptions
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

