#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"


class Score :
	public sf::Drawable
{
public:
	Score();
	~Score();
	bool loadFont();
	void create();
	void update();
	void setCountString();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

public:
	sf::Font font;
	sf::Text text;
	
	struct Options: base::PlayableOptions
	{
		std::string fontName;
		const Player *p1, *p2;
	}
	options;
};

