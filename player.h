//#include "keyBoardManagement.h"
//

class weapon {
	public:
		int damage, firerate, range, bulletSize, bulletSpeed, extra, xpos, ypos;
		string name;
		char style, rarity;
		void FireWeapon();
		void drawHeldWeapon(sf::RenderWindow*);
		void drawGroundWeapon(sf::RenderWindow*);
		void setGun(int, int, int, char, int, int);
		void drawStats(int, int, sf::RenderWindow*);
};

class Player {
	public:
		int xpos, ypos, xVel, yVel, firerate, maxHealth, curHealth, painBuffer;
		int speed = 20;
		int CurSel = -1;
		int inventorysize = 24;
		void hurtPlayer(int);
		void setInitValues(int, int);
		void drawPlayer(sf::RenderWindow*);
		bool MoveCharacter();
		vector<weapon> weaponInventory;
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

	//Draw healthbar.
	sf::RectangleShape backBar(sf::Vector2f(1600.f, 20.f));
	backBar.setPosition(100, 1700);
	backBar.setFillColor(GunGrey);
	backBar.setOutlineColor(black);
	backBar.setOutlineThickness(4);
	//Calculate length
	float healthLength = (static_cast<float>(curHealth) / static_cast<float>(maxHealth)) * 1592.f;	
	//cout << healthLength << "\n";
	sf::RectangleShape healthBar(sf::Vector2f(healthLength, 12.f));
	healthBar.setPosition(104, 1704);
	healthBar.setFillColor(red);


	//Draw objects in the right order
	window->draw(backBar);
	window->draw(healthBar);
	window->draw(circle);

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

