#include "stdafx.h"
#include "State.h"


void State::setEvent(const sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
	{
		c->backToPrevState();
	}
}

bool State::isStarted() const
{
	return started;
}

State::State(Context* context) : c(context)
{
	if (!c)
		throw std::exception("State: null context ptr");
}

void State::start()
{
	started = true;
}

IntroState::IntroState(Context* c) : State(c)
{
}

IntroState::~IntroState()
{
	if (music->getStatus()==sf::Music::Status::Playing)
		music->stop();
}

void IntroState::setEvent(const sf::Event& e)
{
	if (e.type != sf::Event::KeyPressed)
		return;

	switch (e.key.code)
	{
	case sf::Keyboard::S:
		c->setState(std::make_shared<GameState>(c));
		music->stop();
		break;
	case sf::Keyboard::O:
		c->setState(std::make_shared<OptionsState>(c));
		break;
	default:
		break;
	}
}

void IntroState::start()
{
	pong.options = c->getOptions();
	pong.options.font = c->getResources().font;
	pong.create("borsPong", Size::BIG);
	pong.setPositionOnScreen(Position::TOP);

	gameOptions.options = c->getOptions();
	gameOptions.options.font = c->getResources().font;
	gameOptions.create("options", Size::MIDDLE);
	gameOptions.setPositionOnScreen(RelativePosition::UNDER, pong);
	//gameOptions.setPositionOnScreen(Position::CENTER);
	
	startGame.options = c->getOptions();
	startGame.options.font = c->getResources().font;
	startGame.create("start", Size::LITTLE);
	startGame.setPositionOnScreen(Position::BOTTOM);

	music = c->getMusic();
	music->play();

	State::start();
}

void IntroState::update()
{
	if (!isStarted())
		start();
}

void IntroState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(pong, states);
	target.draw(startGame, states);
	target.draw(gameOptions, states);
}

ReadySteadyGoState::ReadySteadyGoState(Context* c) : State(c)
{
}

void ReadySteadyGoState::update()
{
	if (!isStarted())
		start();

	countDown.front().update();

	if (countDown.front().isTimeUp())
	{
		countDown.pop_front();
		
		if (countDown.empty())
			startGame();
	}
}

void ReadySteadyGoState::setEvent(const sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed)
	{
		startGame();
	}
}

void ReadySteadyGoState::start()
{
	readySound.setBuffer(c->getResources().audio.sound1);
	goSound.setBuffer(c->getResources().audio.sound4);

	ready.options = c->getOptions();
	ready.options.font = c->getResources().font;
	ready.create("ready..", Size::LITTLE);
	ready.setPositionOnScreen(Position::CENTER);
	CountDownState cdsReady;
	cdsReady.setText(ready).setSound(readySound).setDelay(sf::seconds(0.5));

	steady.options = c->getOptions();
	steady.options.font = c->getResources().font;
	steady.create("steady..", Size::MIDDLE);
	steady.setPositionOnScreen(Position::CENTER);
	CountDownState cdsSteady;
	cdsSteady.setText(steady).setSound(readySound).setDelay(sf::seconds(0.5));

	go.options = c->getOptions();
	go.options.font = c->getResources().font;
	go.create("go!", Size::BIG);
	go.setPositionOnScreen(Position::CENTER);
	CountDownState cdsGo;
	cdsGo.setText(go).setSound(goSound).setDelay(sf::seconds(1));

	CountDownInterspace interspace;

	countDown.push_back(cdsReady);
	countDown.push_back(interspace);
	countDown.push_back(cdsSteady);
	countDown.push_back(interspace);
	countDown.push_back(cdsGo);

	sf::sleep(sf::seconds(1));
	c->getBall().start();

	State::start();
}

void ReadySteadyGoState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(c->getPlayer1(), states);
	target.draw(c->getPlayer2(), states);
	target.draw(c->getScore(), states);
	target.draw(countDown.front(), states);
}

void ReadySteadyGoState::startGame()
{
	goSound.play();
	c->getBall().start();
	c->backToPrevState();
}

bool ReadySteadyGoState::CountDownState::isTimeUp()
{
	if (isFirstTimeCall)
	{
		throw std::exception("CountDownState::isTimeUp: call before update()");
	}
	return clock.getElapsedTime() >= delay;
}

void ReadySteadyGoState::CountDownState::update()
{
	if (isFirstTimeCall)
	{
		clock.restart();
		sound.play();
		isFirstTimeCall = false;
	}
}

ReadySteadyGoState::CountDownState& ReadySteadyGoState::CountDownState::setDelay(const sf::Time& d)
{
	delay = d;
	return *this;
}

ReadySteadyGoState::CountDownState& ReadySteadyGoState::CountDownState::setText(const TextOnScreen& t)
{
	text = t;
	return *this;
}

ReadySteadyGoState::CountDownState& ReadySteadyGoState::CountDownState::setSound(const sf::Sound& s)
{
	sound = s;
	return *this;
}

void ReadySteadyGoState::CountDownState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(text, states);
}

void OptionsState::setEvent(const sf::Event& e)
{
	State::setEvent(e);
}

void OptionsState::start()
{
	State::start();
}

