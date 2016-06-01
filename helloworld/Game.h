#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Player.h"
#include "Score.h"
#include "State.h"



class Game :
	public sf::Drawable,
	private Context
{
public:
	Game();
	~Game();
	void applySettings();
	void setEvent(const sf::Event& e);
	void update();
	bool loadResources();
	void create();
	
	// Context
	virtual const base::Options& getOptions() const override;
	virtual void setOptions(const base::Options& options) override;
	virtual const base::Resources& getResources() const override;
	virtual sf::Music* getMusic() override;
	virtual void setState(std::shared_ptr<State> state) override;
	virtual void backToPrevState() override;
	virtual Score& getScore() override;
	virtual Player& getPlayer1() override;
	virtual Player& getPlayer2() override;
	virtual Ball& getBall() override;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	Score score;
	Ball ball;
	Player p1;
	Player p2;
	std::vector<std::shared_ptr<State>> states;
	base::PlayableOptions options;
	base::Resources res;
};

