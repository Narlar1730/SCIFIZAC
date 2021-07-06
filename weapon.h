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

sf::Color colourSelector(char Choice)
{
	sf::Color UnderGlow 	{  255, 255, 255, 0};
	switch(Choice)
		{
			case 'R':
				{
					UnderGlow = {255,   0,   0,   5};
					break;
				}
			case 'O':
				{
					UnderGlow = {255, 165,   0,   5};
					break;
				}
			case 'Y':
				{
					UnderGlow = {255, 255,   0,  5};
					break;
				}
			case 'G':
				{
					UnderGlow = {  0,  255,  0,  5};
					break;
				}
			case 'B':
				{
					UnderGlow = {  0,   0, 255,  5};
					break;
				}
			case 'I':
				{
					UnderGlow = { 75,   0, 130,  5};
					break;
				}
			case 'V':
				{
					UnderGlow = {248, 130, 238,  5};
					break;
				}
		}
	return UnderGlow;

}

sf::Color incColourSelector(int inc)
{
	sf::Color output {100, 100, 100};
	char selector = 'V';
	if(inc == 0)
	{
		selector = 'R';
	}
	else if(inc == 1)
	{
		selector = 'O';
	}
	else if(inc == 2)
	{
		selector = 'Y';
	}
	else if(inc == 3)
	{
		selector = 'G';
	}
	else if(inc == 4)
	{
		selector = 'B';
	}
	else if(inc == 5)
	{
		selector = 'I';
	}
	else if(inc == 6)
	{
		selector = 'V';
	}
	output = colourSelector(selector);
	return output;
}

void weapon::drawGroundWeapon(sf::RenderWindow* window)
{
	sf::Color GunGrey  	{100, 100, 100};
	sf::Color bandGrey 	{ 80,  80,  80};
	sf::Color black    	{  0,   0,   0};
	sf::Color handleBrown   { 87,  65,  47};
	//rarity = 'R';
	sf::Color UnderGlow = colourSelector(rarity);

	//Here we draw the underglow to show the rarity of the weapon. Its in roygbiv order for now. And I think I will keep it that way because I like it
	//U rarity unique = rainbow
	int glowRad = 50;
	if(rarity == 'U')
	{
		int inc = gameclock % 210;
		int selector = 0;
		selector = selector + inc/30;
		UnderGlow = incColourSelector(selector);
		for(int i = 0; i < 10; i ++)
		{
			sf::CircleShape circle;
			circle.setRadius(glowRad);
			circle.setFillColor(UnderGlow);
			circle.setPosition(xpos+i*3, ypos+i*3);
			glowRad = glowRad - 3;
			window->draw(circle);
			sf::Color additive {0, 0, 0, 5};
			UnderGlow = UnderGlow + additive;
			selector += 1;
		}		
	}
	else
	{
		for(int i = 0; i < 10; i ++)
		{
			sf::CircleShape circle;
			circle.setRadius(glowRad);
			circle.setFillColor(UnderGlow);
			circle.setPosition(xpos+i*3, ypos+i*3);
			glowRad = glowRad - 3;
			window->draw(circle);
			sf::Color additive {0, 0, 0, 5};
			UnderGlow = UnderGlow + additive;
		}
	}

	//Here we draw the weapons
	switch(style)
	{
		case 'M':
			{
				int xOffset = 30;
				int yOffset = 30;
				for(int i = 0; i <3; i++)
				{
					sf::RectangleShape barrel(sf::Vector2f(60.f, 6.f));
					barrel.setPosition(xpos+xOffset, ypos+10*i+yOffset);
					barrel.setFillColor(GunGrey);
					barrel.setOutlineColor(black);
					barrel.setOutlineThickness(1);
					window->draw(barrel);
				}
				for(int i = 0; i < 2; i++)
				{
					sf::RectangleShape band(sf::Vector2f(4.f, 30.f));
					band.setPosition(xpos+10+i*35+xOffset, ypos-2+yOffset);
					band.setFillColor(bandGrey);
					band.setOutlineColor(black);
					band.setOutlineThickness(1);
					window->draw(band);
				}
				sf::RectangleShape box(sf::Vector2f(20.f, 40.f));
				box.setPosition(xpos-20+xOffset, ypos - 5+yOffset);
				box.setFillColor(bandGrey);
				box.setOutlineColor(black);
				box.setOutlineThickness(1);
				window->draw(box);

				sf::RectangleShape handle(sf::Vector2f(4.f, 16.f));
				handle.setPosition(xpos-12+xOffset, ypos + 8+yOffset);
				handle.setFillColor(black);
				handle.setOutlineColor(black);
				handle.setOutlineThickness(1);
				window->draw(handle);
				break;
			}
		case 'S':
			{
				int xOffset = 30;
				int yOffset = 30;
				
				sf::RectangleShape handle(sf::Vector2f(20.f, 8.f));
				handle.setPosition(xpos+xOffset+2, ypos+yOffset+10);
				handle.setFillColor(handleBrown);
				handle.setOutlineColor(black);
				handle.setOutlineThickness(1);
				handle.setRotation(135);
				window->draw(handle);

				
				sf::RectangleShape barrel(sf::Vector2f(60.f, 8.f));
				barrel.setPosition(xpos+xOffset, ypos+yOffset);
				barrel.setFillColor(GunGrey);
				barrel.setOutlineColor(black);
				barrel.setOutlineThickness(1);
				window->draw(barrel);
				
				sf::RectangleShape band(sf::Vector2f(20.f, 6.f));
				band.setPosition(xpos+xOffset+15, ypos+yOffset+5);
				band.setFillColor(GunGrey);
				band.setOutlineColor(black);
				band.setOutlineThickness(1);
				window->draw(band);
				
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
					int offset = rand() % 3 - 1;
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
						Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos, xVelo-offset, yVelo+offset, bulletSize, range);
					}
					else
					{
						Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos, xVelo+offset, yVelo-offset, bulletSize, range);
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
