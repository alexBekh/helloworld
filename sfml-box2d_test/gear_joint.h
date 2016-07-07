#pragma once
#include"stdafx.h"
#include"DebugDraw.h"
#include"FindFixtureByPosQuery.h"
#include"MouseJoint.h"


void gear_joint()
{
	RenderWindow window({ 800, 600 }, "sfml+box2d gear_joint");
	View view = window.getDefaultView();
	view.zoom(0.2);
	window.setView(view);
	float32 timestep = 1.f / 60.f;
	window.setFramerateLimit(timestep);

	b2World world({ 0,-10 });
	Vector2f center = view.getCenter() + Vector2f(0, view.getSize().y / 3);
	DebugDraw dd(center);
	dd.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
	world.SetDebugDraw(&dd);

	const float xOffset = 40;
	b2BodyDef bd;
	b2Body* ground = world.CreateBody(&bd);
	b2EdgeShape edge;
	edge.Set({ -xOffset, 0 }, { xOffset, 0 });
	ground->CreateFixture(&edge, 0);

	const float32 h = 50;
	bd.type = b2_dynamicBody;
	bd.position.Set(-xOffset, h);
	b2Body* gear = world.CreateBody(&bd);
	b2CircleShape circle;
	circle.m_radius = 10;
	gear->CreateFixture(&circle, 5);
	b2RevoluteJointDef rjd;
	rjd.Initialize(ground, gear, gear->GetWorldCenter());
	rjd.maxMotorTorque = 0;
	rjd.motorSpeed = b2_pi;
	rjd.enableMotor = true;
	b2RevoluteJoint* rj = static_cast<b2RevoluteJoint*>(world.CreateJoint(&rjd));

	bd.position.Set(0, 15);
	b2Body* gear2 = world.CreateBody(&bd);
	b2CircleShape circle2;
	circle2.m_radius = 5;
	gear2->CreateFixture(&circle2, 5);
	b2RevoluteJointDef rjd2;
	rjd2.Initialize(ground, gear2, gear2->GetWorldCenter());
	b2RevoluteJoint* rj2 = static_cast<b2RevoluteJoint*>(world.CreateJoint(&rjd2));
	b2GearJointDef gjd2;
	gjd2.bodyA = gear;
	gjd2.bodyB = gear2;
	gjd2.joint1 = rj;
	gjd2.joint2 = rj2;
	gjd2.ratio = circle2.m_radius / circle.m_radius;
	auto gj2 = static_cast<b2GearJoint*>(world.CreateJoint(&gjd2));

	const float32 boxHalfHeight = 5;
	bd.position.Set(xOffset, h);
	bd.allowSleep = false;
	b2Body* block = world.CreateBody(&bd);
	b2PolygonShape box;
	box.SetAsBox(1, boxHalfHeight);
	block->CreateFixture(&box, 5);
	b2PrismaticJointDef pjd;
	pjd.Initialize(ground, block, block->GetPosition(), b2Vec2(0, 1));
	pjd.lowerTranslation = -40;
	pjd.upperTranslation = 40;
	pjd.enableLimit = true;
	pjd.collideConnected = true;
	b2PrismaticJoint* pj = static_cast<b2PrismaticJoint*>(world.CreateJoint(&pjd));

	b2GearJointDef gjd;
	gjd.joint1 = rj;
	gjd.joint2 = pj;
	gjd.bodyA = gear;
	gjd.bodyB = block;
	float ratio =  -1.f / circle.m_radius;
	std::cout << "ratio=" << ratio << std::endl;
	gjd.ratio = ratio;
	b2GearJoint* gj = static_cast<b2GearJoint*>(world.CreateJoint(&gjd));

	MouseJoint mj(&window, center, &world, ground);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			else if (event.type == Event::MouseWheelScrolled)
			{
				float32 d = 1000 * (event.mouseWheelScroll.delta > 0 ? 1 : -1);

				rj->SetMaxMotorTorque(rj->GetMaxMotorTorque() + d);
				std::cout << " rj torque=" << rj->GetMaxMotorTorque() << std::endl;
			}
			else if (event.type == Event::MouseButtonPressed
				&& event.mouseButton.button == Mouse::Button::Middle)
			{
				rj->SetMaxMotorTorque(0);
				std::cout << " rj torque=" << rj->GetMaxMotorTorque() << std::endl;
			}
			else if (event.type == Event::MouseButtonPressed
				&& event.mouseButton.button == Mouse::Button::Right)
			{
				rj->SetMotorSpeed(-rj->GetMotorSpeed());
				std::cout << " rj speed=" << rj->GetMotorSpeed() << std::endl;
			}
			else
				mj.update(event);
		}
		world.Step(timestep, 6, 2);
		world.DrawDebugData();
		window.clear(Color::Black);
		window.draw(dd);
		window.draw(mj);
		window.display();
		dd.clear();
	}
}