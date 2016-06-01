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
	case Size::BIG:
		radius = diagonal / 25;
		break;
	case Size::MIDDLE:
		radius = diagonal / 50;
		break;
	case Size::LITTLE:
		radius = diagonal / 75;
		break;
	}

	ballShape.setRadius(radius);
	ballShape.setOrigin(radius, radius);
	ballShape.setFillColor(options.shape.color);

	const float ratio = diagonal / radius;

	switch (options.speed)
	{
	case Speed::SLOW:
		speed = ratio * 2.5;
		break;
	case Speed::NORMAL:
		speed = ratio * 5;
		break;
	case Speed::FAST:
		speed = ratio * 10;
		break;
	}

	bounds.top = options.gameField.top + ballShape.getRadius();
	bounds.height = options.gameField.height - 2 * ballShape.getRadius();
	bounds.left = -2 * ballShape.getRadius();
	bounds.width = options.gameField.width + 2 * options.gameField.left + 4 * ballShape.getRadius();

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

	tryUpDown();
}

void Ball::tryUpDown()
{
	float relativePos = bounds.top + bounds.height - ballShape.getPosition().y;
	float returnedPos = 0;
	// ball.pos < bounds.top
	if (relativePos > bounds.height)
	{
		returnedPos = bounds.top + relativePos - bounds.height;
	}
	// ball.pos > bounds.top + bounds.height
	else if (relativePos < 0)
	{
		returnedPos = bounds.top + bounds.height + relativePos;
	}
	if (returnedPos)
	{
		reflectY(returnedPos);
	}
}
bool Ball::tryLeft(const sf::FloatRect& leftRacket)
{

	if (leftRacket.intersects(ballShape.getGlobalBounds()) && !tryDeadZone(leftRacket))
	{
		reflectX(leftRacket.left + leftRacket.width + ballShape.getRadius());
		return true;
	}
	return false;
}

//void Ball::reflect(float x, float y)
//{
//	if (x && y)
//		throw std::exception("Ball::reflect: x!=0 && y!=0. Нельзя отражать одновременно по двум осям");
//	if(!x && !y)
//		throw std::exception("Ball::reflect: x==0 && y==0. Бессмысленный вызов");
//	if(x)
//	{
//		y = ballShape.getPosition().y;
//		velocity.x = -velocity.x;
//
//		float angle = (std::rand() % 30)*3.14 / 180;
//		float sign = std::rand() % 2 ? 1 : -1;
//		velocity.y += sign * std::sin(angle);
//		velocity.x += sign * std::cos(angle);
//	}
//	else
//	{
//		x = ballShape.getPosition().x;
//		velocity.y = -velocity.y;
//	}
//
//	ballShape.setPosition(x, y);
//}

void Ball::reflectX(float x)
{
	velocity.x = -velocity.x;

	if (std::abs(velocity.x) < 0.3 || std::abs(velocity.x) > 0.9 )
	{
		float angle = (std::rand() % 60 - 30)*3.14 / 180;
		float sign = (velocity.x > 0) ? 1 : -1;
		velocity.y = sign * std::sin(angle);
		velocity.x = sign * std::cos(angle);
	}
	ballShape.setPosition(x, ballShape.getPosition().y);
}

void Ball::reflectY(float y)
{
	velocity.y = -velocity.y;
	ballShape.setPosition(ballShape.getPosition().x, y);
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

		reflectY(yReturn + yDelta);
		return true;
	}
	return false;
}

bool Ball::isMissedLeft()
{
	if (ballShape.getPosition().x < bounds.left)
		return true;

	return false;
}

bool Ball::tryRight(const sf::FloatRect& rightRacket)
{
	if (rightRacket.intersects(ballShape.getGlobalBounds()) && !tryDeadZone(rightRacket))
	{
		reflectX(rightRacket.left - ballShape.getRadius());
		return true;
	}
	return false;
}

bool Ball::isMissedRight()
{
	if (ballShape.getPosition().x > bounds.left + bounds.width)
		return true;

	return false;
}

void Ball::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = nullptr;
	target.draw(ballShape, states);
}
