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
vector<char> charPressed ={};

bool Dpressed = false;
bool Epressed = false;
bool Spressed = false;
bool Apressed = false;
bool Wpressed = false;
bool Lpressed = false;


bool UPpressed    = false;
bool DOWNpressed  = false;
bool LEFTpressed  = false;
bool RIGHTpressed = false;

class Player {
	int xpos, ypos;
	float xVel, yVel;

	public:
		void setInitValues(int, int);
		void drawPlayer(sf::RenderWindow*);
};

void Player::setInitValues(int x, int y)
{
	xpos = x;
	ypos = y;
	xVel = 0;
	yVel = 0;
}

void Player::drawPlayer(sf::RenderWindow* window)
{
	sf::Color PlayerColor {160, 160, 180};
	sf::Color black {0, 0, 0};

	sf::CircleShape circle;
	circle.setRadius(150);
	circle.setFillColor(PlayerColor);
	circle.setOutlineColor(black);
	circle.setOutlineThickness(4);
	circle.setPosition(xpos, ypos);

	window->draw(circle);

}


void CharsPressed()
{
	vector<char> outArray = {};
	if(Dpressed)
	{
		outArray.push_back('d');
	}
	if(Epressed)
	{
		outArray.push_back('e');
	}
	if(Spressed)
	{
		outArray.push_back('s');
	}
	if(Apressed)
	{
		outArray.push_back('a');
	}
	if(Wpressed)
	{
		outArray.push_back('w');
	}
	if(Lpressed)
	{
		outArray.push_back('l');
	}
	charPressed = outArray;
}
char DrawGameScreen(int, int, bool, Player, sf::RenderWindow*);


void GameScreen(sf::RenderWindow* window)
{
	bool screenRunning = true;
	char next;
	Player mainChar;
	mainChar.setInitValues(900, 900);
	while(screenRunning)
	{

		sf::Event event;
		sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
		int MouseX = pixelPos.x;
		int MouseY = pixelPos.y;
		bool MouseDown = false;
		bool MouseReleased = false;

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

		next = DrawGameScreen(MouseX, MouseY, MouseReleased, mainChar, window);
		CharsPressed();	
		int len = charPressed.size();
		for (int i = 0; i < len; i++)
		{
			cout << charPressed[i];
		}
		cout << "\n";

		if(next != 's')
		{
			screenRunning = false;
		}

		unsigned int microsecond = 1000000;
		usleep(0.015*microsecond);

	}

}

char DrawGameScreen(int mousex, int mousey, bool MouseReleased, Player mainChar, sf::RenderWindow* window)
{
	char outPut = 's';
	sf::Color backgroundColour {160, 160, 160};
	sf::Color black {0, 0, 0};
	
	//Draw background
	sf::RectangleShape background(sf::Vector2f(1800.f, 1800.f));
	background.setPosition(0, 0);
	background.setFillColor(backgroundColour);
	window->draw(background);

	//Draw Player
	mainChar.drawPlayer(window);

	//Display screen
	window->display();
	window->clear();
	
	//exit function
	return outPut;
}


