#include "stdafx.h"
#include "Score.h"


Score::Score()
{
}


Score::~Score()
{
}

bool Score::create()
{
	if (!font.loadFromFile(options.fontName))
		return false;

	text.setFont(font);

	setCountString();

	float size;
	float diagonal = std::sqrt(options.gameField.height*options.gameField.height
		+ options.gameField.width * options.gameField.width);

	switch (options.shape.size)
	{
	case Options::Shape::Size::BIG:
		size = diagonal / 10;
		break;
	case Options::Shape::Size::MIDDLE:
		size = diagonal / 20;
		break;
	case Options::Shape::Size::LITTLE:
		size = diagonal / 30;
		break;
	}

	text.setCharacterSize(size);
	text.setOrigin(text.getLocalBounds().width / 2, 0);
	text.setPosition(options.gameField.left + options.gameField.width / 2,
		options.gameField.top);

	std::cout << "Score size=" << size << std::endl;
	return true;
}

void Score::update()
{
	setCountString();
}

void Score::setCountString()
{
	if (options.p1 == nullptr || options.p2 == nullptr)
		throw std::exception("Score: options.p1 == nullptr || options.p2 == nullptr");

	std::stringstream ss;
	ss << options.p1->options.name
		<< '\t'
		<< options.p2->missCount << " : " << options.p1->missCount
		<< '\t' << options.p2->options.name;
	text.setString(ss.str());
}

void Score::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}
