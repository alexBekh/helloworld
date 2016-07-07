#pragma once
#include "stdafx.h"
#include "DebugDraw.h"
#include "MouseJoint.h"


void test1()
{
	RenderWindow window(VideoMode(800, 600), "sfml+box2d test");

	Vector2f defViewSize = window.getDefaultView().getSize();
	View sfView;
	sfView.setSize(defViewSize.x / 2, defViewSize.y);
	sfView.setViewport(FloatRect(0, 0, 0.5, 1));
	const float zoomFactor = 1;
	sfView.zoom(zoomFactor);
	View debugView;
	debugView.setSize(defViewSize.x / 2, defViewSize.y);
	debugView.setViewport(FloatRect(0.5, 0, 0.5, 1));
	debugView.zoom(zoomFactor);

	b2World world(b2Vec2(0, -10));
	Vector2f center = debugView.getCenter();
	DebugDraw dd(center);
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	//flags += b2Draw::e_aabbBit;
	//flags += b2Draw::e_centerOfMassBit;
	dd.SetFlags(flags);
	world.SetDebugDraw(&dd);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, -10);
	b2Body* ground = world.CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(150, 10);
	ground->CreateFixture(&groundBox, 0);

	const b2Vec2 initPos(0, 300);
	const float32 initAngle = 0.1f * b2_pi;

	b2BodyDef dynamicBody;
	dynamicBody.type = b2_dynamicBody;
	dynamicBody.position = initPos;
	dynamicBody.angle = initAngle;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(10, 10);
	b2FixtureDef fixture;
	fixture.density = 10;
	fixture.friction = 0.8;
	fixture.restitution = 0.5;
	fixture.shape = &boxShape;
	b2Body* box = world.CreateBody(&dynamicBody);
	box->CreateFixture(&fixture);

	sf::ConvexShape sfGround;
	sfGround.setPointCount(groundBox.GetVertexCount());
	for (int i = 0; i < groundBox.GetVertexCount(); i++)
	{
		sfGround.setPoint(i, box2dToSfml(groundBox.GetVertex(i), sfView.getCenter()));
	}
	sfGround.setOrigin(box2dToSfml(ground->GetLocalCenter(), sfView.getCenter()));
	sfGround.setPosition(box2dToSfml(ground->GetPosition(), sfView.getCenter()));

	sf::ConvexShape sfBox;
	sfBox.setPointCount(boxShape.GetVertexCount());
	for (int i = 0; i < boxShape.GetVertexCount(); i++)
	{
		sfBox.setPoint(i, box2dToSfml(boxShape.GetVertex(i), sfView.getCenter()));
	}
	Vector2f boxCenter;
	boxCenter.x = sfBox.getGlobalBounds().left + sfBox.getGlobalBounds().width / 2;
	boxCenter.y = sfBox.getGlobalBounds().top + sfBox.getGlobalBounds().height / 2;
	sfBox.setOrigin(box2dToSfml(box->GetLocalCenter(), sfView.getCenter()));
	sfBox.setPosition(box2dToSfml(box->GetPosition(), sfView.getCenter()));
	sfBox.setRotation(box->GetAngle() * 180 / b2_pi);

	b2DistanceJointDef distJointDef;
	distJointDef.Initialize(box, ground, box->GetWorldCenter(), box->GetWorldCenter() + b2Vec2(0, 10));
	distJointDef.frequencyHz = 0.2f;
	distJointDef.dampingRatio = 0.1f;
	distJointDef.length = 290;
	distJointDef.collideConnected = true;
	b2DistanceJoint* joint = (b2DistanceJoint*)world.CreateJoint(&distJointDef);
	// Prepare for simulation. Typically we use a time step of 1/60 of a
	// second (60Hz) and 10 iterations. This provides a high quality simulation
	// in most game scenarios.
	float32 timeStep = 1.0f / 60.0f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	window.setFramerateLimit(timeStep);

	MouseJoint mj(&window, center, &world, ground);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
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

		sfBox.setPosition(box2dToSfml(box->GetPosition(), sfView.getCenter()));
		sfBox.setRotation(-box->GetAngle() * 180 / b2_pi);

		window.clear(Color::Black);

		window.setView(sfView);
		window.draw(sfGround);
		window.draw(sfBox);

		window.setView(debugView);
		window.draw(dd);
		window.draw(mj);

		window.display();
	}
}