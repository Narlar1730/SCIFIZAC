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
#include "obstacles.h"
#include "player.h"
//#include "slimeEnemy.h"
using namespace std;
//Handle interface running
bool runningScreen = true;
bool runningGame = true;

int gameclock = 1;
Player mainChar;
int buttonClickTimer = 0;
#include "weapon.h"
#include "inventory.h"
#include "pausescreen.h"
#include "slimeEnemy.h"
#include "tankEnemy.h"
#include "Gameoverscreen.h"
#include "map.h"

Map curMap;

char DrawGameScreen(int, int, bool, bool, Player, sf::RenderWindow*);
void playGameThread();

bool pauseScreen = false;


//Function to check if gun is out
bool checkGunOut()
{
	bool gunOut = false;
	if(UPpressed || DOWNpressed || LEFTpressed || RIGHTpressed)
	{
		gunOut = true;
	}
	return gunOut;
}

//Circle intercept function
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

void loadNextRoom()
{
	//Reset Some things, not sure?
	runningScreen = true;
	playGameThread();
}

void playGameThread()
{
	//initInventory();
	//initMap();
	//curMap.genMap();
	//generateFloor();
	int numRooms = Floor.size();
	for(int i = 0; i < numRooms; i++)
	{
		if(Floor[i].currentRoom)
		{
			curMap = Floor[i];
			mapPiece = curMap.pieces;
			if(curMap.cleared)
			{
				SlimeList.clear();
				TankList.clear();
			}
			else
			{
				SlimeList = curMap.SlimeEnemies;
				TankList = curMap.TankEnemies;
			}
		}
	}
	//FirstGun.setGun(500, 50, 150, 'R', 12, 0);
	//FirstGun.rarity = 'R';
	int index = 0;
	char whatToDo = 'G';
	while (runningScreen)
	{
		bool Firing = checkGunOut();
		index ++;
		runningScreen = mainChar.MoveCharacter();
		//If gameclock ready spawn new shot
		if(Firing)
		{
			FirstGun.FireWeapon();
		}
		if(Epressed && buttonClickTimer == 0)
		{
			buttonClickTimer = 1000;
			pauseScreen = true;
			while(pauseScreen)
			{
				
			}
			//Set Shotgun
			//FirstGun.setGun(100, 30, 75, 'S', 8, 5);
			//Set minigun
			//FirstGun.setGun(30, 5, 75, 'M', 5, 0);
		}
		else if(buttonClickTimer > 0)
		{
			buttonClickTimer -= 1;

		}
		else if(buttonClickTimer < 0)
		{
			buttonClickTimer = 0;
		}

		int NumProjectiles = AllProjectiles.size();
		vector<projectile> newVec{};
		vector<SlimeEnemy> slimeVec{};
		vector<tankEnemy> tankVec{};
		vector<DeadTank> deadTanks{};
		vector<DeadSlime> deadVec{};
		//Spawn New Enemies
		/*	
		if(gameclock%300 == 0)
		{
			tankEnemy FirstTank;
			FirstTank.spawnTank();
			TankList.push_back(FirstTank);
			SlimeEnemy FirstSlime;
			FirstSlime.spawnSlime();
			SlimeList.push_back(FirstSlime);
		}*/
		
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

				if(circleIntercept(slimeX, slimeY, slimeR, Pxpos, Pypos, Pradi))
				{
					SlimeList[i].hurtSlime(FirstGun.damage);
					AllProjectiles[j].Alive = false;
				}
			}
			if(circleIntercept(slimeX, slimeY, slimeR, mainChar.xpos, mainChar.ypos, 40))
			{
				mainChar.hurtPlayer(1);
			}
			if(SlimeList[i].health > 0)
			{
				slimeVec.push_back(SlimeList[i]);
			}
			else
			{
				int DropChance = 10;
				int roll100 = rand() % 100;
				if(roll100 < DropChance)
				{
					spawnRandomGun(slimeX, slimeY);
				}
			}
		}

		SlimeList = slimeVec;
		// Update Tanks
		int numTanks = TankList.size();
		for(int i = 0; i < numTanks; i++)
		{
			TankList[i].moveTank();
			tankEnemy CurTank = TankList[i];
			int TankR = CurTank.curRadius;
			int TankX = CurTank.xpos;
			int TankY = CurTank.ypos;
			for(int j = 0; j < NumProjectiles; j++)
			{
				int Pradi = AllProjectiles[j].radius;
				int Pxpos = AllProjectiles[j].xpos + Pradi;
				int Pypos = AllProjectiles[j].ypos + Pradi;

				if(circleIntercept(TankX, TankY, TankR, Pxpos, Pypos, Pradi))
				{
					TankList[i].hurtTank(FirstGun.damage);
					AllProjectiles[j].Alive = false;
				}
			}
			if(circleIntercept(TankX, TankY, TankR, mainChar.xpos, mainChar.ypos, 40))
			{
				mainChar.hurtPlayer(1);
			}
			if(TankList[i].health > 0)
			{
				tankVec.push_back(TankList[i]);
			}
			else
			{
				int DropChance = 10;
				int roll100 = rand() % 100;
				if(roll100 < DropChance)
				{
					spawnRandomGun(TankX, TankY);
				}
			}
		}
		TankList = tankVec;

		// Update bullet position
		for(int i = 0; i < NumProjectiles; i++)
		{
			bool survived = AllProjectiles[i].moveProjectile();
			if(survived && AllProjectiles[i].Alive)
			{
				newVec.push_back(AllProjectiles[i]);
			}
		}
		
		//Update dead
		int deads = DeadList.size();
		for(int i = 0; i < deads; i++)
		{
			DeadList[i].updateDead();
			if(DeadList[i].lifeSpan > 0)
			{
				deadVec.push_back(DeadList[i]);
			}	
		}
		int numDeadTanks = DeadTanks.size();
		for(int i = 0; i < numDeadTanks; i++)
		{
			DeadTanks[i].updateDead();
			if(DeadTanks[i].lifeSpan > 0)
			{
				deadTanks.push_back(DeadTanks[i]);
			}
		}
		

		//Update ground weapons
		vector<weapon> GroundWeaponsNew;
		int numWeps = GroundWeapons.size();
		for(int i = 0; i < numWeps; i++)
		{
			bool weaponAdded = false;
			if(circleIntercept(GroundWeapons[i].xpos, GroundWeapons[i].ypos, 30, mainChar.xpos, mainChar.ypos, 40))
			{
				weapon CurWep = GroundWeapons[i];
				weaponAdded = insertWeapon(CurWep);
			}
			if(!weaponAdded)
			{
				GroundWeaponsNew.push_back(GroundWeapons[i]);
			}	
		}
		
		//Update Enemy shots
		vector<enemyProjectile> newEnemyShots;
		int numEnemyShots = enemyShots.size();
		for(int i = 0; i < numEnemyShots; i++)
		{
			bool alive = enemyShots[i].moveProjectile();
			
			if(circleIntercept(enemyShots[i].xpos, enemyShots[i].ypos, enemyShots[i].radius, mainChar.xpos, mainChar.ypos, 40))
			{
				mainChar.hurtPlayer(1);

			}
			else if(alive)
			{
				newEnemyShots.push_back(enemyShots[i]);
			}

		}
		if(numTanks == 0 && numSlimes == 0)
		{
			curMap.openDoors();
		}

		GroundWeapons = GroundWeaponsNew;
		DeadList = deadVec;
		DeadTanks = deadTanks;
		AllProjectiles = newVec;
		enemyShots = newEnemyShots;
	
		//Check if moving onto nextRoom;
		int curx = mainChar.xpos;
		int cury = mainChar.ypos;
		if(curx > 1701)
		{
			whatToDo = 'R';
			runningScreen = false;
		}
		if(curx < 59)
		{
			whatToDo = 'L';
			runningScreen = false;
		}
		if(cury > 1701)
		{
			whatToDo = 'D';
			runningScreen = false;
		}
		if(cury < 59)
		{
			whatToDo = 'U';
			runningScreen = false;
		}

		unsigned int microsecond = 1000000;
		usleep(0.005*microsecond);
		gameclock+=1;
	}

	int mapx = curMap.xpos;
	int mapy = curMap.ypos;
	bool nextRoom = false;
	switch(whatToDo)
	{
		case 'R':
			{
				mapx = mapx+1;
				nextRoom = true;
				mainChar.xpos = 150;
				break;
			}
		case 'L':
			{
				mapx = mapx-1;
				mainChar.xpos = 1650;
				nextRoom = true;
				break;
			}
		case 'U':
			{
				mapy = mapy-1;
				nextRoom = true;
				mainChar.ypos = 1650;
				break;
			}
		case 'D':
			{
				mapy = mapy+1;
				nextRoom = true;
				mainChar.ypos = 150;
				break;
			}
		case 'Q':
			{
				runningGame = false;
				break;
			}
	}
	if(nextRoom)
	{
		int numRooms = Floor.size();
		for(int i = 0; i < numRooms; i++)
		{
			int curxx = Floor[i].xpos;
			int curyy = Floor[i].ypos;
			if(curxx == curMap.xpos && curyy == curMap.ypos)
			{
				Floor[i].cleared = true;
			}
			if(curxx == mapx && curyy == mapy)
			{
				Floor[i].currentRoom = true;
				Floor[i].discovered  = true;
				
			}
			else
			{
				Floor[i].currentRoom = false;
			}
		}
		loadNextRoom();
	}

}

