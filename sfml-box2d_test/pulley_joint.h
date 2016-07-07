#pragma once
#include "stdafx.h"
#include "DebugDraw.h"
#include "MouseJoint.h"


void pulley_joint()
{
	RenderWindow window(VideoMode(800,600), "sfml+box2d pulley_joint");
	View v = window.getDefaultView();
	v.zoom(0.2);
	window.setView(v);

	float32 timestep = 1.f / 60;
	window.setFramerateLimit(timestep);

	b2World world(b2Vec2( 0, -10 ));
	Vector2f center = v.getCenter() + Vector2f(0, v.getSize().y / 3);
	DebugDraw dd(center);
	dd.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_centerOfMassBit);
	world.SetDebugDraw(&dd);
	
	b2BodyDef bd;
	b2Body* ground = world.CreateBody(&bd);
	b2EdgeShape edge;
	edge.Set({ -40, 0 }, { 40,0 });
	//ground->CreateFixture(&edge, 0);
	
	bd.type = b2_dynamicBody;
	b2Body *block1, *block2;
	bd.position.Set(-30, 50);
	block1 = world.CreateBody(&bd);
	bd.position.Set(30, 50);
	block2 = world.CreateBody(&bd);
	b2PolygonShape box;
	box.SetAsBox(5, 10);
	block1->CreateFixture(&box, 9);
	box.SetAsBox(5, 10);
	block2->CreateFixture(&box, 10);

	b2PulleyJointDef jd;
	jd.Initialize(
		block1,
		block2,
		block1->GetWorldCenter() + b2Vec2(0, 40),
		block2->GetWorldCenter() + b2Vec2(0, 40),
		block1->GetWorldCenter(),
		block2->GetWorldCenter(),
		1);
	
	b2PulleyJoint* j = static_cast<b2PulleyJoint*>(world.CreateJoint(&jd));
	
	{
		float32 y = 16.0f;
		float32 L = 12.0f;
		float32 a = 1.0f;
		float32 b = 2.0f;

		//b2Body* ground = NULL;
		{/*
			b2BodyDef bd;
			ground = world.CreateBody(&bd);

			b2EdgeShape edge;
			edge.Set(b2Vec2(-40.0f, 0.0f), b2Vec2(40.0f, 0.0f));*/
			////ground->CreateFixture(&shape, 0.0f);

			b2CircleShape circle;
			circle.m_radius = 2.0f;

			circle.m_p.Set(-10.0f, y + b + L);
			ground->CreateFixture(&circle, 0.0f);

			circle.m_p.Set(10.0f, y + b + L);
			ground->CreateFixture(&circle, 0.0f);
		}

		{

			b2PolygonShape shape;
			shape.SetAsBox(a, b);

			b2BodyDef bd;
			bd.type = b2_dynamicBody;

			//bd.fixedRotation = true;
			bd.position.Set(-10.0f, y);
			b2Body* body1 = world.CreateBody(&bd);
			body1->CreateFixture(&shape, 5.0f);

			bd.position.Set(10.0f, y);
			b2Body* body2 = world.CreateBody(&bd);
			body2->CreateFixture(&shape, 5.0f);

			b2PulleyJointDef pulleyDef;
			b2Vec2 anchor1(-10.0f, y + b);
			b2Vec2 anchor2(10.0f, y + b);
			b2Vec2 groundAnchor1(-10.0f, y + b + L);
			b2Vec2 groundAnchor2(10.0f, y + b + L);
			pulleyDef.Initialize(body1, body2, groundAnchor1, groundAnchor2, anchor1, anchor2, 1.5f);

			b2PulleyJoint* m_joint1 = (b2PulleyJoint*)world.CreateJoint(&pulleyDef);
		}
	}

	MouseJoint mj(&window, center, &world, ground);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			else
				mj.update(event);
		}

		world.Step(timestep, 8, 3);
		world.DrawDebugData();

		window.clear(Color::Black);
		window.draw(dd);
		window.draw(mj);
		window.display();

		dd.clear();
	}

}