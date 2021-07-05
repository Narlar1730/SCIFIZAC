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
		int damage, firerate, range, bulletSize, bulletSpeed, extra, xpos, ypos;
		char style, rarity;
		void FireWeapon();
		void drawHeldWeapon(sf::RenderWindow*);
		void drawGroundWeapon(sf::RenderWindow*);
		void setGun(int, int, int, char, int, int);
};

class projectile {
	public: 
		int xSpeed, ySpeed, xpos, ypos, radius, life, maxSpeed;
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

//Ground Weapon List
vector<weapon> GroundWeapons;

// Set init Weapon
weapon FirstGun;

void weapon::drawGroundWeapon(sf::RenderWindow* window)
{
	sf::Color GunGrey  {100, 100, 100};
	sf::Color bandGrey { 80,  80,  80};
	sf::Color black    {  0,   0,   0};
	switch(style)
	{
		case 'M':
			{
				for(int i = 0; i <3; i++)
				{
					sf::RectangleShape barrel(sf::Vector2f(60.f, 6.f));
					barrel.setPosition(xpos, ypos+10*i);
					barrel.setFillColor(GunGrey);
					barrel.setOutlineColor(black);
					barrel.setOutlineThickness(1);
					window->draw(barrel);
				}
				for(int i = 0; i < 2; i++)
				{
					sf::RectangleShape band(sf::Vector2f(4.f, 30.f));
					band.setPosition(xpos+10+i*35, ypos-2);
					band.setFillColor(bandGrey);
					band.setOutlineColor(black);
					band.setOutlineThickness(1);
					window->draw(band);
				}
				break;
			}
	}
}

void weapon::setGun(int D, int FR, int R, char S, int BS, int N)
{
	damage = D;
	firerate = FR;
	range = R;
	style = S;
	bulletSize = BS;
	extra = N;

	bulletSpeed = 7;
}


void weapon::FireWeapon()
{
	if(gameclock % firerate == 0)
	{
		switch(style)
		{
			case 'R':
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
				Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos, xVelo, yVelo, bulletSize, range);
				AllProjectiles.push_back(Bullet);	
				break;
				}
			case 'M':
				{
				int xVelo = 0;
				int yVelo = 0;
				if(RIGHTpressed)
				{
					xVelo += 5;
				}
				else if(LEFTpressed)
				{
					xVelo -= 5;
				}
				else if(UPpressed)
				{
					yVelo -= 5;
				}
				else if(DOWNpressed)
				{
					yVelo += 5;
				}
				projectile Bullet;
				Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos, xVelo, yVelo, bulletSize, range);
				AllProjectiles.push_back(Bullet);
				break;
				}
			case 'S':
				{
				//double angleSep = 45/extra;
				int xVelo = 0;
				int yVelo = 0;
				bool yShift = false;
				bool xShift = false;
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
					xShift = true;
				}
				if(DOWNpressed)
				{
					yVelo += 5;
					xShift = true;
				}
				for(int i = 0; i < extra; i++)
				{
					int offset = rand() % extra - (extra/2);
					projectile Bullet;
					if(yShift && xShift)
					{
						int up = rand() % 2;
						if(up == 0)
						{
							Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos, xVelo, yVelo+2*offset, bulletSize, range);
						}
						else
						{
							Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos, xVelo+2*offset, yVelo, bulletSize, range);
						}
					}
					else if(yShift)
					{
						Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos, xVelo, yVelo+offset, bulletSize, range);
					}
					else
					{
						Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos, xVelo+offset, yVelo, bulletSize, range);
					}

					AllProjectiles.push_back(Bullet);
				}
				break;
				}
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

vector<int> velocityFix(int x, int y, int maxVel)
{

	vector<int> out = {};
	double xd = static_cast<double>(x);
	double yd = static_cast<double>(y);

	int o = maxVel*sin(atan(yd/xd));
	int a = maxVel*cos(atan(yd/xd));
	if(x > 0)
	{
		a = abs(a);
	}
	else if(x < 0 && a > 0)
	{
		a = -1*a;
	}
	if(y > 0)
	{
		o = abs(o);
	}
	else if(x < 0 && o > 0)
	{
		o = -1*o;
	}
	out.push_back(static_cast<int>(a));
	out.push_back(static_cast<int>(o));
	return out;
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

	maxSpeed = FirstGun.bulletSpeed;
	
	//Fixed stupid velocty on the stupid bullets
	//this required a lot of maths. ended up proving cos2(x) + sin2(x) = 1.  so that was fun
	vector<int> vels = velocityFix(xVel, yVel, maxSpeed);
	xVel = vels[0] + mainChar.xVel;
	yVel = vels[1] + mainChar.yVel;

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
