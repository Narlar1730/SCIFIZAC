/*
 *This header file contains all the stuff for the tank enemy. 
 * 
 * We have the class, tank Enemy, and the vector, tankList which contains all the tanks
 */
class tankEnemy {
	public:
		int xpos, ypos, curRadius, init_size, r, g, b;
		int hitCounter = 0;
		int health = init_size*50;
		int countdownReset = 160; 
		int countdown = countdownReset;
		int speed = 5;
		bool growing;
		void spawnTank();
		bool hurtTank(int);
		void spawnTank(int, int);
		void drawTank(sf::RenderWindow*);
		void moveTank();
		void fireTank();

};

class DeadTank {
	public:
	        int xpos, ypos, radius, lifeSpan;
	        void spawnDead(int, int, int, int);
		void updateDead();
		void drawDead(sf::RenderWindow*);	       
};

class enemyProjectile {
	public:
		int xSpeed, ySpeed, xpos, ypos, radius, life, colour;
		int maxSpeed = 5;
		void spawnProjectile(int, int, int, int, int, int);
		void drawProjectile(sf::RenderWindow*);
		bool moveProjectile();
		bool Alive;
};

vector<enemyProjectile> enemyShots;

void enemyProjectile::spawnProjectile(int xPos, int yPos, int xVel, int yVel, int radii, int lifespan)
{
	Alive = true;
	xVel = xVel;
	yVel = yVel;

	xpos = xPos;
	ypos = yPos;

	xSpeed = xVel;
	ySpeed = yVel;

	life = lifespan;
	radius = radii;
}

bool enemyProjectile::moveProjectile()
{
	bool survived = true;
	xpos = xpos+xSpeed;
	ypos = ypos+ySpeed;
	life = life - 1;
	if(life == 0)
	{
		survived = false;
		Alive = false;
	}
	return survived;
}

void enemyProjectile::drawProjectile(sf::RenderWindow* window)
{
	sf::Color bulletColour {100, 100, 180};
	sf::Color outline      {120, 120, 200};

	sf::CircleShape bullet;
	bullet.setRadius(radius);
	bullet.setFillColor(bulletColour);
	bullet.setOutlineColor(outline);
	bullet.setPosition(xpos, ypos);
	window->draw(bullet);
}

vector<tankEnemy> TankList;
vector<DeadTank> DeadTanks;

void DeadTank::drawDead(sf::RenderWindow* window)
{
	int xcent = xpos + radius;
	int ycent = ypos + radius;

	for(int i = 0; i < 8; i++)
	{
		sf::RectangleShape rectangle(sf::Vector2f(5.f, 20.f));
		rectangle.setFillColor(sf::Color(255, 0, 0));
		rectangle.setPosition(xcent, ycent);
		rectangle.setRotation(360-45*i);
		window->draw(rectangle);
	}
}

void DeadTank::updateDead()
{
	lifeSpan = lifeSpan - 1;
}

void DeadTank::spawnDead(int x, int y, int rad, int life)
{
	xpos = x;
	ypos = y;
	radius = rad;
	lifeSpan = life;
}

void tankEnemy::fireTank()
{
	enemyProjectile bullet;
	//TODO
	float angle = (atan((static_cast<float>(mainChar.ypos)-static_cast<float>(ypos))/(static_cast<float>(mainChar.xpos) - static_cast<float>(xpos))));
	
	if(mainChar.xpos < xpos)
	{
		angle = angle - 3.141592653589793238463;
	}

	int xVel = static_cast<int>(bullet.maxSpeed*cos(angle));
	int yVel = static_cast<int>(bullet.maxSpeed*sin(angle));

	bullet.spawnProjectile(xpos, ypos, xVel, yVel, 12, 250);
	enemyShots.push_back(bullet);
	countdown = countdownReset;
}

bool tankEnemy::hurtTank(int damage)
{
	bool Alive = true;
	//Maybe implement crits?
	health -= damage;

	if(health < 0)
	{
		Alive = false;
		DeadTank newTank;
		newTank.spawnDead(xpos, ypos, curRadius, 20);
		DeadTanks.push_back(newTank);
	}

	hitCounter = 50;

	return Alive;
}

