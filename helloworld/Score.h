#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"


class Score :
	public sf::Drawable
{
public:
	Score();
	~Score();
	void create();
	void update();
	void updateCountString();

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	std::string makeCountString() const;
public:
	TextOnScreen text;
	
	struct Options: TextOnScreen::Options
	{
		const Player *p1, *p2;
	}
	options;
};

