#pragma once
#include "stdafx.h"
#include <random>
#include <sstream>
#include "DebugDraw.h"

void updateCount(sf::Text& count, int lCount, int rCount)
{
	std::stringstream ss;
	ss << lCount << "\t\t\t\t\t\t" << rCount << std::endl;
	count.setString(ss.str());
}

static const float32 SPEED = 25;

void pong_box2d()
{
	std::srand(std::time(0));
	
	RenderWindow window(VideoMode(800, 600), "sfml+box2d test3");
	View debugView, sfView;
	debugView.setSize(window.getSize().x, window.getSize().y / 2);
	debugView.setViewport(FloatRect(0, 0, 1, 0.5));
	debugView.zoom(2);
	sfView.setSize(window.getSize().x, window.getSize().y / 2);
	sfView.setViewport(FloatRect(0, 0.5, 1, 0.5));
	sfView.zoom(2);

	b2World world(b2Vec2(0, -2));
	DebugDraw dd(debugView.getCenter());
	dd.AppendFlags(b2Draw::e_shapeBit);
	dd.AppendFlags(b2Draw::e_jointBit);
	world.SetDebugDraw(&dd);
	float32 timestep = 1.f / 60.f;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	window.setFramerateLimit(timestep);

	b2BodyDef groundDef;
	b2Body* ground = world.CreateBody(&groundDef);
	float hwidth = 300;
	float hheight = 200;
	b2Vec2 vs[4] = { {-hwidth, hheight}, {-hwidth, -hheight}, {hwidth, -hheight}, {hwidth, hheight} };
	b2ChainShape field;
	field.CreateLoop(vs, 4);
	ground->CreateFixture(&field, 0);

	b2BodyDef ballDef;
	ballDef.type = b2_dynamicBody;
	ballDef.position.Set(0, 0);
	ballDef.linearVelocity.Set((std::rand() % 2 ? 1 : -1) * SPEED, 0);
	b2Body* ball = world.CreateBody(&ballDef);
	b2FixtureDef ballFix;
	ballFix.density = 0.1;
	ballFix.friction = 0.1;
	ballFix.restitution = 0.9;
	b2CircleShape circle;
	circle.m_radius = 5;
	ballFix.shape = &circle;
	ball->CreateFixture(&ballFix);
	
	static const float32 racketHalfWidth = 5;
	static const float32 racketHalfHeight = 75;
	static const float32 racketOffsetX = hwidth - 4 * racketHalfWidth;
	
	b2BodyDef racketDef;
	racketDef.type = b2_dynamicBody;
	racketDef.angularDamping = 0.3;
	racketDef.position.Set(-racketOffsetX, 0);
	b2Body* racket1 = world.CreateBody(&racketDef);
	b2PolygonShape racketShape;
	racketShape.SetAsBox(racketHalfWidth, racketHalfHeight);
	b2FixtureDef racketFix;
	racketFix.density = 100;
	racketFix.friction = 1;
	racketFix.restitution = 1;
	racketFix.shape = &racketShape;
	racket1->CreateFixture(&racketFix);
	racket1->SetGravityScale(0);
	racketDef.position.Set(racketOffsetX, 0);
	b2Body* racket2 = world.CreateBody(&racketDef);
	racket2->CreateFixture(&racketFix);
	racket2->SetGravityScale(0);

	sf::Font font;
	if (!font.loadFromFile("../res/ARCADECLASSIC.TTF"))
	{
		std::cout << "Can't load font" << std::endl;
		return;
	}
	sf::Text count;
	count.setFont(font);
	count.setCharacterSize(20);
	int rCount = 0, lCount = 0;
	updateCount(count, lCount, rCount);
	count.setOrigin(count.getLocalBounds().left + count.getLocalBounds().width / 2, 0);
	count.setPosition(window.getSize().x / 2, 0);
	
	sf::CircleShape sfBall;
	sfBall.setRadius(circle.m_radius);
	sfBall.setOrigin(sfBall.getRadius(), sfBall.getRadius());
	sfBall.setPosition(box2dToSfml(ball->GetPosition(), sfView.getCenter()));

	static const auto initSfRacket = [&](sf::ConvexShape& _sfShape, const b2Body* _racket)
	{
		const b2PolygonShape* racketShape = 
			static_cast<const b2PolygonShape*>(_racket->GetFixtureList()->GetShape());

		_sfShape.setPointCount(racketShape->GetVertexCount());
		for (int i = 0; i < racketShape->GetVertexCount(); i++)
		{
			_sfShape.setPoint(i, box2dToSfml(racketShape->GetVertex(i), sfView.getCenter()));
		}

		_sfShape.setOrigin(
			_sfShape.getLocalBounds().left + _sfShape.getLocalBounds().width / 2,
			_sfShape.getLocalBounds().top + _sfShape.getLocalBounds().height / 2);

		_sfShape.setPosition(box2dToSfml(_racket->GetPosition(), sfView.getCenter()));
	};
	
	sf::ConvexShape sfRacket1, sfRacket2;
	initSfRacket(sfRacket1, racket1);
	initSfRacket(sfRacket2, racket2);

	sf::VertexArray sfField;
	const b2ChainShape* fieldChain = 
		static_cast<const b2ChainShape*>(ground->GetFixtureList()->GetShape());
	sfField.setPrimitiveType(PrimitiveType::LinesStrip);
	for (int i = 0; i < fieldChain->GetChildCount(); i++)
	{
		b2EdgeShape edge;
		fieldChain->GetChildEdge(&edge, i);
		sfField.append(box2dToSfml(edge.m_vertex1, sfView.getCenter()));
		sfField.append(box2dToSfml(edge.m_vertex2, sfView.getCenter()));
	}
	
	//sf::Clock clock;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		//b2Vec2 velocity(0, 100 * clock.restart().asSeconds());
		racket1->SetTransform(b2Vec2(-racketOffsetX, racket1->GetPosition().y), 0);

		static const b2Vec2 velocity(0, 0.3);
		if (Keyboard::isKeyPressed(Keyboard::W))
			racket1->SetTransform(racket1->GetPosition() + velocity, 0);
		if (Keyboard::isKeyPressed(Keyboard::S))
			racket1->SetTransform(racket1->GetPosition() - velocity, 0);
		
		float32 angle = 0;
		if (Keyboard::isKeyPressed(Keyboard::E))
			angle = 0.25 * b2_pi;
		if (Keyboard::isKeyPressed(Keyboard::D))
			angle = -0.25 * b2_pi;
		
		racket2->SetTransform(b2Vec2(racketOffsetX, racket2->GetPosition().y), 0);

		if (Keyboard::isKeyPressed(Keyboard::Up))
			racket2->SetTransform(racket2->GetPosition() + velocity, 0);
		if (Keyboard::isKeyPressed(Keyboard::Down))
			racket2->SetTransform(racket2->GetPosition() - velocity, 0);

		static const auto stayRacketInFieldBounds = [&](b2Body* _racket) 
		{
			if (_racket->GetFixtureList()->GetAABB(0).upperBound.y > hheight)
				_racket->SetTransform(b2Vec2(_racket->GetPosition().x, hheight - racketHalfHeight), 0);
			
			else if (_racket->GetFixtureList()->GetAABB(0).lowerBound.y < -hheight)
				_racket->SetTransform(b2Vec2(_racket->GetPosition().x, -hheight + racketHalfHeight), 0);
		};

		stayRacketInFieldBounds(racket1);
		stayRacketInFieldBounds(racket2);

		world.Step(timestep, velocityIterations, positionIterations);
		dd.clear();
		world.DrawDebugData();
		
		b2ContactEdge* contactEdge = ball->GetContactList();
		if (ball->GetContactList())
		{
			b2Contact* c = contactEdge->contact;
			const bool isGroundContact = c->GetFixtureA()->GetBody() == ground;
			if (isGroundContact)
			{
				const bool missLeft = c->GetChildIndexA() == 0 && ++rCount;
				const bool missRight = c->GetChildIndexA() == 2 && ++lCount;

				if (missLeft || missRight)
				{
					updateCount(count, lCount, rCount);
					sf::sleep(sf::seconds(1));
					ball->SetLinearVelocity(b2Vec2((std::rand() % 2 ? 1 : -1) * SPEED, 0));
					ball->SetTransform(b2Vec2(0, 0), 0);
					racket1->SetTransform(b2Vec2(racket1->GetPosition().x, 0), 0);
					racket2->SetTransform(b2Vec2(racket2->GetPosition().x, 0), 0);
				}
			}
			static const b2Vec2 reflectVelocity(5, 0);
			if (c->GetFixtureA()->GetBody() == racket1)
				ball->SetLinearVelocity(ball->GetLinearVelocity() + reflectVelocity);
			if (c->GetFixtureA()->GetBody() == racket2)
				ball->SetLinearVelocity(ball->GetLinearVelocity() - reflectVelocity);
		}
		
		window.clear(Color::Black);

		window.setView(debugView);
		window.draw(dd);
				
		window.setView(sfView);

		sfBall.setPosition(box2dToSfml(ball->GetPosition(), sfView.getCenter()));
		sfRacket1.setPosition(box2dToSfml(racket1->GetPosition(), sfView.getCenter()));
		sfRacket2.setPosition(box2dToSfml(racket2->GetPosition(), sfView.getCenter()));

		window.draw(sfBall);
		window.draw(sfRacket1);
		window.draw(sfRacket2);
		window.draw(sfField);
		//window.draw(count);

		window.display();
	}
}