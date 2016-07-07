#pragma once
#include "stdafx.h"
#include "DebugDraw.h"
#include "MouseJoint.h"
#include "JointMgr.h"

#define GROUND_POINT_COUNT 10


void wheel_joint()
{
	RenderWindow window({ 800, 600 }, "sfml+box2d wheel_joint");
	
	float32 timestep = 1.f / 60.f;
	window.setFramerateLimit(timestep);
	window.setKeyRepeatEnabled(false);

	View v = window.getDefaultView();
	v.zoom(0.2);
	window.setView(v);

	Vector2f center = v.getCenter() + Vector2f(0, v.getSize().y / 3);
	DebugDraw dd(center);
	dd.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
	
	b2World world({ 0, -10 });
	world.SetDebugDraw(&dd);

	b2BodyDef bd;
	bd.position.Set(0, -10);
	b2Body* ground = world.CreateBody(&bd);
	b2ChainShape chain;
	float32 x = -v.getSize().x/2;
	float32 deltaX = v.getSize().x / (GROUND_POINT_COUNT-1);
	b2Vec2 vs[GROUND_POINT_COUNT] = { {0,0} };
	std::srand(time(0));

	for (int i = 0; i < GROUND_POINT_COUNT; i++)
	{
		float y = static_cast<float>(rand() % static_cast<int>(v.getSize().y / 10));
		vs[i] = { x, y};
		x += deltaX;
	}
	chain.CreateChain(vs, LENGTH_OF(vs));
	//ground->CreateFixture(&chain, 0);
	b2PolygonShape groundbox;
	groundbox.SetAsBox(300, 10);
	ground->CreateFixture(&groundbox, 0);

	bd.type = b2_dynamicBody;
	bd.position.Set(0, 10);
	b2Body* car = world.CreateBody(&bd);
	b2PolygonShape carshape;
	carshape.SetAsBox(10, 5);
	car->CreateFixture(&carshape, 1);
	
	const float32 wheeloffsetX = 7;
	const float32 wheeloffsetY = -5;
	const float32 wheelradius = 3;
	bd.position = car->GetPosition() + b2Vec2(wheeloffsetX, wheeloffsetY);
	b2Body* wheel1 = world.CreateBody(&bd);
	b2CircleShape circle;
	circle.m_radius = wheelradius;
	b2FixtureDef wfd;
	wfd.density = 3;
	wfd.friction = 0.8;
	wfd.restitution = 0.5;
	wfd.shape = &circle;
	wheel1->CreateFixture(&wfd);

	bd.position = car->GetPosition() + b2Vec2(-wheeloffsetX, wheeloffsetY);
	b2Body* wheel2 = world.CreateBody(&bd);
	wheel2->CreateFixture(&wfd);

	b2WheelJointDef wjd;
	wjd.dampingRatio = 0.7f;
	wjd.frequencyHz = 5.f;
	
	b2Vec2 axis(0, 1);
	wjd.Initialize(car, wheel1, wheel1->GetPosition(), axis);
	b2WheelJoint* w1j = static_cast<b2WheelJoint*>(world.CreateJoint(&wjd));

	wjd.dampingRatio = 0.7f;
	wjd.frequencyHz = 5.f;
	wjd.Initialize(car, wheel2, wheel2->GetPosition(), axis);
	b2WheelJoint* w2j = static_cast<b2WheelJoint*>(world.CreateJoint(&wjd));

	WheelJointControl w1jc(w1j, "w1jc");
	w1jc.motor.assignEnableKey(sf::Keyboard::M);
	
	w1jc.speed.assignKey(cmd::Increase, sf::Keyboard::Add);
	w1jc.speed.assignKey(cmd::Decrease, sf::Keyboard::Subtract);
	w1jc.speed.assignKey(cmd::Inverse, sf::Keyboard::Numpad1);
	
	w1jc.torque.assignKey(cmd::Increase, sf::Keyboard::Multiply);
	w1jc.torque.assignKey(cmd::Decrease, sf::Keyboard::Divide);
	w1jc.torque.assignKey(cmd::Inverse, sf::Keyboard::Numpad3);
	w1jc.torque.assignKey(cmd::Max, sf::Keyboard::Home);
	w1jc.torque.assignKey(cmd::Min, sf::Keyboard::End);
	w1jc.torque.setRange(-50000, 50000);
	
	
	WheelJointControl w2jc(w2j, "w2jc");

	JointControlMgr jcMgr(window);
	jcMgr.add(w1jc);
	jcMgr.add(w2jc);

	MouseJoint mj(&window, center, &world, ground);
	
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else
			{
				mj.update(event);
				jcMgr.update(event);
			}
		}
		world.Step(timestep, 6, 2);
		world.DrawDebugData();

		window.clear(Color::Black);
		window.draw(dd);
		window.draw(jcMgr);
		window.draw(mj);
		window.display();

		dd.clear();
	}
}