void tankEnemy::spawnTank()
{
	int xSlime = rand() % 1800;
	int ySlime = rand() % 1800;
	int offset = rand() % 4;
	if(offset == 0)
	{
		xSlime = -20;
	}
	else if(offset == 1)
	{
		xSlime = 1820;
	}
	else if(offset == 2)
	{
		ySlime = -20;
	}
	else
	{
		ySlime = 1820;
	}

	tankEnemy::spawnTank(xSlime, ySlime);


}

void tankEnemy::spawnTank(int x, int y)
{
	r = rand() % 255;
	g = r;
	b = r;

	xpos = x;
	ypos = y;

	curRadius = rand() % 30 + 20;
	init_size = curRadius;

	hitCounter = 0;
}

void tankEnemy::moveTank()
{
	int xDir = mainChar.xpos;
	int yDir = mainChar.ypos;
	//Move slimear
	//
	//Angle betwen slime and player = theta	
	double theta = 0;
		
	int distance = sqrt((xDir - xpos)*(xDir -xpos) +(yDir - ypos)*(yDir-ypos));



	theta = atan((static_cast<double>(ypos) - static_cast<double>(yDir))/(static_cast<double>(xpos) - static_cast<double>(xDir)));

	if(hitCounter == 0 && gameclock % 6 == 0 && distance > 600)
	{	
		int yVelo = abs(static_cast<int>(3*sin(theta)));
		int xVelo = abs(static_cast<int>(3*cos(theta)));
		if(xDir > xpos) 
		{
			xpos += xVelo;
		}
		else if(xDir < xpos)
		{
			xpos -= xVelo;
		}
		if(yDir > ypos)
		{
			ypos += yVelo;
		}
		else if(yDir < ypos)
		{
			ypos -= yVelo;
		}
	}
	else if(gameclock % 6 == 0 && hitCounter > 0)
	{
		int yVelo = abs(static_cast<int>(3*sin(theta)));
		int xVelo = abs(static_cast<int>(3*cos(theta)));
		if(xDir > xpos) 
		{
			xpos -= 2*xVelo;
		}
		else if(xDir < xpos)
		{
			xpos += 2*xVelo;
		}
		if(yDir > ypos)
		{
			ypos -= 2*yVelo;
		}
		else if(yDir < 2*ypos)
		{
			ypos += 2*yVelo;
		}
		hitCounter -= 2;

	}
	
	if(distance <= 600 && countdown == 0)
	{
		fireTank();
	}
	else if(distance <= 600)
	{
		countdown = countdown - 1;
	}
	else
	{
		countdown = countdownReset;
	}

}

void tankEnemy::drawTank(sf::RenderWindow* window)
{
	sf::Color barrelGrey { 60,  60,  60};
	sf::Color black      {  0,   0,   0};
	//Draw bottom of tank
	sf::CircleShape tank;
	tank.setRadius(curRadius);
	int rHurt = r+hitCounter;
	int gHurt = g-hitCounter;
	int bHurt = b-hitCounter;
	if(gHurt < 0)
	{
		gHurt = 0;
	}
	if(bHurt < 0)
	{
		bHurt = 0;
	}

	if(rHurt > 255)
	{
		rHurt = 255;	
	}
	tank.setFillColor(sf::Color(rHurt, gHurt, bHurt));
	
	int rO = r + 20;
	int gO = g + 20;
       	int bO = b + 20;
	if(rO > 255)
	{
		rO = 255;
	}	
	if(gO > 255)
	{
		gO = 255;
	}
	if(bO > 255)
	{
		bO = 255;
	}

	tank.setOutlineColor(sf::Color(rO, gO, bO));
	tank.setOutlineThickness(4);
	tank.setPosition(xpos, ypos);
	window->draw(tank);
	
	//angle between player and tank
	float angle = (atan((static_cast<float>(mainChar.ypos)-static_cast<float>(ypos))/(static_cast<float>(mainChar.xpos) - static_cast<float>(xpos)))) * (180.0/3.141592653589793238463);
	if(mainChar.xpos < xpos)
	{
		angle = angle-180;
	}
	//Draw barrel
	sf::RectangleShape barrel(sf::Vector2f(static_cast<float>(curRadius*1.5), 10.f));
	barrel.setPosition(xpos+curRadius-5, ypos+curRadius-5);
	barrel.setFillColor(barrelGrey);
	barrel.setOutlineColor(black);
	barrel.setOutlineThickness(2);
	barrel.setRotation(angle);
	window->draw(barrel);

}
