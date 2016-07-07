#pragma once
#include "stdafx.h"
#include "DebugDraw.h"
#include "MouseJoint.h"


void test2()
{
	RenderWindow window(VideoMode(800, 600), "sfml+box2d test2");

	b2World world(b2Vec2(0, -10));

	b2BodyDef groundDef;
	b2Body* ground = world.CreateBody(&groundDef);
	b2Vec2 v[4];
	v[0] = b2Vec2(-300, 200);
	v[1] = b2Vec2(-300, -200);
	v[2] = b2Vec2(300, -200);
	v[3] = b2Vec2(300, 200);
	b2ChainShape gameField;
	gameField.CreateLoop(v, 4);
	ground->CreateFixture(&gameField, 0);

	float32 timeStep = 1 / 60.f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	window.setFramerateLimit(timeStep);

	Vector2f center = window.getDefaultView().getCenter();
	DebugDraw dd(center);
	dd.AppendFlags(b2Draw::e_shapeBit);
	world.SetDebugDraw(&dd);

	const b2Vec2 initPos(0, 150);
	const float32 initAngle = 0.20f * b2_pi;

	b2BodyDef boxDef;
	boxDef.type = b2_dynamicBody;
	boxDef.position = initPos;
	boxDef.angle = initAngle;
	b2Body* box = world.CreateBody(&boxDef);
	b2PolygonShape boxShape;
	boxShape.SetAsBox(10, 10);
	b2FixtureDef fixDef;
	fixDef.shape = &boxShape;
	fixDef.density = 10;
	fixDef.friction = 0.3;
	fixDef.restitution = 0.5;
	box->CreateFixture(&fixDef);

	MouseJoint mj(&window, center, &world, ground);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				box->SetTransform(initPos, initAngle);
				box->SetLinearVelocity(b2Vec2(0, 0));
				box->SetAngularVelocity(0);
				box->SetAwake(true);
			}
			else
				mj.update(event);
		}
		world.Step(timeStep, velocityIterations, positionIterations);
		dd.clear();
		world.DrawDebugData();

		window.clear(Color::Black);
		window.draw(dd);
		window.draw(mj);
		window.display();
	}

}