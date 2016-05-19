#pragma once
#include <SFML/Graphics.hpp>

namespace options {

	struct Options
	{
		struct Shape
		{
			sf::Color color = sf::Color::White;
			enum class Size { LITTLE, MIDDLE, BIG } size = Size::MIDDLE;
		}
		shape;

		enum class Speed { SLOW, NORMAL, FAST } speed = Speed::SLOW;
		//float speed = 0.3;

		sf::FloatRect gameField;

		sf::Sound sound;
	};

} // namespace options
