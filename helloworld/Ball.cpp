#include "stdafx.h"
#include "Ball.h"


Ball::Ball()
{
}


Ball::~Ball()
{
}

void Ball::create()
{
	float radius;
	float diagonal = std::sqrtf(options.gameField.height*options.gameField.height
		+ options.gameField.width*options.gameField.width);

	switch (options.shape.size)
	{
	case Options::Shape::Size::BIG:
		radius = diagonal / 25;
		break;
	case Options::Shape::Size::MIDDLE:
		radius = diagonal / 50;
		break;
	case Options::Shape::Size::LITTLE:
		radius = diagonal / 75;
		break;
	}

	ballShape.setRadius(radius);
	ballShape.setOrigin(radius, radius);
	ballShape.setFillColor(options.shape.color);

	const float ratio = diagonal / radius;

	switch (options.speed)
	{
	case Options::Speed::SLOW:
		speed = ratio * 2.5;
		break;
	case Options::Speed::NORMAL:
		speed = ratio * 5;
		break;
	case Options::Speed::FAST:
		speed = ratio * 10;
		break;
	}
	std::cout << "ball speed=" << speed << std::endl;
}

void Ball::start()
{
	std::srand(std::time(0));
	float angle = (std::rand() % 120 - 60) * 3.14 / 180;
	velocity.x = std::cos(angle);
	velocity.y = std::sin(angle);

	if (std::rand() % 2)
		velocity.x = -velocity.x;

	ballShape.setPosition(options.gameField.left + options.gameField.width / 2,
		options.gameField.top + options.gameField.height / 2);

	clock.restart();
}

void Ball::update()
{
	ballShape.move(velocity * speed * clock.restart().asSeconds());

	if(!tryTop())
		tryBottom();
}

bool Ball::tryBottom()
{
	if (ballShape.getGlobalBounds().top + ballShape.getGlobalBounds().height >
		options.gameField.top + options.gameField.height)
	{
		float yReturn = options.gameField.top + options.gameField.height - ballShape.getRadius();
		float yDelta = ballShape.getPosition().y - options.gameField.top - options.gameField.height;
		ballShape.setPosition(ballShape.getPosition().x, yReturn + yDelta);
		velocity.y = -velocity.y;
		return true;
	}
	return false;
}

bool Ball::tryTop()
{
	if (ballShape.getGlobalBounds().top < options.gameField.top)
	{
		float yReturn = options.gameField.top + ballShape.getRadius();
		float yDelta = ballShape.getPosition().y - options.gameField.top;
		ballShape.setPosition(ballShape.getPosition().x, yReturn + yDelta);
		velocity.y = -velocity.y;

		return true;
	}
	return false;
}

bool Ball::tryLeft(const sf::FloatRect& leftRacket)
{

	if (leftRacket.intersects(ballShape.getGlobalBounds()))
	{
		if (!tryDeadZone(leftRacket))
		{
			velocity.x = -velocity.x;
			ballShape.setPosition(leftRacket.left + leftRacket.width + ballShape.getRadius(), 
				ballShape.getPosition().y);
			velocity.y += std::sin((std::rand() % 120)*3.14 / 180);
			velocity.x += std::cos((std::rand() % 120)*3.14 / 180);
			return true;
		}
	}
	return false;
}

bool Ball::tryDeadZone(const sf::FloatRect &racket)
{
	float yRelativePos = racket.top + racket.height - ballShape.getPosition().y;
	if (yRelativePos < 0 || yRelativePos > racket.height)
	{
		float yReturn = ballShape.getPosition().y < racket.top ?
			racket.top - ballShape.getRadius() :
			racket.top + racket.height + ballShape.getRadius();

		float yDelta = ballShape.getPosition().y < racket.top ?
			ballShape.getPosition().y - racket.top :
			racket.top + racket.height - ballShape.getPosition().y;

		ballShape.setPosition(ballShape.getPosition().x, yReturn + yDelta);
		velocity.y = -velocity.y;

		return true;
	}
	return false;
}

bool Ball::isMissedLeft()
{
	if (ballShape.getGlobalBounds().left < options.gameField.left)
		return true;

	return false;
}

bool Ball::tryRight(const sf::FloatRect& rightRacket)
{
	if (rightRacket.intersects(ballShape.getGlobalBounds()))
	{
		if (!tryDeadZone(rightRacket))
		{
			velocity.x = -velocity.x;
			ballShape.setPosition(rightRacket.left - ballShape.getRadius(), ballShape.getPosition().y);
			return true;
		}
	}
	return false;
}

bool Ball::isMissedRight()
{
	const float ballRightBound = ballShape.getGlobalBounds().left + ballShape.getGlobalBounds().width;
	const float gameFieldRightBound = options.gameField.left + options.gameField.width;

	if (ballRightBound > gameFieldRightBound)
		return true;

	return false;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = nullptr;
	target.draw(ballShape, states);
}
