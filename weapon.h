#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>

using namespace std;

class weapon {
	int damage, firerate, range;

};

class projectile {
	int xSpeed, ySpeed, xpos, ypos, radius, life;
	public:
		void spawnProjectile(int, int, int, int, int, int);
		void drawProjectile(sf::RenderWindow*);
		void addSpeed(int, int);
		bool moveProjectile();
};

vector<projectile> AllProjectiles;

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
		ySpeed -= ySpeed;
	}
	else
	{
		ySpeed += ySpeed;
	}
}

void projectile::spawnProjectile(int xPos, int yPos, int xVel, int yVel, int radii, int lifespan)
{
	double totalVelocity = 0;
	int biggerVal;
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
