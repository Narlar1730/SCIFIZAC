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
#include "player.h"
//#include "slimeEnemy.h"
using namespace std;
//Handle interface running
bool runningScreen = true;

int gameclock = 1;
Player mainChar;

#include "slimeEnemy.h"

//Game Clock! to get things to happen at certain times. I did the maths, if you run the game for 24 days striaght
//you will run into a buffer overflow. Sooooooo don't do that I guess? maybe I will put a check in there for later
//to make sure that we don't get anything weird happen
//Handle Characters
vector<char> charPressed ={};

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
			Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos, mainChar.xVel+xVelo, mainChar.yVel+yVelo, 5, 150);
			//Bullet.addSpeed(5, 5);
			AllProjectiles.push_back(Bullet);
		}
		int NumProjectiles = AllProjectiles.size();
		vector<projectile> newVec{};
		for(int i = 0; i < NumProjectiles; i++)
		{
			bool survived = AllProjectiles[i].moveProjectile();
			if(survived)
			{
				newVec.push_back(AllProjectiles[i]);
			}
		}
		
		if(gameclock%300 == 0)
		{
			SlimeEnemy FirstSlime;
			FirstSlime.spawnSlime();
			SlimeList.push_back(FirstSlime);
		}

		int numSlimes = SlimeList.size();
		for(int i = 0; i < numSlimes; i++)
		{
			slime CurSlime = SlimeList[i].moveSlime();
			int slimeX = CurSlime.xpos;
			int slimeY = CurSlime.ypos;
			for(int i = 0; i < NumProjectiles; i++)
			{
				//FIXME -- this is where I got up to, slime collision with bullets.
				//Will do tomorrow
			}
		}

		AllProjectiles = newVec;

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
		
		//FIXME
		//I know I will need mouse down, Just not yet.
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

		next = DrawGameScreen(MouseX, MouseY, MouseReleased, mainChar, window);
		CharsPressed();	
		if(next != 's')
		{
			runningScreen = false;
		}

	}

}

char DrawGameScreen(int mousex, int mousey, bool MouseReleased, Player mainChar, sf::RenderWindow* window)
{
	//Just removing warnings for things I will need later.
	if(mousex == mousey)
	{
	}
	else if(MouseReleased)
	{
	}



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


	//Draw Slimes
	int numSlimes = SlimeList.size();
	for(int i = 0; i < numSlimes; i++)
	{
		SlimeList[i].drawSlime(window);
	}

	//Draw Player
	mainChar.drawPlayer(window);
	
	//Display screen
	window->display();
	window->clear();
	
	//exit function
	return outPut;
}


