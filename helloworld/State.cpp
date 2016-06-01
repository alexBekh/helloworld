#include "stdafx.h"
#include "State.h"


void State::setEvent(const sf::Event& e)
{
	if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
	{
		c->backToPrevState();
	}
}

IntroState::IntroState(Context* c): State(c)
{
	pong.options = c->getOptions();
	pong.options.font = c->getResources().font;
	pong.create("borsPong", Size::BIG);
	pong.setPositionOnScreen(Position::TOP);

	options.options = c->getOptions();
	options.options.font = c->getResources().font;
	options.create("options", Size::MIDDLE);
	options.setPositionOnScreen(RelativePosition::UNDER, pong);

	start.options = c->getOptions();
	start.options.font = c->getResources().font;
	start.create("start", Size::LITTLE);
	start.setPositionOnScreen(Position::BOTTOM);

	music = c->getMusic();
	music->play();
}

IntroState::~IntroState()
{
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

void IntroState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(pong, states);
	target.draw(start, states);
	target.draw(options, states);
}

ReadySteadyGoState::ReadySteadyGoState(Context* c) : State(c)
{
	readySound.setBuffer(c->getResources().audio.sound1);
	goSound.setBuffer(c->getResources().audio.sound4);

	ready.options = c->getOptions();
	ready.create("ready..", Size::LITTLE);
	ready.setPositionOnScreen(Position::CENTER);
	CountDownState cdsReady;
	cdsReady.setText(ready).setSound(readySound).setDelay(sf::seconds(0.5));

	steady.options = c->getOptions();
	steady.create("steady..", Size::MIDDLE);
	steady.setPositionOnScreen(Position::CENTER);
	CountDownState cdsSteady;
	cdsSteady.setText(ready).setSound(readySound).setDelay(sf::seconds(0.5));

	go.options = c->getOptions();
	go.create("ready..", Size::BIG);
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
}

void ReadySteadyGoState::update()
{
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

void ReadySteadyGoState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
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

void OptionsState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(options, states);
	target.draw(speed, states);
	target.draw(color, states);
	target.draw(ballSize, states);
	target.draw(racketSize, states);
}

GameState::GameState(Context* c) : State(c)
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
	c->getScore().options.fontName = "../res/ARCADECLASSIC.TTF";
	c->getScore().options.sound.setBuffer(c->getResources().audio.sound3);

	c->getBall().options.gameField = c->getOptions().gameField;
	c->getBall().options.speed = Speed::FAST;

	c->getMusic()->setLoop(true);
	c->getMusic()->setVolume(30);

	c->getPlayer1().createRacket();
	c->getPlayer2().createRacket();
	c->getBall().create();
	c->getScore().create();

	c->setState(std::make_shared<ReadySteadyGoState>(c));
}

void GameState::setEvent(const sf::Event& e)
{
	State::setEvent(e);
}

void GameState::update()
{
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
		c->getScore().update();
		c->setState(std::make_shared<ReadySteadyGoState>(c));
	}
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(c->getPlayer1(), states);
	target.draw(c->getPlayer2(), states);
	target.draw(c->getBall(), states);
	target.draw(c->getScore(), states);
}


