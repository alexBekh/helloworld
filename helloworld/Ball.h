#pragma once
#include "F:\coding\SFML-2.3.2\include\SFML\Graphics\Transformable.hpp"
#include "Options.h"


class Ball :
	public sf::Drawable,
	public sf::Transformable
{
public:
	Ball();
	~Ball();

	void create();
	void start();
	void update();

	bool tryBottom();

	bool tryTop();

	bool tryLeft(const sf::FloatRect& leftRacket);
	bool tryRight(const sf::FloatRect& rightRacket);
	bool tryDeadZone(const sf::FloatRect &racket);
	bool isMissedLeft();
	bool isMissedRight();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	sf::CircleShape ballShape;
	sf::Vector2f velocity;
	Options options;
	float speed;
	sf::Clock clock;
	sf::FloatRect bounds;
};

