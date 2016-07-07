#pragma once
#include "stdafx.h"





class DebugDraw : public b2Draw, public Drawable
{

public:
	DebugDraw(const sf::Vector2f _center)
	{
		center = _center;
	}

	DebugDraw(const sf::FloatRect& _field)
	{
		setField(_field);
	}

	void clear()
	{
		this->drawables.clear();
	}

	void setField(const sf::FloatRect& _f) 
	{
		field = _f;

		center.x = field.left + field.width / 2;
		center.y = field.top + field.height / 2;
	}

	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
	{
		auto polygon = std::make_shared<sf::VertexArray>();

		for (int i = 0; i < vertexCount; i++)
		{
			sf::Vertex v;
			v.position = box2dToSfml(vertices[i]);
			v.color = ::box2dToSfml(color);
			polygon->append(v);
		}
		polygon->setPrimitiveType(sf::PrimitiveType::LinesStrip);

		this->drawables.push_back(polygon);
	}


	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) override
	{
		auto solidPolygon = std::make_shared<ConvexShape>(vertexCount);

		for (int i = 0; i < vertexCount; i++)
		{
			solidPolygon->setPoint(i, box2dToSfml(vertices[i]));
		}
		solidPolygon->setFillColor(::box2dToSfml(color));

		this->drawables.push_back(solidPolygon);
	}


	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) override
	{
		auto circle = std::make_shared<sf::CircleShape>(radius);
		circle->setOrigin(radius, radius);
		circle->setPosition(box2dToSfml(center));
		circle->setFillColor(sf::Color::Transparent);
		circle->setOutlineColor(::box2dToSfml(color));
		circle->setOutlineThickness(-1);

		this->drawables.push_back(circle);
	}


	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) override
	{
		auto solidCircle = std::make_shared<sf::CircleShape>(radius);
		solidCircle->setFillColor(::box2dToSfml(color));
		solidCircle->setOrigin(radius, radius);
		solidCircle->setPosition(box2dToSfml(center));

		this->drawables.push_back(solidCircle);

		auto r = std::make_shared<sf::VertexArray>();
		r->setPrimitiveType(PrimitiveType::Lines);
		r->append(Vertex(solidCircle->getPosition()));
		r->append(Vertex(box2dToSfml(center + radius * axis)));

		this->drawables.push_back(r);
	}


	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) override
	{
		sf::Vertex
			v1(box2dToSfml(p1), ::box2dToSfml(color)),
			v2(box2dToSfml(p2), ::box2dToSfml(color));

		auto line = std::make_shared<sf::VertexArray>();
		line->append(v1);
		line->append(v2);
		line->setPrimitiveType(sf::PrimitiveType::Lines);

		this->drawables.push_back(line);
	}


	virtual void DrawTransform(const b2Transform& xf) override
	{
		const float32 k_axisScale = 0.4f;
		b2Vec2 p1 = xf.p, p2;

		Vertex v1(box2dToSfml(p1), sf::Color::Red);
		p2 = p1 + k_axisScale * xf.q.GetXAxis();
		Vertex v2(box2dToSfml(p2), sf::Color::Red);

		Vertex v3(box2dToSfml(p1), sf::Color::Green);
		p2 = p1 + k_axisScale * xf.q.GetYAxis();
		Vertex v4(box2dToSfml(p2), sf::Color::Green);

		auto transform = std::make_shared<sf::VertexArray>();
		transform->append(v1);
		transform->append(v2);
		transform->append(v3);
		transform->append(v4);
		transform->setPrimitiveType(sf::PrimitiveType::Lines);

		this->drawables.push_back(transform);
	}


	virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) override
	{
		auto vertex = std::make_shared<VertexArray>(sf::PrimitiveType::Points);
		vertex->append(sf::Vertex(box2dToSfml(p), ::box2dToSfml(color)));

		this->drawables.push_back(vertex);
	}

protected:
	virtual void draw(RenderTarget& target, RenderStates states) const override
	{
		for each (auto i in drawables)
			target.draw(*i, states);
	}

private:
	sf::Vector2f box2dToSfml(const b2Vec2& _v)
	{
		return ::box2dToSfml(_v, center);
	}

private:
	std::vector<std::shared_ptr<Drawable>> drawables;
	Vector2f center;
	sf::FloatRect field;
};