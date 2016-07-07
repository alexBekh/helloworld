#pragma once
#include"stdafx.h"
#include"FindFixtureByPosQuery.h"


class MouseJoint : public sf::Drawable
{
public:
	MouseJoint(const RenderTarget* _rt, const Vector2f _center, b2World* _w, b2Body* _ground)
		: window(_rt), center(_center), world(_w), ground(_ground)
	{
		assert(_rt != nullptr);
		assert(_w != nullptr);
		assert(_ground != nullptr);
	}

	void update(const Event& _e)
	{
		if (_e.type == Event::MouseButtonPressed 
			&& _e.mouseButton.button == Mouse::Button::Left 
			&& !mj)
		{
			const Vector2i mpos = { _e.mouseButton.x, _e.mouseButton.y };

			b2Vec2 p = mapPixelToBox2dCoords(mpos, center, window);

			FindFixtureByPosQuery callback(p);
			world->QueryAABB(&callback, callback.getAABB());

			if (callback.isFound())
			{
				b2Body* body = callback.getFixture()->GetBody();
				b2MouseJointDef mjd;
				mjd.bodyA = ground;
				mjd.bodyB = body;
				mjd.maxForce = 100.f * body->GetMass();
				mjd.target = p;
				mjd.collideConnected = true;
				mj = static_cast<b2MouseJoint*>(world->CreateJoint(&mjd));
				body->SetAwake(true);
			}
		}
		else if (_e.type == Event::MouseMoved && mj)
		{
			const Vector2i mpos = { _e.mouseMove.x, _e.mouseMove.y };

			b2Vec2 p = mapPixelToBox2dCoords(mpos, center, window);

			mj->SetTarget(p);
		}
		else if (_e.type == Event::MouseButtonReleased 
			&& _e.mouseButton.button == Mouse::Button::Left 
			&& mj)
		{
			world->DestroyJoint(mj);
			mj = nullptr;
		}
	}

protected:
	virtual void draw(RenderTarget& target, RenderStates states) const override
	{
		assert(&target == window);

		if (!mj)
			return;

		static const float radius = 0.5;
		static const int pcount = 8;
		sf::CircleShape p1(radius, pcount), p2;
		p1.setOrigin(radius, radius);
		p1.setFillColor(Color::Green);
		p2 = p1;
		Vector2f pos1 = box2dToSfml(mj->GetAnchorB(), center);
		Vector2f pos2 = box2dToSfml(mj->GetTarget(), center);
		p1.setPosition(pos1);
		p2.setPosition(pos2);

		VertexArray line;
		line.setPrimitiveType(PrimitiveType::Lines);
		line.append(pos1);
		line.append(pos2);

		target.draw(p1,states);
		target.draw(p2,states);
		target.draw(line, states);
	}

private:
	b2MouseJoint* mj;
	Vector2f center;
	const RenderTarget* window;
	b2World* world;
	b2Body* ground;
};