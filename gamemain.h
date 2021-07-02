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
#include <math.h>
#include <time.h>
#include "player.h"
//#include "slimeEnemy.h"
using namespace std;
//Handle interface running
bool runningScreen = true;

int gameclock = 1;
Player mainChar;

#include "weapon.h"
#include "slimeEnemy.h"

//Game Clock! to get things to happen at certain times. I did the maths, if you run the game for 24 days striaght
//you will run into a buffer overflow. Sooooooo don't do that I guess? maybe I will put a check in there for later
//to make sure that we don't get anything weird happen

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

bool circleIntercept(int x1, int y1, int r1, int x2, int y2, int r2)
{
	bool intercept = false;

	float Distance = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));

	float totalRadius = static_cast<float>(r1) + static_cast<float>(r2);

	if(Distance < totalRadius)
	{
		intercept = true;
	}

	return intercept;
}

void playGameThread()
{
	FirstGun.setGun(100, 30, 150, 'R', 8, 0);
	while (runningScreen)
	{
		bool Firing = checkGunOut();

		mainChar.MoveCharacter();
		//If gameclock ready spawn new shot
		if(Firing)
		{
			FirstGun.FireWeapon();
		}
		if(Lpressed)
		{
			FirstGun.setGun(100, 30, 75, 'S', 8, 15);
		}
		int NumProjectiles = AllProjectiles.size();
		vector<projectile> newVec{};
		vector<SlimeEnemy> slimeVec{};
		
		//Spawn New SLimes
		if(gameclock%300 == 0)
		{
			SlimeEnemy FirstSlime;
			FirstSlime.spawnSlime();
			SlimeList.push_back(FirstSlime);
		}
		
		// Update slime position
		int numSlimes = SlimeList.size();
		
		for(int i = 0; i < numSlimes; i++)
		{
			SlimeList[i].moveSlime();
			SlimeEnemy CurSlime = SlimeList[i];
			int slimeR = CurSlime.curRadius;
			int slimeX = CurSlime.xpos;
			int slimeY = CurSlime.ypos;
			for(int j = 0; j < NumProjectiles; j++)
			{
				//FIXME
				int Pradi = AllProjectiles[j].radius;
				int Pxpos = AllProjectiles[j].xpos + Pradi;
				int Pypos = AllProjectiles[j].ypos + Pradi;

				if(circleIntercept(slimeX, slimeY, slimeR, Pxpos, Pypos, Pradi) || Epressed)
				{
					SlimeList[i].hurtSlime(100);
					AllProjectiles[j].Alive = false;
				}
			}
			if(SlimeList[i].health > 0)
			{
				slimeVec.push_back(SlimeList[i]);
			}
		}

		SlimeList = slimeVec;
		// Update bullet position
		for(int i = 0; i < NumProjectiles; i++)
		{
			bool survived = AllProjectiles[i].moveProjectile();
			if(survived && AllProjectiles[i].Alive)
			{
				newVec.push_back(AllProjectiles[i]);
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


