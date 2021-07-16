/*
 *This header file contains all the stuff for the slime enemy. 
 * 
 * We have the class, slime Enemy, and the vector, SlimeList which contains all the slimes
 */

vector<SlimeKing> SlimeKingList;
vector<DeadKingSlime> DeadKingList;

void DeadKingSlime::drawDead(sf::RenderWindow* window)
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

void DeadKingSlime::updateDead()
{
	lifeSpan = lifeSpan - 1;
}

void DeadKingSlime::spawnDead(int x, int y, int rad, int life)
{
	xpos = x;
	ypos = y;
	radius = rad;
	lifeSpan = life;
}

bool SlimeKing::hurtSlime(int damage)
{
	bool Alive = true;
	//Maybe implement crits?
	health -= damage;

	if(health < 0)
	{
		Alive = false;
		DeadKingSlime newSlime;
		newSlime.spawnDead(xpos, ypos, curRadius, 20);
		DeadKingList.push_back(newSlime);
	}

	hitCounter = 50;

	return Alive;
}

void SlimeKing::spawnSlime()
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

	SlimeKing::spawnSlime(xSlime, ySlime);


}

void SlimeKing::spawnSlime(int x, int y)
{
	r = rand() % 255;
	g = rand() % 255;
	b = rand() % 255;

	xpos = x;
	ypos = y;

	curRadius = rand() % 30 + 20;
	init_size = curRadius;

	hitCounter = 0;
}

void SlimeKing::moveSlime()
{
	int xDir = mainChar.xpos;
	int yDir = mainChar.ypos;
	//Move slimear
	//
	//Angle betwen slime and player = theta	
	double theta = 0;
	
	theta = atan((static_cast<double>(ypos) - static_cast<double>(yDir))/(static_cast<double>(xpos) - static_cast<double>(xDir)));

	if(attackCounter <= 0)
	{
		attackCounter = 1000;
	}
	
	if(attackCounter == 1)
	{
		for(int i = 0; i <2; i++)
		{
			for(int j = 0; j<2; j++)
			{
				SlimeEnemy slime;
				slime.spawnSlime(xpos-10+2*curRadius*i, ypos-10+2*curRadius*j);
				SlimeList.push_back(slime);
			}
		}

		for(int i = 0; i <2; i++)
		{
			for(int j = 0; j<2; j++)
			{
				SlimeEnemy slime;
				slime.spawnSlime(xpos+curRadius-10+curRadius*2*i, ypos+curRadius+10+curRadius*2*i);
				SlimeList.push_back(slime);
			}
		}
	}
	else if(attackCounter < 100)
	{
	
	}
	else if(gameclock%4==0)
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

	attackCounter -= 1;
	//Change size
	if(gameclock % 15 == 0)
	{
		if(curRadius == init_size)
		{
			int buffer = rand() % 2;
			if(buffer == 0)
			{
				growing = true;
				curRadius +=3;
			}
			else
			{
				growing = false;
				curRadius -=3;
			}
		}
		else if(curRadius > init_size+10)
		{
			curRadius -= 2;
			growing = false;
		}
		else if(curRadius < init_size-10)
		{
			curRadius +=2;
			growing = true;
		}
		else if(growing)
		{
			curRadius +=2;
		}
		else
		{
			curRadius -=2;
		}
	}
	//Change one rgb value
	int rgb = rand() % 3;
	int val = rand() % 10;
	int upOrDown = rand() % 2;
	if(gameclock % 15 == 0)
	{
		switch(rgb)
		{
			case 0:
				if(upOrDown == 0)
				{
					r -= val;
					if(r < 0)
					{
						r = 0;
					}
				}
				else
				{
					r += val;
					if(r > 255)
					{
						r = 255;
					}
				}
				break;
			case 1:
				if(upOrDown == 0)
				{
					g -= val;
					if(g < 0)
					{
						g = 0;
					}
				}
				else
				{
					g += val;
					if(g > 255)
					{
						g = 255;
					}
				}
				break;
			case 2:
				if(upOrDown == 0)
				{
					b -= val;
					if(b < 0)
					{
						b = 0;
					}
				}
				else
				{
					b += val;
					if(b > 255)
					{
						b = 255;
					}
				}
				break;
		}
	}
	
	
}

void SlimeKing::drawSlime(sf::RenderWindow* window)
{
	sf::CircleShape slime;
	sf::Color black {0, 0, 0};

	slime.setRadius(curRadius);
	int rHurt = r+2*hitCounter;
	int gHurt = g-2*hitCounter;
	int bHurt = b-2*hitCounter;
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

	sf::Color curColour = sf::Color(rHurt, gHurt, bHurt);
	slime.setFillColor(curColour);
	
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

	slime.setOutlineColor(sf::Color(rO, gO, bO));
	slime.setOutlineThickness(4);
	slime.setPosition(xpos, ypos);
	window->draw(slime);
	if(attackCounter < 100)
	{
		sf::RectangleShape eye1(sf::Vector2f(20.f, 6.f));
		eye1.setPosition(xpos+80, ypos+80);
		eye1.setFillColor(black);
		window->draw(eye1);

		sf::RectangleShape eye2(sf::Vector2f(20.f, 6.f));
		eye2.setPosition(xpos+240, ypos+80);
		eye2.setFillColor(black);
		window->draw(eye2);
	}
	else
	{			
		sf::CircleShape eye1;
		eye1.setRadius(15);
		eye1.setFillColor(sf::Color(0, 0, 0));
		//eye1.setFillColor(curColour - sf::Color(50, 50, 50));
		eye1.setPosition(xpos+80, ypos+80);
		window->draw(eye1);

		sf::CircleShape eye2;
		eye2.setRadius(15);
		eye2.setFillColor(sf::Color(0, 0, 0));
		eye2.setPosition(xpos+240, ypos+80);
		window->draw(eye2);
	}
	float healthBarWidth = (static_cast<float>(health) / 10000) * 400.f;

	sf::RectangleShape healthBak(sf::Vector2f(404.f, 8.f));
	sf::RectangleShape healthBar(sf::Vector2f(healthBarWidth, 4.f));
	healthBak.setPosition(xpos, ypos+420);
	healthBar.setPosition(xpos+2, ypos+422);
	healthBak.setFillColor(sf::Color(20, 20, 20));
	healthBar.setFillColor(sf::Color(255, 0 , 0));
	
	window->draw(healthBak);
	window->draw(healthBar);

}
