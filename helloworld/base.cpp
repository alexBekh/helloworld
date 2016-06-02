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

		sf::FloatRect locBounds = this->getLocalBounds();

		float halfWidth = locBounds.width / 2;
		float halfHeight = locBounds.height / 2;
		setOrigin(locBounds.left + halfWidth, locBounds.top + halfHeight);

		isCreated = true;
	}

	void TextOnScreen::setPositionOnScreen(Position pos)
	{
		if (!isCreated)
			std::exception("TextOnScreen hasn't been created");

		float halfWidth = getGlobalBounds().width / 2;
		float halfHeight = getGlobalBounds().height / 2;

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

		const float halfWidth = getGlobalBounds().width / 2;
		const float halfHeight = getGlobalBounds().height / 2;
		
		const float relHalfWidth = rel.getGlobalBounds().width / 2;
		const float relHalfHeight = rel.getGlobalBounds().height / 2;

		static const float SPACE = 10.f;
		const float horizOffset = relHalfWidth + halfWidth + SPACE;
		const float vertOffset = relHalfHeight + halfHeight + SPACE;

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