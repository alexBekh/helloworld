#pragma once
#include <SFML\Graphics.hpp>
#include "base.h"


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
	void tryUpDown();
	bool tryLeft(const sf::FloatRect& leftRacket);

	//void reflect(float x, float y);
	void reflectX(float x);
	void reflectY(float y);

	bool tryRight(const sf::FloatRect& rightRacket);
	bool tryDeadZone(const sf::FloatRect &racket);
	bool isMissedLeft();
	bool isMissedRight();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	sf::CircleShape ballShape;
	sf::Vector2f velocity;
	PlayableOptions options;
	float speed;
	sf::Clock clock;
	sf::FloatRect bounds;
};

