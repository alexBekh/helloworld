#pragma once
#include "stdafx.h"
#include "DebugDraw.h"
#include "MouseJoint.h"


void revolute_joint()
{
	RenderWindow window(VideoMode(800, 600), "sfml+box2d revolute_joint");
	window.setKeyRepeatEnabled(false);

	b2World world(b2Vec2(0, -10));
	Vector2f center(window.getSize().x / 2, window.getSize().y - 100);
	DebugDraw dd(center);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	//flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_centerOfMassBit;
	dd.SetFlags(flags);
	world.SetDebugDraw(&dd);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, -10);
	b2Body* ground = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(390, 10);
	ground->CreateFixture(&groundBox, 0);

	const b2Vec2 initPos(0, 300);
	const float32 initAngle = 0.1f * b2_pi;

	b2BodyDef body1Def;
	body1Def.type = b2_dynamicBody;
	body1Def.position = initPos;
	body1Def.angle = initAngle;
	b2PolygonShape body1Shape;
	body1Shape.SetAsBox(10, 10);
	

	b2FixtureDef fixture;
	fixture.density = 10;
	fixture.friction = 0.8;
	fixture.restitution = 0.5;
	fixture.shape = &body1Shape;
	b2Body* body1 = world.CreateBody(&body1Def);
	body1->CreateFixture(&fixture);

	b2DistanceJointDef distJointDef;
	distJointDef.Initialize(body1, ground, body1->GetWorldCenter(), body1->GetWorldCenter() + b2Vec2(0, 10));
	distJointDef.frequencyHz = 0.2f;
	distJointDef.dampingRatio = 0.1f;
	distJointDef.length = 100;
	distJointDef.collideConnected = true;
	b2DistanceJoint* joint = (b2DistanceJoint*)world.CreateJoint(&distJointDef);

	b2BodyDef body2Def;
	body2Def.type = b2_dynamicBody;
	body2Def.position = body1->GetWorldCenter();
	//body2Def.allowSleep = false;
	body2Def.angle = 0.3 * b2_pi;
	b2Body* body2 = world.CreateBody(&body2Def);
	b2PolygonShape body2Shape;
	float32 radius = 30;
	b2Vec2 vs[3] = { {0, 0}, {-radius, 2 * -radius}, {radius, 2 * -radius} };
	body2Shape.Set(vs, sizeof(vs) / sizeof(vs[0]));
	fixture.shape = &body2Shape;
	body2->CreateFixture(&fixture);

	b2RevoluteJointDef revoluteJointDef;
	revoluteJointDef.Initialize(body1, body2, body1->GetWorldCenter());
	revoluteJointDef.enableMotor = true;
	revoluteJointDef.maxMotorTorque = 100;
	revoluteJointDef.motorSpeed = 50;
	b2RevoluteJoint* revoluteJoint = static_cast<b2RevoluteJoint*>(world.CreateJoint(&revoluteJointDef));

	b2BodyDef wheelDef;
	wheelDef.position.Set(-40, 20);
	wheelDef.type = b2_dynamicBody;
	b2Body* wheel1 = world.CreateBody(&wheelDef);
	b2CircleShape circle;
	circle.m_radius = 20;
	b2FixtureDef wheelFixDef;
	wheelFixDef.density = 0.1;
	wheelFixDef.friction = 0.8;
	wheelFixDef.restitution = 0.5;
	wheelFixDef.shape = &circle;
	wheel1->CreateFixture(&wheelFixDef);
	wheelDef.position.Set(40, 20);
	b2Body* wheel2 = world.CreateBody(&wheelDef);
	wheel2->CreateFixture(&wheelFixDef);
	b2BodyDef carDef;
	//carDef.allowSleep = false;
	carDef.position.Set(0, 20);
	carDef.type = b2_dynamicBody;
	b2Body* car = world.CreateBody(&carDef);
	b2PolygonShape box;
	box.SetAsBox(40, 5);
	car->CreateFixture(&box, 0.1);

	b2RevoluteJointDef jd;
	jd.Initialize(car, wheel1, wheel1->GetWorldCenter());
	jd.enableMotor = true;
	jd.maxMotorTorque = 0;
	jd.motorSpeed = 10;
	//jd.collideConnected = true;
	b2RevoluteJoint* revJ = static_cast<b2RevoluteJoint*>(world.CreateJoint(&jd));
	jd.Initialize(car, wheel2, wheel2->GetWorldCenter());
	world.CreateJoint(&jd);

	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	window.setFramerateLimit(timeStep);
	float32 speed = 0;
	float32 maxTorque = 10;

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
				body1->SetTransform(initPos, initAngle);
				body1->SetLinearVelocity(b2Vec2(0, 0));
				body1->SetAngularVelocity(0);
				body1->SetAwake(true);

				car->SetTransform(b2Vec2(0, 100), 0.25*b2_pi);
				car->SetLinearVelocity(b2Vec2(0, 0));
			}
			else if (event.type == Event::KeyPressed && event.key.code == Keyboard::S)
			{
				revJ->SetMotorSpeed(-revJ->GetMotorSpeed());

				std::cout << "speed=" << revJ->GetMotorSpeed() << std::endl;
			}
			else if (event.type == Event::MouseWheelScrolled)
			{
				static const float32 SPEED = 10;
				if (event.mouseWheelScroll.delta > 0)
				{
					revJ->SetMaxMotorTorque(revJ->GetMaxMotorTorque() + 10);
				}
				else if (event.mouseWheelScroll.delta < 0)
				{
					revJ->SetMaxMotorTorque(revJ->GetMaxMotorTorque() - 10);
				}
				std::cout << "speed=" << revJ->GetMotorSpeed()
					<< "\tmax torque=" << revJ->GetMaxMotorTorque()
					<< std::endl;
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