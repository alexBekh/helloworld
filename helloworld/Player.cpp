#include "stdafx.h"
#include "Player.h"
#include <iostream>


Player::Player()
{
}


Player::~Player()
{
}

void Player::createRacket()
{
	sf::Vector2f size(options.gameField.width / 100, 0);

	switch (options.shape.size)
	{
	case Size::BIG:
		size.y = options.gameField.height / 2;
		break;
	case Size::MIDDLE:
		size.y = options.gameField.height / 3;
		break;
	case Size::LITTLE:
		size.y = options.gameField.height / 4;
		break;
	}
	racket.setSize(size);
	
	sf::Vector2f pos(0, options.gameField.top + options.gameField.height / 2);

	switch (options.side)
	{
	case Options::Side::LEFT:
		pos.x = options.gameField.left;
		break;
	case Options::Side::RIGHT:
		pos.x = options.gameField.left + options.gameField.width - racket.getSize().x;
			break;
	}
	racket.setPosition(pos);

	const float ratio = options.gameField.height / size.y;

	switch (options.speed)
	{
	case Speed::SLOW:
		speed = ratio * 0.1f;
		break;
	case Speed::NORMAL:
		speed = ratio * 0.25f;
		break;
	case Speed::FAST:
		speed = ratio * 0.5f;
		break;
	}
	std::cout << options.name <<" speed=" << speed << std::endl;
}

void Player::update()
{
	if (sf::Keyboard::isKeyPressed(options.controls.up) 
		&& sf::Keyboard::isKeyPressed(options.controls.down))
	{
		// нефиг жать на все кнопки сразу!!
	}
	else if (sf::Keyboard::isKeyPressed(options.controls.up))
	{
		racket.move(0, -speed);
		if (racket.getGlobalBounds().top < options.gameField.top)
			racket.setPosition(racket.getPosition().x, options.gameField.top);
	}
	else if (sf::Keyboard::isKeyPressed(options.controls.down))
	{
		racket.move(0, speed);
		float racketBottom = racket.getGlobalBounds().top + racket.getGlobalBounds().height;
		float gameFieldBottom = options.gameField.top + options.gameField.height;

		if (racketBottom > gameFieldBottom)
		{
			racket.setPosition(racket.getPosition().x,
				gameFieldBottom - racket.getGlobalBounds().height);
		}
	}
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = nullptr;
	target.draw(this->racket, states);
}
