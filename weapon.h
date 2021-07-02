#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// Different weapons fire different style shots. ie. Shotgun, many short.
// Rifle, 1 long as it stands, this is what we have
// Shotgun - S
// Rifle - R
class weapon {
	public:
		int damage, firerate, range, bulletSize, bulletSpeed, extra;
		char style;
		void FireWeapon();
		void drawWeapon(sf::RenderWindow*);
		void setGun(int, int, int, char, int, int);
};

class projectile {
	public: 
		int xSpeed, ySpeed, xpos, ypos, radius, life;
		void spawnProjectile(int, int, int, int, int, int);
		void drawProjectile(sf::RenderWindow*);
		void addSpeed(int, int);
		bool moveProjectile();
		bool Alive;
		friend bool operator== (projectile lhs, projectile rhs);
		friend bool operator!= (projectile lhs, projectile rhs);
};


//Set Projectile List
vector<projectile> AllProjectiles;

// Set init Weapon
weapon FirstGun;
//FirstGun.setGun(100, 30, 150, 'R', 8, 'N');

/*
FirstGun.damage = 100;
FirstGun.firerate = 30;
FirstGun.range = 150;
FirstGun.style = 'R';
FirstGun.bulletSize = 8;
*/
void weapon::setGun(int D, int FR, int R, char S, int BS, int N)
{
	damage = D;
	firerate = FR;
	range = R;
	style = S;
	bulletSize = BS;
	extra = N;
}


void weapon::FireWeapon()
{
	if(gameclock % firerate == 0)
	{
		switch(style)
		{
			case 'R':
				if(true)
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
					Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos, mainChar.xVel+xVelo, mainChar.yVel+yVelo, bulletSize, range);
					//Bullet.addSpeed(5, 5);
					AllProjectiles.push_back(Bullet);
				}

				break;
			case 'S':
				//double angleSep = 45/extra;
				int xVelo = 0;
				int yVelo = 0;
				bool yShift = false;
				if(RIGHTpressed)
				{
					xVelo += 5;
					yShift = true;
				}
				if(LEFTpressed)
				{
					xVelo -= 5;
					yShift = true;
				}
				if(UPpressed)
				{
					yVelo -= 5;
				}
				if(DOWNpressed)
				{
					yVelo += 5;
				}
				for(int i = 0; i < extra; i++)
				{
					int offset = rand() % extra - (extra/2);
					projectile Bullet;
					if(yShift)
					{
						Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos, mainChar.xVel+xVelo, mainChar.yVel+yVelo+offset, bulletSize, range);
					}
					else
					{
						Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos, mainChar.xVel+xVelo+offset, mainChar.yVel+yVelo, bulletSize, range);
					}

					AllProjectiles.push_back(Bullet);
				}
				break;
		}
	}
}

bool operator!= (projectile lhs, projectile rhs)
{
	bool output = true;
	if(lhs == rhs)
	{
		output = false;
	}
	return output;
}

bool operator== (projectile lhs, projectile rhs)
{
	bool output = true;
	//cout << "Checking projectile equality\n";
	if(lhs.xSpeed != rhs.xSpeed)
	{
		output = false;
	}
	if(lhs.ySpeed != rhs.xSpeed)
	{
		output = false;
	}
	if(lhs.xpos != rhs.xpos)
	{
		output = false;
	}
	if(lhs.ypos != rhs.ypos)
	{
		output = false;
	}
	if(lhs.radius != rhs.radius)
	{
		output = false;
	}
	if(lhs.life != rhs.life)
	{
		output = false;
	}
	return output;
}

void projectile::addSpeed(int xVel, int yVel)
{
	if(xSpeed < 0)
	{
		xSpeed -= xVel;
	}
	else
	{
		xSpeed += xVel;
	}
	if(ySpeed < 0)
	{
		ySpeed -= yVel;
	}
	else
	{
		ySpeed += yVel;
	}
}

int divRootTwo(int Value)
{
	int retVal;
	double rootTwo   = 1.414214;
	double retValDub = static_cast<double>(Value)/rootTwo;

	retVal = static_cast<int>(retValDub);

	return retVal;


}

void projectile::spawnProjectile(int xPos, int yPos, int xVel, int yVel, int radii, int lifespan)
{
	Alive = true;
	if(xVel > 0 && xVel < 5)
	{
		xVel = 5;
	}
	else if(xVel < 0 && xVel > -5)
	{
		xVel = -5;
	}
	if (yVel > 0 && yVel < 5)
	{
		yVel = 5;
	}
	else if(yVel < 0 && yVel > -5)
	{
		yVel = -5;
	}
	//FIXME
	//Velocity is too high. It is the same when the player points both up and left for example
	//V = sqrt(x*x +y*y)
	//This means bullets go faster on the diagonal
	//i can probably fix this? But thats why its fixme tagged.
	if(xVel*xVel == yVel*yVel)
	{
		xVel = divRootTwo(xVel);
		yVel = divRootTwo(yVel);
	}


	xpos = xPos+20;
	ypos = yPos+20;
	xSpeed = xVel;
	ySpeed = yVel;
	life = lifespan;
	radius = radii;
	//Add Projectile
}

bool projectile::moveProjectile()
{
	bool survived = true;
	xpos = xpos+xSpeed;
	ypos = ypos+ySpeed;
	life = life - 1;
	//Remove projectile if dead
	if(life == 0)
	{
		survived = false;
		Alive = false;
	}
	return survived;
}

void projectile::drawProjectile(sf::RenderWindow* window)
{
	sf::Color bulletColour {180, 100, 100};
	sf::Color black        {  0,   0,   0};

	sf::CircleShape bullet;
	bullet.setRadius(radius);
	bullet.setFillColor(bulletColour);
	bullet.setOutlineColor(black);
	bullet.setPosition(xpos, ypos);

	window->draw(bullet);
}
