#pragma once
#include "stdafx.h"
#include "DebugDraw.h"
#include "MouseJoint.h"
#include "JointMgr.h"

extern sf::Font g_font;

void weld_joint()
{
	RenderWindow window({ 800,600 }, "weld_joint");
	float32 timestep = 1.f / 60.f;
	window.setFramerateLimit(timestep);
	window.setKeyRepeatEnabled(false);
	
	sf::View v = window.getDefaultView();
	v.zoom(0.06f);
	
	sf::Vector2f center = v.getCenter() + sf::Vector2f(0, window.getSize().y / 50.f);
	DebugDraw dd(center);
	dd.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
	b2World world({ 0,-10 });
	world.SetDebugDraw(&dd);

	b2BodyDef bd;
	b2Body *ground = world.CreateBody(&bd);
	b2EdgeShape groundLine;
	float hw = (float)(window.getSize().x) / 2;
	groundLine.Set({ -hw,0 }, { hw,0 });
	ground->CreateFixture(&groundLine, 0);

	bd.type = b2_dynamicBody;
	b2PolygonShape brick;
	const float brickHalfWidth = 0.5f;
	const float brickHalfHeight = 0.125f;
	brick.SetAsBox(brickHalfWidth, brickHalfHeight);
	b2FixtureDef fd;
	fd.shape = &brick;
	fd.density = 20.f;

	b2Body* prev = ground;
	b2Vec2 anchor = { 0, 20 };
	WeldJointsControl wjc("my");
	wjc.damping.assignKey(cmd::Max, Keyboard::Home);
	wjc.damping.assignKey(cmd::Decrease, Keyboard::Divide);
	wjc.damping.assignKey(cmd::Increase, Keyboard::Multiply);
	wjc.freq.assignKey(cmd::Max, Keyboard::End);
	wjc.freq.assignKey(cmd::Decrease, Keyboard::Subtract);
	wjc.freq.assignKey(cmd::Increase, Keyboard::Add);
	wjc.freq.setDelta(10);
	wjc.damping.setRange(0, 10000);
	wjc.damping.setDelta(100);

	for (int i = 0; i < 8; i++)
	{
		b2BodyDef bd;
		bd.type = b2_dynamicBody;
		bd.allowSleep = false;
		bd.position = anchor + b2Vec2(brickHalfWidth, 0);
		b2Body* body = world.CreateBody(&bd);
		body->CreateFixture(&fd);
		b2WeldJointDef jd;
		jd.Initialize(prev, body, anchor);
		b2WeldJoint* j = (b2WeldJoint*)world.CreateJoint(&jd);
		wjc.add(j);
		prev = body;
		anchor += b2Vec2(2 * brickHalfWidth, 0);
	}
	JointControlMgr jMgr(window);
	jMgr.add(wjc);

	MouseJoint mj(&window, center, &world, ground);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			jMgr.update(event);
			mj.update(event);
		}
		world.Step(timestep, 6, 2);
		dd.clear();
		world.DrawDebugData();

		window.clear(sf::Color::Black);
		window.setView(v);
		window.draw(dd);
		window.draw(mj);
		window.draw(jMgr);
		window.display();
	}
}