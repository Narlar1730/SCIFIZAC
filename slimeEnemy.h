class SlimeEnemy {
	public:
		int xpos, ypos, curRadius, init_size, r, g, b, hitCounter;
		int health = init_size*10;
		int speed = 10;
		bool growing;
		void spawnSlime();
		bool hurtSlime(int);
		void spawnSlime(int, int);
		void drawSlime(sf::RenderWindow*);
		void moveSlime();
};

vector<SlimeEnemy> SlimeList;

bool SlimeEnemy::hurtSlime(int damage)
{
	bool Alive = true;
	//Maybe implement crits?
	health -= damage;

	if(health < 0)
	{
		Alive = false;
	}

	hitCounter = 20;

	return Alive;
}

void SlimeEnemy::spawnSlime()
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

	SlimeEnemy::spawnSlime(xSlime, ySlime);


}

void SlimeEnemy::spawnSlime(int x, int y)
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

void SlimeEnemy::moveSlime()
{
	int xDir = mainChar.xpos;
	int yDir = mainChar.ypos;
	//Move slime
	
	if(hitCounter == 0)
	{
		if(xDir > xpos)
		{
			xpos += 1;
		}
		else
		{
			xpos -= 1;
		}
		if(yDir > ypos)
		{
			ypos += 1;
		}
		else
		{
			ypos -= 1;
		}
	}
	else
	{
		if(xDir > xpos)
		{
			xpos -= 1;
		}
		else
		{
			xpos += 1;
		}
		if(yDir > ypos)
		{
			ypos -= 1;
		}
		else
		{
			ypos += 1;
		}
		hitCounter -= 1;
	}


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

void SlimeEnemy::drawSlime(sf::RenderWindow* window)
{
	sf::CircleShape slime;
	slime.setRadius(curRadius);
	slime.setFillColor(sf::Color(r, g, b));
	
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

}
