#pragma once
#include "stdafx.h"
#include "DebugDraw.h"
#include "MouseJoint.h"
#include "JointMgr.h"


void prismatic_joint()
{
	RenderWindow window(VideoMode(800, 600), "sfml+box2d prismatic_joint");
	float32 timestep = 1.f / 60;
	window.setFramerateLimit(timestep);
	window.setKeyRepeatEnabled(false);

	b2World world(b2Vec2(0, -10));
	Vector2f center = window.getDefaultView().getCenter();
	DebugDraw dd(center);
	dd.AppendFlags(b2Draw::e_shapeBit);
	dd.AppendFlags(b2Draw::e_jointBit);
	world.SetDebugDraw(&dd);
	
	b2BodyDef bd;
	b2Body* ground = world.CreateBody(&bd);
	float xRatio = window.getSize().x / window.getSize().y;
	float yFieldOffset = window.getSize().y / 10;
	float32 hw = window.getSize().x / 2 - yFieldOffset * xRatio;
	float32 hh = window.getSize().y / 2 - yFieldOffset;
	b2Vec2 vs[4] = { {-hw, hh}, {-hw, -hh}, {hw, -hh}, {hw, hh} };
	b2ChainShape field;
	field.CreateLoop(vs, 4);
	ground->CreateFixture(&field, 0);
	
	bd.type = b2_dynamicBody;
	bd.position.Set(-100, -100);
	bd.angle = 0.1 * b2_pi;
	b2Body* body1 = world.CreateBody(&bd);
	b2PolygonShape box;
	box.SetAsBox(30, 45);
	body1->CreateFixture(&box, 10);

	bd.position.Set(200, 0);
	bd.angle = 0.2 * b2_pi;
	bd.allowSleep = false;
	b2Body* body2 = world.CreateBody(&bd);
	box.SetAsBox(40, 25);
	body2->CreateFixture(&box, 0.1);

	b2PrismaticJointDef jd;
	b2Vec2 axis(2, 1);
	axis.Normalize();
	jd.Initialize(ground, body2, b2Vec2(0, 0), axis);
	jd.lowerTranslation = 0.f;
	jd.upperTranslation = 100.f;
	jd.enableLimit = true;
	jd.maxMotorForce = 10000.f;
	jd.motorSpeed = 10.f;
	jd.enableMotor = true;
	jd.collideConnected = true;
	b2PrismaticJoint* j = (b2PrismaticJoint*)world.CreateJoint(&jd);

	PrismaticJointControl pjc(j, "j");
	pjc.limit.assignEnableKey(sf::Keyboard::L);
	
	pjc.motor.assignEnableKey(sf::Keyboard::M);
	
	pjc.speed.assignKey(cmd::Increase, Keyboard::Add);
	pjc.speed.assignKey(cmd::Decrease, Keyboard::Subtract);
	pjc.speed.assignKey(cmd::Reset, Keyboard::Numpad0);
	pjc.speed.assignKey(cmd::Min, Keyboard::Divide);
	pjc.speed.assignKey(cmd::Max, Keyboard::Multiply);
	pjc.speed.assignKey(cmd::Inverse, Keyboard::Return);
	
	pjc.force.assignKey(cmd::Increase, Keyboard::PageUp);
	pjc.force.assignKey(cmd::Decrease, Keyboard::PageDown);
	pjc.force.assignKey(cmd::Reset, Keyboard::Delete);
	pjc.force.assignKey(cmd::Min, Keyboard::Home);
	pjc.force.assignKey(cmd::Max, Keyboard::End);
	pjc.force.assignKey(cmd::Inverse, Keyboard::BackSpace);
	
	JointControlMgr mgr(window);
	mgr.add(pjc);

	MouseJoint mj(&window, center, &world, ground);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			mgr.update(event);
			mj.update(event);
		}

		world.Step(timestep, 6, 2);
		world.DrawDebugData();

		window.clear(Color::Black);
		window.draw(dd);
		window.draw(mgr);
		window.draw(mj);
		window.display();
		dd.clear();
	}
}