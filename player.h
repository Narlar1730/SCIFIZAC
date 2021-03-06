//#include "keyBoardManagement.h"
//

#include "item.h"

//Declaring gun
weapon FirstGun;

class Player {
	public:
		int xpos, ypos, xVel, yVel, firerate, maxHealth, curHealth, painBuffer;
		int speed = 20;
		int CurSel = -1;
		bool justClicked = false;
		int inventorysize = 24;
		void hurtPlayer(int);
		void setInitValues(int, int);
		void drawPlayer(sf::RenderWindow*);
		bool MoveCharacter();
		weapon EquippedGun;
};

void Player::hurtPlayer(int hurt)
{
	if(painBuffer <= 0)
	{
		curHealth = curHealth - hurt;
		painBuffer += 60;
	}

}

int divRootTwoToo(int Value)
{
	int retVal;
	double rootTwo = 1.414214;
	double retValDub = static_cast<double>(Value)/rootTwo;
	retVal = static_cast<int>(retValDub);

	return retVal;
}

void Player::setInitValues(int x, int y)
{
	xpos = x;
	ypos = y;
	xVel = 0;
	yVel = 0;
	firerate = 30;
	maxHealth = 10;
	curHealth = 10;
	painBuffer = 0;
}

void drawArmour(sf::RenderWindow* window, int xpos, int ypos, weapon head, weapon chest, weapon leggings, weapon boots)
{
	if(head.itemType == 'H')
	{
		drawWornHead(window, xpos, ypos, head);
	}
	if(chest.itemType == 'C')
	{
		drawWornChest(window, xpos, ypos, chest);
	}
	if(leggings.itemType == 'L')
	{
		drawWornLeggings(window, xpos, ypos, leggings);
	}
	if(boots.itemType == 'B')
	{
		drawWornBoots(window, xpos, ypos, boots);
	}
}

void Player::drawPlayer(sf::RenderWindow* window)
{
	//Draw Player
	//
	int r = 160+painBuffer*2;
	if(r > 255)
	{
		r = 255;
	}
	sf::Uint8 rColor = r;
	sf::Color PlayerColor {rColor, 160, 200};
	sf::Color black       {0,     0,   0};
	sf::Color GunGrey     {120, 120, 120};
	sf::Color red	      {255,   0,   0};
	sf::CircleShape circle;
	circle.setRadius(40);
	circle.setFillColor(PlayerColor);
	circle.setOutlineColor(black);
	circle.setOutlineThickness(4);
	circle.setPosition(xpos, ypos);


	//Draw gun
	//Gun doesn't point the way I like. Will come back to this later
	//
	EquippedGun.xpos = xpos;
	EquippedGun.ypos = ypos;
	EquippedGun.drawHeldWeapon(window);
	

	//FIXME
	//Draw healthbar.
	sf::RectangleShape backBar(sf::Vector2f(1500.f, 20.f));
	backBar.setPosition(150, 1650);
	backBar.setFillColor(GunGrey);
	backBar.setOutlineColor(black);
	backBar.setOutlineThickness(4);
	//Calculate length
	float healthLength = (static_cast<float>(curHealth) / static_cast<float>(maxHealth)) * 1492.f;	
	//cout << healthLength << "\n";
	sf::RectangleShape healthBar(sf::Vector2f(healthLength, 12.f));
	healthBar.setPosition(154, 1654);
	healthBar.setFillColor(red);


	//Draw objects in the right order
	window->draw(circle);
	
	drawArmour(window, xpos, ypos, inventory[30], inventory[31], inventory[32], inventory[33]);

	window->draw(backBar);
	window->draw(healthBar);

}

bool Player::MoveCharacter()
{
	bool gameRun = true;

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
	if(xVel*xVel == yVel*yVel)
	{
		xVel = divRootTwoToo(xVel);
		yVel = divRootTwoToo(yVel);
	}

		
	//Perform collisions
	int numObsts = mapPiece.size();
	for(int i = 0; i < numObsts; i++)
	{
		obstacle curObst = mapPiece[i];
		int rectX = curObst.xpos-50;
		int rectY = curObst.ypos-50;
		int size  = 120;
		
		int testx = xpos;
		int testy = ypos;

		bool checkLeft = false;
		bool checkRight = false;
		bool checkUp = false;
		bool checkDown = false;

		if(xpos+20 < rectX)
		{
			checkLeft = true;
			testx = rectX;
		}
		else if(xpos > rectX + size)
		{
			checkRight = true;
			testx = rectX + size;
		}

		if(ypos+20 < rectY)
		{
			checkUp = true;
			testy = rectY;
		}
		else if(ypos > rectY + size)
		{
			checkDown = true;
			testy = rectY+size;	
		}

		float distX = xpos - testx;
		float distY = ypos - testy;
		float distance = sqrt((distX*distX) + (distY*distY));
		if(distance <= 40)
		{
			if(checkLeft)
			{
				xpos = rectX - 40;
				if(xVel > 0)
				{
					xVel = 0;
				}

			}
			if(checkRight)
			{
				
				xpos = rectX + 160;
				if(xVel < 0)
				{
					xVel = 0;
				}
			}
			if(checkUp)
			{
				ypos = rectY- 40;
				if(yVel > 0)
				{
					yVel = 0;
				}
			}
			if(checkDown)
			{
				ypos = rectY + 160;
				if(yVel < 0)
				{
					yVel = 0;
				}
			}
		}
	}
	
	xpos = xpos + xVel;
	ypos = ypos + yVel;

	//Reduce pain buffer
	if(painBuffer <= 0)
	{
		painBuffer = 0;
	}
	else
	{
		painBuffer -= 1;
	}

	if(curHealth <= 0)
	{
		gameRun = false;
	}
	return gameRun;

}

