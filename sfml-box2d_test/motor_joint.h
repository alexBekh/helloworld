#pragma once
#include "stdafx.h"
#include "DebugDraw.h"
#include "MouseJoint.h"
#include "JointMgr.h"


void motor_joint()
{
	RenderWindow window({ 800,600 }, "motor_joint");
	window.setKeyRepeatEnabled(false);
	float timestep = 1.f / 60;
	window.setFramerateLimit(timestep);

	sf::View v = window.getDefaultView();
	const float zoomFactor = 0.1f;
	v.zoom(zoomFactor);
	window.setView(v);

	sf::Vector2f center = v.getCenter() + sf::Vector2f(0, /*2 * zoomFactor * */v.getSize().y / 3);
	DebugDraw dd(center);
	dd.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
	
	b2World world({ 0,-10 });
	world.SetDebugDraw(&dd);

	b2BodyDef bd;
	b2Body* ground = world.CreateBody(&bd);
	b2EdgeShape shape;
	shape.Set({ -20, 0 }, { 20, 0 });
	ground->CreateFixture(&shape, 0);

	bd.type = b2_dynamicBody;
	bd.position.Set(0, 30);
	b2Body* body = world.CreateBody(&bd);
	b2PolygonShape box;
	box.SetAsBox(4, 0.5);
	body->CreateFixture(&box, 10.f);

	b2MotorJointDef jd;
	jd.Initialize(ground, body);
	jd.collideConnected = true;
	jd.maxForce = 1000.f;
	jd.maxTorque = 1000.f;
	b2MotorJoint* j = (b2MotorJoint*)world.CreateJoint(&jd);

	MotorJointControl mjc(j, "j");
	mjc.assignRunKey(sf::Keyboard::Space);

	JointControlMgr mgr(window);
	mgr.add(mjc);

	MouseJoint mj(&window, center, &world, ground);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			mgr.update(event);
			mj.update(event);
		}

		mjc.run(center);
		
		world.Step(timestep, 6, 2);
		dd.clear();
		world.DrawDebugData();

		window.clear(sf::Color::Black);
		window.draw(dd);
		window.draw(mjc);
		window.draw(mgr);
		window.draw(mj);
		window.display();
	}
}