void OptionsState::update()
{
	if (!isStarted())
		start();
}

void OptionsState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(options, states);
	target.draw(speed, states);
	target.draw(color, states);
	target.draw(ballSize, states);
	target.draw(racketSize, states);
}

GameState::GameState(Context* c)
	: State(c)
	, world(b2Vec2(0.f, -10.f))
{
}

void GameState::setEvent(const sf::Event& e)
{
	State::setEvent(e);
}

void GameState::update()
{
	if (!isStarted())
		start();

	Ball& b = c->getBall();
	b2Vec2 ballPos = ball->GetPosition();
	b.setPosition(ballPos.x, ballPos.y);
	
	static const float32 timeStep = 1.0f / 60.0f;
	static const int32 velocityIterations = 6;
	static const int32 positionIterations = 2;

	world.Step(timeStep, velocityIterations, positionIterations);
}

void GameState::updateOld()
{
	if (!isStarted())
		start();

	c->getPlayer1().update();
	c->getPlayer2().update();
	c->getBall().update();

	if (c->getBall().tryLeft(c->getPlayer1().racket.getGlobalBounds()))
		c->getPlayer1().options.sound.play();

	if (c->getBall().tryRight(c->getPlayer2().racket.getGlobalBounds()))
		c->getPlayer2().options.sound.play();

	if ((c->getBall().isMissedLeft() && ++c->getPlayer1().missCount)
		||
		(c->getBall().isMissedRight() && ++c->getPlayer2().missCount))
	{
		c->getBall().options.sound.play();
		c->getScore().update();
		c->setState(std::make_shared<ReadySteadyGoState>(c));
	}
}

void GameState::start()
{
	c->getPlayer1().options.gameField = c->getOptions().gameField;
	c->getPlayer1().options.sound.setBuffer(c->getResources().audio.sound1);
	c->getPlayer1().options.controls.up = sf::Keyboard::W;
	c->getPlayer1().options.controls.down = sf::Keyboard::S;
	c->getPlayer1().options.name = "Player1";

	c->getPlayer2().options.gameField = c->getOptions().gameField;
	c->getPlayer2().options.sound.setBuffer(c->getResources().audio.sound2);
	c->getPlayer2().options.side = Player::Options::Side::RIGHT;
	c->getPlayer2().options.name = "Player2";

	c->getScore().options.gameField = c->getOptions().gameField;
	c->getScore().options.p1 = &c->getPlayer1();
	c->getScore().options.p2 = &c->getPlayer2();
	c->getScore().options.shape.size = Size::LITTLE;
	c->getScore().options.font = c->getResources().font;
	
	c->getBall().options.gameField = c->getOptions().gameField;
	c->getBall().options.speed = Speed::FAST;
	c->getBall().options.sound.setBuffer(c->getResources().audio.sound3);

	c->getMusic()->setLoop(true);
	c->getMusic()->setVolume(30);

	c->getPlayer1().createRacket();
	c->getPlayer2().createRacket();
	c->getBall().create();
	c->getScore().create();

	c->setState(std::make_shared<ReadySteadyGoState>(c));

	State::start();

	bindWithBox2d();
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(c->getPlayer1(), states);
	target.draw(c->getPlayer2(), states);
	target.draw(c->getBall(), states);
	target.draw(c->getScore(), states);
}

void GameState::bindWithBox2d()
{
	sf::FloatRect gf = c->getOptions().gameField;
	{
		b2BodyDef bd;
		bd.position.Set(gf.left + gf.width/2, gf.top + gf.height/2);
		field = world.CreateBody(&bd);

		b2EdgeShape shape;

		b2FixtureDef sd;
		sd.shape = &shape;
		sd.density = 0.0f;
		sd.restitution = 0.4f;

		b2Vec2 leftBottom(-gf.width / 2, -gf.height / 2)
			, leftTop(-gf.width / 2, gf.height / 2)
			, rightBottom(gf.width / 2, -gf.height / 2)
			, rightTop(gf.width / 2, gf.height / 2);

		// Left vertical
		shape.Set(leftBottom, leftTop);
		field->CreateFixture(&sd);

		// Right vertical
		shape.Set(rightBottom, rightTop);
		field->CreateFixture(&sd);

		// Top horizontal
		shape.Set(leftTop, rightTop);
		field->CreateFixture(&sd);

		// Bottom horizontal
		shape.Set(leftBottom, rightBottom);
		field->CreateFixture(&sd);
	}

	// Define the dynamic body. We set its position and call the body factory.
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(gf.left + gf.width / 2, gf.top + gf.height / 2);
	ball = world.CreateBody(&bodyDef);

	// Define another box shape for our dynamic body.
	b2CircleShape circle;
	circle.m_p.Set(gf.left + gf.width / 2, gf.top + gf.height / 2);
	circle.m_radius = c->getBall().ballShape.getRadius();

	// Define the dynamic body fixture.
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;

	// Set the box density to be non-zero, so it will be dynamic.
	fixtureDef.density = 10.f;

	// Override the default friction.
	fixtureDef.friction = 0.3f;

	fixtureDef.restitution = 0.5f;

	// Add the shape to the body.
	ball->CreateFixture(&fixtureDef);
}




