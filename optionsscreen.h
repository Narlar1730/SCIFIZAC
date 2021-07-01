#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <X11/Xlib.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <tuple>
#include <string>
#include <sstream>
#include <time.h>


using namespace std;
char DrawStatsMenu(int, int, bool, sf::RenderWindow*);
void openingScreen(sf::RenderWindow*);

void statsScreen(sf::RenderWindow* window)
{
	bool screenRunning = true;
	char next;
	while(screenRunning)
	{
	
		sf::Event event;
		sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
		int MouseX = pixelPos.x;
		int MouseY = pixelPos.y;
		bool MouseDown = false;
		bool MouseReleased = false;
		
		//FIXME
		//This is only here to stop a warning, it doesn't do anything
		if(MouseDown)
		{
		
		}
		while(window->pollEvent(event))
		{
			if(event.type == sf::Event::MouseButtonReleased)
			{
				MouseReleased = true;
			}
			else if(event.type == sf::Event::MouseButtonPressed)
			{
				MouseDown = true;
			}
		}

		next = DrawStatsMenu(MouseX, MouseY, MouseReleased, window);

		if(next != 's')
		{
			screenRunning = false;
		}
	}

	switch(next)
	{
		case 'b' :
			openingScreen(window);
			break;
	}
}

char DrawStatsMenu(int mousex, int mousey, bool MouseReleased, sf::RenderWindow* window)
{
	//return s for stay on same screen and don't change screen. 
	char outPut = 's';
	
	//Set Colours
	sf::Color backgroundColour {160, 160, 160};
	sf::Color titleTextColour {0, 0, 255};
	sf::Color buttonColourNoHover {120, 120, 120};
	sf::Color buttonColourHover {140, 140, 140};
	sf::Color black {0, 0, 0};

	//Draw Background
	sf::RectangleShape background(sf::Vector2f(1800.f, 1800.f));
	background.setPosition(0, 0);
	background.setFillColor(backgroundColour);
	window->draw(background);
	
	//Draw Title!
	sf::Text title;
	title.setFont(font);
	title.setString("OPTIONS");
	title.setCharacterSize(60);
	title.setFillColor(titleTextColour);
	title.setStyle(sf::Text::Bold);
	title.setPosition(800, 100);
	window->draw(title);
	
	//Draw Top button, play!
	sf::RectangleShape b1(sf::Vector2f(800.f, 200.f));
	b1.setPosition(500, 400);
	b1.setFillColor(buttonColourNoHover);
	b1.setOutlineColor(black);
	b1.setOutlineThickness(4);
	sf::Text b1Text;
	b1Text.setFont(font);
	b1Text.setString("Need to be filled");
	b1Text.setCharacterSize(40);
	b1Text.setFillColor(black);
	b1Text.setStyle(sf::Text::Bold);
	b1Text.setPosition(580, 480);
	
	//Draw Button 2, options?
	sf::RectangleShape b2(sf::Vector2f(800.f, 200.f));
	b2.setPosition(500, 700);
	b2.setFillColor(buttonColourNoHover);
	b2.setOutlineColor(black);
	b2.setOutlineThickness(4);
	sf::Text b2Text;
	b2Text.setFont(font);
	b2Text.setString("Sound? IDK");
	b2Text.setCharacterSize(40);
	b2Text.setFillColor(black);
	b2Text.setStyle(sf::Text::Bold);
	b2Text.setPosition(580, 780);

	//Draw Button 3, stuff
	sf::RectangleShape b3(sf::Vector2f(800.f, 200.f));
	b3.setPosition(500, 1000);
	b3.setFillColor(buttonColourNoHover);
	b3.setOutlineColor(black);
	b3.setOutlineThickness(4);
	sf::Text b3Text;
	b3Text.setFont(font);
	b3Text.setString("Some other option");
	b3Text.setCharacterSize(40);
	b3Text.setFillColor(black);
	b3Text.setStyle(sf::Text::Bold);
	b3Text.setPosition(580, 1080);

	//Draw Button 4, quit.
	sf::RectangleShape b4(sf::Vector2f(800.f, 200.f));
	b4.setPosition(500, 1300);
	b4.setFillColor(buttonColourNoHover);
	b4.setOutlineColor(black);
	b4.setOutlineThickness(4);
	sf::Text b4Text;
	b4Text.setFont(font);
	b4Text.setString("NADA");
	b4Text.setCharacterSize(40);
	b4Text.setFillColor(black);
	b4Text.setStyle(sf::Text::Bold);
	b4Text.setPosition(580, 1380);

	//Draw Back Button
	sf::RectangleShape backButton(sf::Vector2f(150.f, 100.f));
	backButton.setPosition(10, 10);
	backButton.setFillColor(buttonColourNoHover);
	backButton.setOutlineColor(black);
	backButton.setOutlineThickness(4);
	sf::Text backText;
	backText.setFont(font);
	backText.setString("BACK");
	backText.setCharacterSize(40);
	backText.setFillColor(black);
	backText.setStyle(sf::Text::Bold);
	backText.setPosition(15, 15);

	if(b1.getGlobalBounds().contains(mousex, mousey))
	{
		b1.setFillColor(buttonColourHover);
	}
	else if(b2.getGlobalBounds().contains(mousex, mousey))
	{
		b2.setFillColor(buttonColourHover);
	}
	else if(b3.getGlobalBounds().contains(mousex, mousey))
	{
		b3.setFillColor(buttonColourHover);
	}
	else if(b4.getGlobalBounds().contains(mousex, mousey))
	{
		b4.setFillColor(buttonColourHover);
	}
	else if(backButton.getGlobalBounds().contains(mousex, mousey))
	{
		backButton.setFillColor(buttonColourHover);
		if(MouseReleased)
		{
			outPut = 'b';
		}
	}

	//Slap the buttons down
	window->draw(b1);
	window->draw(b2);
	window->draw(b3);
	window->draw(b4);
	window->draw(backButton);
	
	//Slap the text down
	window->draw(b1Text);
	window->draw(b2Text);
	window->draw(b3Text);
	window->draw(b4Text);
	window->draw(backText);

	//Actually draw the screen
	window->display();
	window->clear();
	//Return current selection
	return outPut;
}


