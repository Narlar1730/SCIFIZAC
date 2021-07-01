//#include "keyBoardManagement.h"

class Player {
	public:
		int xpos, ypos, xVel, yVel, firerate;
		int speed = 20;

		void setInitValues(int, int);
		void drawPlayer(sf::RenderWindow*);
		void MoveCharacter();
};

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
	if(xVel*xVel == yVel*yVel)
	{
		xVel = divRootTwoToo(xVel);
		yVel = divRootTwo(yVel);
	}

	xpos = xpos + xVel;
	ypos = ypos + yVel;
	

}

