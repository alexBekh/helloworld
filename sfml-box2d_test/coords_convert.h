#pragma once
#include<SFML/Graphics.hpp>
#include<Box2D/Box2D.h>


inline sf::Vector2f box2dToSfml(const b2Vec2& _v, const sf::Vector2f& _center)
{
	return sf::Vector2f(_center.x + _v.x, _center.y - _v.y);
}

inline b2Vec2 sfmlToBox2d(const sf::Vector2f& _v, const sf::Vector2f& _center)
{
	return b2Vec2(_v.x - _center.x, _center.y - _v.y);
}

inline b2Vec2 mapPixelToBox2dCoords(
	const sf::Vector2i& _pos, 
	const sf::Vector2f& _center, 
	const sf::RenderTarget* _window)
{
	sf::Vector2f sfPos = _window->mapPixelToCoords(_pos);
	return sfmlToBox2d(sfPos, _center);
}

inline sf::Color box2dToSfml(const b2Color& _c)
{
	return sf::Color(_c.r * 255, _c.g * 255, _c.b * 255, _c.a * 255);
}

class Convert
{
public:
	static void create(const sf::RenderTarget& rt, sf::Vector2f& center)
	{
		instanse.reset(new Convert);
		instanse->window = &rt;
		instanse->center = center;
	}
	static Convert* get() {
		assert((bool)instanse);
		return instanse.get(); 
	}
	b2Vec2 sf2box(const sf::Vector2f& v) const
	{
		return sfmlToBox2d(v, center);
	}
	sf::Vector2f box2sf(const b2Vec2& v) const
	{
		return box2dToSfml(v, center);
	}
	b2Vec2 pixelToBox2d(const sf::Vector2i& p) const
	{
		return mapPixelToBox2dCoords(p, center, window);
	}
private:
	explicit Convert(){}
	explicit Convert(const Convert&);
	Convert& operator=(const Convert&);

	static std::shared_ptr<Convert> instanse;
	const sf::RenderTarget* window = nullptr;
	sf::Vector2f center;
};