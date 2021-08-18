/*
 *This header file contains all the stuff for the slime enemy. 
 * 
 * We have the class, slime Enemy, and the vector, SlimeList which contains all the slimes
 */
vector<SlimeEnemy> SlimeList;
vector<DeadSlime> DeadList;

void DeadSlime::drawDead(sf::RenderWindow* window)
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

void DeadSlime::updateDead()
{
	lifeSpan = lifeSpan - 1;
}

void DeadSlime::spawnDead(int x, int y, int rad, int life)
{
	xpos = x;
	ypos = y;
	radius = rad;
	lifeSpan = life;
}

bool SlimeEnemy::hurtSlime(int damage)
{
	bool Alive = true;
	//Maybe implement crits?
	health -= damage;

	if(health < 0)
	{
		Alive = false;
		DeadSlime newSlime;
		newSlime.spawnDead(xpos, ypos, curRadius, 20);
		DeadList.push_back(newSlime);
	}

	hitCounter = 50;

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

	xVel = rand() % 7 - 3;
	yVel = rand() % 7 - 3;

	vector<int> vels = velocityFix(xVel, yVel, 3);
	
	xVel = vels[0];
	yVel = vels[1];

	curRadius = rand() % 30 + 20;
	init_size = curRadius;

	hitCounter = 0;
}

bool OverlapRectangles(int R1X1, int R1Y1, int R2X1, int R2Y1, int R1X2, int R1Y2, int R2X2, int R2Y2)
{
	bool output = true;

	if (R1X1 >= R2X2 || R2X1 >= R1X2)
	{
		output = false;
	}
	if(R1Y1 >= R2Y2 || R2Y1 >= R1Y2)
	{
		output = false;
	}

	return output;
}

void SlimeEnemy::moveSlime()
{
	//Move slimear
	//
	//Angle betwen slime and player = theta	
	
	//theta = atan((static_cast<double>(ypos) - static_cast<double>(yDir))/(static_cast<double>(xpos) - static_cast<double>(xDir)));

	if(gameclock % 4 == 0)
	{
		int numObsts = mapPiece.size();
		for(int i = 0; i < numObsts; i++)
		{
			obstacle curObst = mapPiece[i];
			int rectX1 = curObst.xpos-10;
			int rectY1 = curObst.ypos-10;
			int size = 120;
			int rectX2 = rectX1 + size;
			int rectY2 = rectY1 + size;

			int xpos2 = xpos + 2*init_size;
			int ypos2 = ypos + 2*init_size;

			bool overlap = OverlapRectangles(rectX1, rectY1, xpos, ypos, rectX2, rectY2, xpos2, ypos2);
			
			if(overlap){
				if(rectX1+1 <= xpos2 || xpos <= rectX2)
				{
					xVel = xVel*-1;
					xpos += xVel;
				}
				if(rectY1+1 <= ypos2 || ypos <= rectY2)
				{
					yVel = yVel*-1;
					ypos += yVel;
				}
				
			}
				

		}
		//perform collisions

		//cout xpos
		/*cout << "xpos: " << xpos << " ypos: " << ypos << "\n";
		cout << "xvel: " << xVel << " yVel: " << yVel << "\n";
		cout << "-------------------------\n";*/
		xpos += xVel;
		ypos += yVel;
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
	slime.setFillColor(sf::Color(rHurt, gHurt, bHurt));
	
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
