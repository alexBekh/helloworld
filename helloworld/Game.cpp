#include "stdafx.h"
#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::applySettings()
{
	p1.options.gameField = options.gameField;
	p1.options.sound.setBuffer(res.audio.sound1);
	p1.options.controls.up = sf::Keyboard::W;
	p1.options.controls.down = sf::Keyboard::S;
	p1.options.name = "Player1";

	p2.options.gameField = options.gameField;
	p2.options.sound.setBuffer(res.audio.sound2);
	p2.options.side = Player::Options::Side::RIGHT;
	p2.options.name = "Player2";

	score.options.gameField = options.gameField;
	score.options.p1 = &p1;
	score.options.p2 = &p2;
	score.options.shape.size = Size::LITTLE;
	score.options.fontName = "../res/ARCADECLASSIC.TTF";
	score.options.sound.setBuffer(res.audio.sound3);

	ball.options.gameField = options.gameField;
	ball.options.speed = Speed::FAST;

	res.audio.music.setLoop(true);
	res.audio.music.setVolume(30);
}

void Game::setEvent(const sf::Event& e)
{
	if(!states.empty())
		states.back()->setEvent(e);
}

void Game::update()
{
	if(!states.empty())
		states.back()->update();
}

void Game::setOptions(const base::Options& options)
{
	this->options = options;
}

const base::Options& Game::getOptions() const 
{
	return options;
}

const base::Resources& Game::getResources() const 
{
	return res;
}

sf::Music* Game::getMusic()
{
	return &res.audio.music;
}

void Game::setState(std::shared_ptr<State> state)
{
	states.push_back(state);
}

void Game::backToPrevState()
{
	if (states.empty())
		throw std::exception("Game::backToPrevState: no state");

	states.pop_back();
}

Score& Game::getScore()
{
	return score;
}

Player& Game::getPlayer1()
{
	return p1;
}

Player& Game::getPlayer2()
{
	return p2;
}

Ball& Game::getBall()
{
	return ball;
}

bool Game::loadResources()
{
	if (!res.audio.sound1.loadFromFile("../res/Beep1.wav"))
		return false;
	if (!res.audio.sound1.loadFromFile("../res/Beep2.wav"))
		return false;
	if (!res.audio.sound3.loadFromFile("../res/Beep8.wav"))
		return false;
	if (!res.audio.sound4.loadFromFile("../res/Beep9.wav"))
		return false;
	if (!res.audio.music.openFromFile("../res/Visager_-_26_-_We_Can_Do_It_Loop.ogg"))
		return false;
	if (!res.font.loadFromFile("../res/ARCADECLASSIC.TTF"))
		return false;

	return true;
}

void Game::create()
{
	setState(std::make_shared<IntroState>(static_cast<Context*>(this)));
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(*this->states.back(), states);
}
