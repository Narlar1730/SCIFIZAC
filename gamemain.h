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
#include "weapon.h"

using namespace std;
//Handle interface running
bool runningScreen = true;

//Game Clock! to get things to happen at certain times. I did the maths, if you run the game for 24 days striaght
//you will run into a buffer overflow. Sooooooo don't do that I guess? maybe I will put a check in there for later
//to make sure that we don't get anything weird happen
int gameclock = 1;

//Handle Characters
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
	public:
		int xpos, ypos, xVel, yVel, firerate;
		int speed = 20;
	
		void setInitValues(int, int);
		void drawPlayer(sf::RenderWindow*);
		void MoveCharacter();
};

void Player::setInitValues(int x, int y)
{
	xpos = x;
	ypos = y;
	xVel = 0;
	yVel = 0;
	firerate = 30;
}

void Player::drawPlayer(sf::RenderWindow* window)
{
	//Draw Player
	sf::Color PlayerColor {160, 160, 200};
	sf::Color black       {0,     0,   0};
	sf::Color GunGrey     {120, 120, 120};

	sf::CircleShape circle;
	circle.setRadius(40);
	circle.setFillColor(PlayerColor);
	circle.setOutlineColor(black);
	circle.setOutlineThickness(4);
	circle.setPosition(xpos, ypos);


	//Draw gun
	//Gun doesn't point the way I like. Will come back to this later
	//FIXME
	bool DrawGun = false;
	vector<int> angles = {};
	int arrowsPressed = 0;
	if(RIGHTpressed)
	{
		angles.push_back(0);	
		DrawGun = true;
		arrowsPressed+=1;
	}
	if(LEFTpressed)
	{
		angles.push_back(180);
		DrawGun = true;
		arrowsPressed+=1;
	}
	if(UPpressed)
	{
		angles.push_back(270);
		DrawGun = true;
		arrowsPressed+=1;
	}
	if(DOWNpressed)
	{
		angles.push_back(90);
		DrawGun = true;
		arrowsPressed+=1;
	}
	if(DrawGun and arrowsPressed < 3)
	{
		int angle = 0;
		int len = angles.size();
		for(int i = 0; i < len; i++)
		{
			angle += angles[i];
		}	
		angle = angle / len;
		sf::RectangleShape gun(sf::Vector2f(55.f, 10.f));
		gun.setPosition(xpos+35, ypos+35);
		gun.setFillColor(GunGrey);
		gun.setOutlineColor(black);
		gun.setOutlineThickness(4);
		if(RIGHTpressed && UPpressed)
		{
			angle = 315;
		}
		gun.setRotation(angle);
		window->draw(gun);
	}


	//Draw objects in the right order
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

void Player::MoveCharacter()
{
	//Change Speed based on arrow key pressed
	if(Apressed)
	{
		xVel = xVel-speed;
	}
	if(Dpressed)
	{
		xVel = xVel+speed;
	}
	if(Wpressed)
	{
		yVel = yVel-speed;
	}
	if(Spressed)
	{
		yVel = yVel+speed;
	}

	//Slow down chracter
	if(xVel > 0)
	{
		xVel -= 1;
	}
	else if(xVel < 0)
	{
		xVel +=1;
	}

	if(yVel > 0)
	{
		yVel -= 1;
	}
	else if(yVel < 0)
	{
		yVel += 1;
	}
	//set max speed, currently set to be a static 5, but could be changed.
	int topspeed = 3;

	if(xVel > topspeed)
	{
		xVel = topspeed;
	}
	else if(xVel < -1*topspeed)
	{
		xVel = -1*topspeed;
	}
	if(yVel > topspeed)
	{
		yVel = topspeed;
	}
	else if(yVel < -1*topspeed)
	{
		yVel = -1*topspeed;
	}
	xpos = xpos + xVel;
	ypos = ypos + yVel;

}

Player mainChar;

bool checkGunOut()
{
	bool gunOut = false;
	if(UPpressed || DOWNpressed || LEFTpressed || RIGHTpressed)
	{
		gunOut = true;
	}
	return gunOut;
}

void playGameThread()
{
	while (runningScreen)
	{
		bool Firing = checkGunOut();

		mainChar.MoveCharacter();
		//If gameclock ready spawn new shot
		if(gameclock % mainChar.firerate == 0 && Firing)
		{
			//Fixme
			int xVelo = 0;
			int yVelo = 0;

			if(RIGHTpressed)
			{
				xVelo += 5;
			}
			if(LEFTpressed)
			{
				xVelo -= 5;
			}
			if(UPpressed)
			{
				yVelo -= 5;
			}
			if(DOWNpressed)
			{
				yVelo += 5;
			}
			


			projectile Bullet;
			Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos, mainChar.xVel+xVelo, mainChar.yVel+yVelo, 5, 200);
			//Bullet.addSpeed(5, 5);
			AllProjectiles.push_back(Bullet);
		}
		int NumProjectiles = AllProjectiles.size();

		for(int i = 0; i < NumProjectiles; i++)
		{
			bool survived = AllProjectiles[i].moveProjectile();
			if(!survived)
			{
				//Kill bullet idk;
			}
		}

		unsigned int microsecond = 1000000;
		usleep(0.005*microsecond);
		gameclock+=1;
	}
}

void GameScreen(sf::RenderWindow* window)
{
	//Init values
	char next;
	mainChar.setInitValues(900, 900);
	//This thread handles the game stuff. Seperated them in order to have the game render quicker
	//
	
	sf::Thread thread(&playGameThread);
	thread.launch();
	//This loop updates the screen and draws the picture.
	while(runningScreen)
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
		/*for (int i = 0; i < len; i++)
		{
			cout << charPressed[i];
		}
		cout << "\n";
		*/
		if(next != 's')
		{
			runningScreen = false;
		}

	}

}

char DrawGameScreen(int mousex, int mousey, bool MouseReleased, Player mainChar, sf::RenderWindow* window)
{
	//Init variables, colours, etc.
	char outPut = 's';
	sf::Color backgroundColour {160, 160, 160};
	sf::Color black {0, 0, 0};
	
	//Clear the window before we draw
	window->clear();

	//Draw background
	sf::RectangleShape background(sf::Vector2f(1800.f, 1800.f));
	background.setPosition(0, 0);
	background.setFillColor(backgroundColour);
	window->draw(background);
	
	//Draw Player Bullets
	int numShots = AllProjectiles.size();
	for(int i = 0; i < numShots; i++)
	{
		AllProjectiles[i].drawProjectile(window);
	}


	//Draw Player
	mainChar.drawPlayer(window);
	
	//Display screen
	window->display();
	window->clear();
	
	//exit function
	return outPut;
}


