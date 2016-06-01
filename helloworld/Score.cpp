#include "stdafx.h"
#include "Score.h"


Score::Score()
{
}


Score::~Score()
{
}

void Score::create()
{
	text.options = options;
	text.create(makeCountString(), Size::LITTLE);
	text.setPositionOnScreen(Position::TOP);
}

void Score::update()
{
	updateCountString();
}

void Score::updateCountString()
{
	text.setString(makeCountString());
}

std::string Score::makeCountString() const
{
	if (options.p1 == nullptr || options.p2 == nullptr)
		throw std::exception("Score: options.p1 == nullptr || options.p2 == nullptr");

	std::stringstream ss;
	ss << options.p1->options.name
		<< '\t'
		<< options.p2->missCount << " : " << options.p1->missCount
		<< '\t' << options.p2->options.name;
	
	return ss.str();
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}