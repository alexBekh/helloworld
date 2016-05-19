// helloworld.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Player.h"
#include "Ball.h"
#include "Score.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode(600,400), "thePong", sf::Style::Default^sf::Style::Resize);
	
	sf::SoundBuffer beep1;
	if (!beep1.loadFromFile("../res/Beep1.wav"))
		return 1;
	sf::SoundBuffer beep2;
	if (!beep2.loadFromFile("../res/Beep2.wav"))
		return 1;
	sf::SoundBuffer beep8;
	if (!beep8.loadFromFile("../res/Beep8.wav"))
		return 1;
	sf::SoundBuffer beep9;
	if (!beep9.loadFromFile("../res/Beep9.wav"))
		return 1;
	
	sf::Music music;
	if (!music.openFromFile("../res/Visager_-_26_-_We_Can_Do_It_Loop.ogg"))
		return 1;

	music.setLoop(true);
	music.setVolume(30);
	music.play();
	
	const sf::FloatRect gameField(10, 10, window.getSize().x - 20, window.getSize().y - 20);
	
	Player p1;
	p1.options.gameField = gameField;
	p1.options.sound.setBuffer(beep1);
	p1.options.controls.up = sf::Keyboard::W;
	p1.options.controls.down = sf::Keyboard::S;
	p1.options.name = "Player1";
	p1.createRacket();
	
	Player p2;
	p2.options.gameField = gameField;
	p2.options.sound.setBuffer(beep2);
	p2.options.side = Player::Options::Side::RIGHT;
	p2.options.name = "Player2";
	p2.createRacket();

	Score score;
	score.options.gameField = gameField;
	score.options.p1 = &p1;
	score.options.p2 = &p2;
	score.options.shape.size = Options::Shape::Size::LITTLE;
	score.options.fontName = "../res/ARCADECLASSIC.TTF";
	score.options.sound.setBuffer(beep8);
	if (!score.create())
		return 1;

	Ball ball;
	ball.options.gameField = gameField;
	ball.options.speed = Options::Speed::NORMAL;
	ball.create();
	ball.start();

	bool restart = false;
	
	sf::FloatRect outOfScreenBounds(-ball.ballShape.getRadius(), -ball.ballShape.getRadius(),
		window.getSize().x + 2 * ball.ballShape.getRadius(),
		window.getSize().y + 2 * ball.ballShape.getRadius());

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		p1.update();
		p2.update();

		if (restart && !outOfScreenBounds.contains(ball.ballShape.getPosition()))
		{
			sf::sleep(sf::seconds(1));
			ball.start();
			sf::View view(window.getDefaultView());
			window.setView(view);
			sf::Sound readySound(beep1);
			
			for (int i = 0; i < 3; i++)
			{
				sf::sleep(sf::seconds(0.5));
				window.clear(sf::Color::Black);
				window.display();
				sf::sleep(sf::seconds(0.5));
				window.draw(ball);
				window.display();
				readySound.play();
			}
			sf::Sound goSound(beep9);
			goSound.play();
			sf::sleep(sf::seconds(1));

			window.setView(window.getDefaultView());
			ball.start();
			restart = false;
		}
		else
		{
			ball.update();
		}

		if (!restart)
		{
			if (ball.tryLeft(p1.racket.getGlobalBounds()))
				p1.options.sound.play();

			if (ball.tryRight(p2.racket.getGlobalBounds()))
				p2.options.sound.play();

			if (
				(ball.isMissedLeft() && ++p1.missCount)
				||
				(ball.isMissedRight() && ++p2.missCount))
			{
				score.update();
				score.options.sound.play();
				restart = true;
			}
		}
		
		window.clear(sf::Color::Black);
		window.draw(p1);
		window.draw(p2);
		window.draw(ball);
		window.draw(score);
		window.display();
	}
    return 0;
}

