#include "stdafx.h"
#include "Ball.h"


namespace base 
{
	void TextOnScreen::create(const std::string& text, Size size)
	{
		setFont(options.font);
		setString(text);
		setSize(size);
		setColor(options.shape.color);

		float halfWidth = getLocalBounds().width / 2;
		float halfHeight = getLocalBounds().height / 2;
		setOrigin(halfWidth, halfHeight);

		isCreated = true;
	}

	void TextOnScreen::setPositionOnScreen(Position pos)
	{
		if (!isCreated)
			std::exception("TextOnScreen hasn't been created");

		float halfWidth = getLocalBounds().width / 2;
		float halfHeight = getLocalBounds().height / 2;

		sf::Vector2f center;

		Position vertical = pos & Position::VERT;
		switch (vertical)
		{
		case Position::TOP:
			center.y = options.gameField.top + halfHeight;
			break;
		case Position::CENTER:
			center.y = options.gameField.top + options.gameField.height / 2;
			break;
		case Position::BOTTOM:
			center.y = options.gameField.top + options.gameField.height - halfHeight;
			break;
		default:
			break;
		}
		
		Position horizontal = pos & Position::HORIZ;
		switch (horizontal)
		{
		case Position::LEFT:
			center.x = options.gameField.left + halfWidth;
			break;
		case Position::CENTER:
			center.x = options.gameField.left + options.gameField.width / 2;
			break;
		case Position::RIGHT:
			center.x = options.gameField.left + options.gameField.width - halfWidth;
			break;
		default:
			break;
		}
		
		sf::Text::setPosition(center);
	}

	void TextOnScreen::setPositionOnScreen(RelativePosition pos, const TextOnScreen& rel)
	{
		if (!isCreated)
			std::exception("TextOnScreen hasn't been created");

		const float halfWidth = getLocalBounds().width / 2;
		const float halfHeight = getLocalBounds().height / 2;
		
		const float relHalfWidth = rel.getLocalBounds().width / 2;
		const float relHalfHeight = rel.getLocalBounds().height / 2;

		const float horizOffset = relHalfWidth + halfWidth;
		const float vertOffset = relHalfHeight + halfHeight;

		sf::Vector2f center = rel.getPosition();

		RelativePosition relativeVertival = pos & RelativePosition::REL_VERT;
		switch (relativeVertival)
		{
		case RelativePosition::ABOVE:
			center.y -= vertOffset;
			break;
		case RelativePosition::UNDER:
			center.y += vertOffset;
			break;
		default:
			break;
		}

		RelativePosition relativeHoriz = pos & RelativePosition::REL_HORIZ;
		switch (relativeHoriz)
		{
		case RelativePosition::LEFT_OF:
			center.x -= horizOffset;
			break;
		case RelativePosition::RIGHT_OF:
			center.x += horizOffset;
			break;
		default:
			break;
		}

		if (!options.gameField.contains(center))
		{
			throw std::exception("Position error: out of game field");
		}
		sf::Text::setPosition(center);
	}

	void TextOnScreen::setSize(Size size)
	{
		float diagonal = std::sqrt(
			options.gameField.height * options.gameField.height +
			options.gameField.width * options.gameField.width);

		float charSize;

		switch (size)
		{
		case Size::BIG:
			charSize = diagonal / 10;
			break;
		case Size::MIDDLE:
			charSize = diagonal / 20;
			break;
		case Size::LITTLE:
			charSize = diagonal / 30;
			break;
		}
		sf::Text::setCharacterSize(charSize);
	}

} // namespace base 