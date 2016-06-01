#pragma once

#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Player.h"
#include "Score.h"
#include <list>

class Resources;
class State;

class Context
{
public:
	virtual void setState(std::shared_ptr<State> state) = 0;
	virtual void backToPrevState() = 0;
	virtual const base::Options& getOptions() const = 0;
	virtual void setOptions(const base::Options& options) = 0;
	virtual const base::Resources& getResources() const = 0;
	virtual sf::Music* getMusic() = 0;
	virtual Score& getScore() = 0;
	virtual Player& getPlayer1() = 0;
	virtual Player& getPlayer2() = 0;
	virtual Ball& getBall() = 0;
};


class State
	: public sf::Drawable
{
public:
	State(Context* context);
	virtual void start();
	virtual void setEvent(const sf::Event& e);
	virtual void update() = 0;
	bool isStarted() const;

protected:
	Context* c;

private:
	State(){}

private:
	bool started = false;
};


class IntroState : public State
{
public:
	IntroState(Context* c);
	~IntroState();
	virtual void setEvent(const sf::Event& e) override;
	virtual void start() override;
	virtual void update() override;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	TextOnScreen pong, player1, player2, startGame, gameOptions;
	sf::Music * music;
};


class ReadySteadyGoState : public State
{
public:
	ReadySteadyGoState(Context* c);
	virtual void update() override;
	virtual void setEvent(const sf::Event& e) override;
	virtual void start() override;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	void startGame();

private:
	class CountDownState : public sf::Drawable {
	public:
		bool isTimeUp();
		virtual void update();
		CountDownState& setDelay(const sf::Time& d);
		CountDownState& setText(const TextOnScreen& t);
		CountDownState& setSound(const sf::Sound& s);
		
	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	private:
		TextOnScreen text;
		sf::Sound sound;
		sf::Time delay;
		sf::Clock clock;
		bool isFirstTimeCall = true;
	};

	class CountDownInterspace : public CountDownState {
	public:
		virtual void update() final {}
	protected:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const final {}
	private:
		CountDownState& setText(const TextOnScreen& t) {}
		CountDownState& setSound(const sf::Sound& s) {}
	};
	
private:
	std::list<CountDownState> countDown;
	TextOnScreen ready;
	TextOnScreen steady;
	TextOnScreen go;
	sf::Sound readySound, goSound;
};


class OptionsState : public State
{
public:
	OptionsState(Context* c) : State(c) {}
	virtual void setEvent(const sf::Event& e) override;
	virtual void start() override;
	virtual void update() override;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	TextOnScreen options, speed, color, ballSize, racketSize;
};


class GameState: public State
{
public:
	GameState(Context* c);

	virtual void setEvent(const sf::Event& e) override;
	virtual void update() override;
	virtual void start() override;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

