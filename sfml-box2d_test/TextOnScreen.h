#pragma once
#include "stdafx.h"


namespace base {

	enum class Size { LITTLE, MIDDLE, BIG, FIT };

	enum class Speed { SLOW, NORMAL, FAST };

	enum class Position : unsigned int {
		CENTER = 0,
		TOP = 1,
		BOTTOM = 1 << 1,
		LEFT = 1 << 2,
		RIGHT = 1 << 3,
		VERT = TOP | BOTTOM,
		HORIZ = LEFT | RIGHT
	};

	enum class RelativePosition : unsigned int {
		ABOVE = 1,
		UNDER = 1 << 1,
		LEFT_OF = 1 << 2,
		RIGHT_OF = 1 << 3,
		REL_VERT = ABOVE | UNDER,
		REL_HORIZ = LEFT_OF | RIGHT_OF
	};

	inline Position operator|(const Position lvalue, const Position rvalue)
	{
		return static_cast<Position>(static_cast<unsigned int>(lvalue) | static_cast<unsigned int>(rvalue));
	}
	inline Position operator^(const Position lvalue, const Position rvalue)
	{
		return static_cast<Position>(static_cast<unsigned int>(lvalue) ^ static_cast<unsigned int>(rvalue));
	}
	inline Position operator&(const Position lvalue, const Position rvalue)
	{
		return static_cast<Position>(static_cast<unsigned int>(lvalue) & static_cast<unsigned int>(rvalue));
	}
	inline RelativePosition operator|(const RelativePosition lvalue, const RelativePosition rvalue)
	{
		return static_cast<RelativePosition>(static_cast<unsigned int>(lvalue) | static_cast<unsigned int>(rvalue));
	}
	inline RelativePosition operator^(const RelativePosition lvalue, const RelativePosition rvalue)
	{
		return static_cast<RelativePosition>(static_cast<unsigned int>(lvalue) ^ static_cast<unsigned int>(rvalue));
	}
	inline RelativePosition operator&(const RelativePosition lvalue, const RelativePosition rvalue)
	{
		return static_cast<RelativePosition>(static_cast<unsigned int>(lvalue) & static_cast<unsigned int>(rvalue));
	}


	struct Options
	{
		struct Shape
		{
			sf::Color color = sf::Color::White;
			Size size = Size::MIDDLE;
		}
		shape;

		sf::FloatRect gameField;
	};

	class TextOnScreen : public sf::Text
	{
	public:
		void create(const std::string& text, Size size);
		void setPositionOnScreen(Position pos);
		void setPositionOnScreen(RelativePosition pos, const TextOnScreen& rel);
		bool loadFont(const char* _fontname);
	private:
		void setSize(Size size);

	public:
		struct Options : base::Options
		{
			sf::Font font;

			void operator=(const base::Options& rvalue)
			{
				*static_cast<base::Options*>(this) = rvalue;
			}
		}
		options;

	private:
		bool isCreated = false;
		float fitableSize = 0.f;
	};

} // namespace options
