#pragma once
#include "F:\coding\SFML-2.3.2\include\SFML\Graphics\Drawable.hpp"
#include "Player.h"


class Score :
	public sf::Drawable
{
public:
	Score();
	~Score();
	bool create();
	void update();
	void setCountString();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	sf::Font font;
	sf::Text text;
	
	struct Options: options::Options
	{
		std::string fontName;
		const Player *p1, *p2;
	}
	options;
};

