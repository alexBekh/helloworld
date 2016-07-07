#pragma once
#include "stdafx.h"
#include "DebugDraw.h"
#include "MouseJoint.h"
#include "JointMgr.h"

void rope_joint()
{
	sf::RenderWindow window({ 800,600 }, "rope joint");
	window.setKeyRepeatEnabled(false);
	float timestep = 1.f / 60;
	window.setFramerateLimit(timestep);
	sf::View v = window.getDefaultView();
	const float zoomFactor = 0.1f;
	v.zoom(zoomFactor);
	window.setView(v);

	b2World world({ 0,-10 });
	sf::Vector2f center = v.getCenter() /*+ sf::Vector2f(0, window.getSize().y * zoomFactor / 3)*/;
	DebugDraw dd(center);
	dd.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
	world.SetDebugDraw(&dd);

	b2BodyDef bd;
	b2Body* ground = world.CreateBody(&bd);
	b2EdgeShape line;
	line.Set({ -10, 0 }, { 10, 0 });
	ground->CreateFixture(&line, 0);

	b2RopeJointDef jd;
	jd.localAnchorA.Set(0, 15);
	jd.localAnchorB.SetZero();
	jd.maxLength = 10.f;

	bd.type = b2_dynamicBody;
	bd.position.Set(0, jd.localAnchorA.y - jd.maxLength);
	bd.allowSleep = false;
	bd.angularDamping = 0.5f;
	bd.linearDamping = 0.2f;
	b2Body* body = world.CreateBody(&bd);
	b2PolygonShape shape;
	shape.SetAsBox(1.5f, 1.5f);
	body->CreateFixture(&shape, 10);
	
	jd.bodyA = ground;
	jd.bodyB = body;
	jd.collideConnected = true;
	b2RopeJoint* j = (b2RopeJoint*) world.CreateJoint(&jd);

	RopeJointControl jc(j, "j");
	jc.len.assignKey(cmd::Increase, sf::Keyboard::Add);
	jc.len.assignKey(cmd::Decrease, sf::Keyboard::Subtract);
	jc.len.assignKey(cmd::Reset, sf::Keyboard::Numpad0);
	jc.len.setDelta(1);

	JointControlMgr mgr(window);
	mgr.add(jc);

	MouseJoint mj(&window, center, &world, ground);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			mgr.update(event);
			mj.update(event);
		}
		world.Step(timestep, 6, 2);
		dd.clear();
		world.DrawDebugData();

		window.clear(sf::Color::Black);
		window.draw(dd);
		window.draw(mgr);
		window.draw(mj);
		window.display();
	}
}