void GameScreen(sf::RenderWindow* window)
{
	//Init values
	char next;
	mainChar.setInitValues(900, 900);
	//This thread handles the game stuff. Seperated them in order to have the game render quicker
	//	
	
	initInventory();
	generateFloor();
	FirstGun.setGun(500, 2, 150, 'R', 12, 0);
	FirstGun.rarity = 'R';	
	sf::Thread thread(&playGameThread);
	thread.launch();
	//This loop updates the screen and draws the picture.
	while(runningGame)
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

		next = DrawGameScreen(MouseX, MouseY, MouseReleased, MouseDown, mainChar, window);
		if(next != 's')
		{
			runningScreen = false;
		}

	}
	mainChar.curHealth = mainChar.maxHealth;

}

char DrawGameScreen(int mousex, int mousey, bool MouseReleased, bool MouseDown, Player mainChar, sf::RenderWindow* window)
{
	//Init variables, colours, etc.
	char outPut = 's';
	sf::Color backgroundColour {160, 160, 160};
	sf::Color black            {  0,   0  , 0};
	sf::Color white            {255, 255, 255};
	sf::Color minimap	   { 40,  40,  40, 180};
	
	//Clear the window before we draw
	window->clear();

	//Draw background
	sf::RectangleShape background(sf::Vector2f(1800.f, 1800.f));
	background.setPosition(0, 0);
	background.setFillColor(backgroundColour);
	window->draw(background);
	
	//Draw ground weapons
	int numWeapons = GroundWeapons.size();
	for(int i = 0; i < numWeapons; i++)
	{
		GroundWeapons[i].drawGroundWeapon(window);
	}

	//Draw Player Bullets
	int numShots = AllProjectiles.size();
	for(int i = 0; i < numShots; i++)
	{
		AllProjectiles[i].drawProjectile(window);
	}

	//Draw Dead slimes
	int numDead = DeadList.size();
	for(int i = 0; i < numDead; i++)
	{
		DeadList[i].drawDead(window);
	}

	//Draw Dead Tanks
	int numDeadTanks = DeadTanks.size();
	for(int i = 0; i < numDeadTanks; i++)
	{
		DeadTanks[i].drawDead(window);
	}

	//Draw Enemy Shots
	int numEnemyShots = enemyShots.size();
	for(int i = 0; i < numEnemyShots; i++)
	{
		enemyShots[i].drawProjectile(window);
	}
		
	//Draw Slimes
	int numSlimes = SlimeList.size();
	for(int i = 0; i < numSlimes; i++)
	{
		SlimeList[i].drawSlime(window);
	}
	
	//Draw Tanks
	int numTanks = TankList.size();
	for(int i = 0; i < numTanks; i++)
	{
		TankList[i].drawTank(window);
	}

	//Draw Walls
	int numObsts = mapPiece.size();
	for(int i = 0; i < numObsts; i++)
	{
		mapPiece[i].drawObstacle(window);
	}

	//Draw outline and inline?
	sf::RectangleShape flatLine(sf::Vector2f(1800.f, 2.f));
	flatLine.setPosition(0, 0);
	flatLine.setFillColor(white);
	window->draw(flatLine);
	flatLine.setPosition(0, 1800);
	window->draw(flatLine);
	sf::RectangleShape innerLine(sf::Vector2f(1600.f, 2.f));
	innerLine.setPosition(100, 100);
	innerLine.setFillColor(white);
	window->draw(innerLine);
	innerLine.setPosition(100, 1700);
	window->draw(innerLine);

	sf::RectangleShape downLine(sf::Vector2f(2.f, 1800.f));
	downLine.setPosition(0, 0);
	downLine.setFillColor(white);
	window->draw(downLine);
	downLine.setPosition(1800, 0);
	window->draw(downLine);
	sf::RectangleShape smallLine(sf::Vector2f(2.f, 1600.f));
	smallLine.setPosition(100, 100);
	smallLine.setFillColor(white);
	window->draw(smallLine);
	smallLine.setPosition(1700, 100);
	window->draw(smallLine);

	//Draw Player
	mainChar.drawPlayer(window);
	
	if(pauseScreen)
	{
		pauseScreen = drawPauseScreen(mousex, mousey, MouseReleased, MouseDown, window);
	}

	//Draw Minimap
	sf::RectangleShape minimap1(sf::Vector2f(250.f, 250.f));
	minimap1.setPosition(1400, 150);
	minimap1.setFillColor(minimap);
	minimap1.setOutlineColor(black);
	minimap1.setOutlineThickness(2);
	window->draw(minimap1);
	int discRooms = Floor.size();
	int curMapX;
	int curMapY;
	for(int i = 0; i < discRooms; i++)
	{
		Map curRoom = Floor[i];
		if(curRoom.currentRoom)
		{
			curMapX = curRoom.xpos;
			curMapY = curRoom.ypos;
			break;
		}
	}
	for(int i = 0; i < discRooms; i++)
	{
		Map curRoom = Floor[i];
		int xdistance = abs(curMapX - curRoom.xpos);
		int ydistance = abs(curMapY - curRoom.ypos);
		
		if(xdistance < 3 && ydistance < 3)
		{
			sf::RectangleShape room(sf::Vector2f(48.f, 48.f));
			sf::Color sideRoom  {80, 80, 80};
			if(curRoom.currentRoom)
			{
				sideRoom = {200, 200, 200};
			}
			else if(curRoom.cleared)
			{
				sideRoom = {150, 150, 150};
			}
			room.setPosition(1500+50*(curRoom.xpos-curMapX), 250+50*(curRoom.ypos-curMapY));
			room.setFillColor(sideRoom);
			room.setOutlineColor(white);
			room.setOutlineThickness(2);
			window->draw(room);
		}
	}
	//Display screen
	window->display();
	window->clear();
	
	//exit function
	return outPut;
}


