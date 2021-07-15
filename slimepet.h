weapon initSlimePet()
{
	weapon SlimePet;
	SlimePet.damage = 10;
	int random = rand() % 7;
	SlimePet.extra = random;
	SlimePet.bulletSize = 30;
	SlimePet.bulletSpeed = 0;
	SlimePet.itemType = 'P';
	SlimePet.style = 'S';
	SlimePet.rarity = 'U';
	SlimePet.xpos = mainChar.xpos - 80;
	SlimePet.ypos = mainChar.ypos;

	return SlimePet;
}

sf::Color switchColor(int value)
{
	sf::Color output {255, 255, 255, 160};
	switch(value)
	{
		case 0:
			output = {137, 207, 240, 160};
			break;
		case 1:
			output = {240, 137, 207, 160};
			break;
		case 2:
			output = {191, 227, 180, 160};
			break;
		case 3:
			output = {244, 113, 116, 160};
			break;
		case 4:
			output = {244, 241, 134, 160};
			break;
		case 5:
			output = {177, 156, 217, 160};
			break;
		case 6:
			output = {160, 166, 160, 160};
			break;
	}

	return output;
}

void weapon::moveSlimePet()
{
	int xDir = mainChar.xpos;
	int yDir = mainChar.ypos;
	double theta = atan((static_cast<double>(ypos) - static_cast<double>(yDir))/(static_cast<double>(xpos) - static_cast<double>(xDir)));

	int distance = sqrt((xDir-xpos)*(xDir-xpos) + (yDir-ypos)*(yDir-ypos));
	if(gameclock % 600 == 0 && !curMap.cleared)
	{
		bulletSpeed = 200;
		cout << "test\n";
	}
	if(bulletSpeed == 1)
	{
		bulletSpeed = 0;
		/*Bullet.spawnStationaryProjectile(xpos, ypos,  0,  3, 8, 120);
		AllProjectiles.push_back(Bullet);
		Bullet.spawnStationaryProjectile(xpos, ypos,  3,  0, 8, 120);
		AllProjectiles.push_back(Bullet);
		Bullet.spawnStationaryProjectile(xpos, ypos,  0, -3, 8, 120);
		AllProjectiles.push_back(Bullet);
		Bullet.spawnStationaryProjectile(xpos, ypos, -3,  0, 8, 120);
		AllProjectiles.push_back(Bullet);*/
		for(int i = -1; i < 2; i++)
		{
			for(int j = -1; j < 2; j++)
			{
				if(i != 0 || j != 0)
				{
					projectile bullet;
					bullet.spawnStationaryProjectile(xpos, ypos, i*3, j*3, 8, 120);
					AllProjectiles.push_back(bullet);
				}
			}
		}
		/*for(int i = 0; i < 8; i++)
		{
			
		}*/
		//FireShots
	}
	else if(bulletSpeed > 0)
	{
		bulletSpeed = bulletSpeed - 1;
	}
	else if(gameclock % 2 == 0 && distance > 100)
	{
		bulletSpeed = 0;
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
}


void weapon::drawSlimePet(sf::RenderWindow* window)
{

	int offset = 30;
	int radius = bulletSize;
	int dxpos   = xpos+offset;
	int dypos   = ypos+offset;

	sf::Color innerColor = switchColor(extra);
	//sf::Color innerBlue {137, 207, 240, 160};
	sf::Color outerBlue {101, 187, 210};
	sf::Color darkBlue  {  0,   0, 140};
	sf::CircleShape circle;
	circle.setRadius(radius);
	circle.setFillColor(innerColor);
	circle.setOutlineColor(outerBlue);
	circle.setOutlineThickness(4);
	circle.setPosition(dxpos, dypos);
	window->draw(circle);
	if(bulletSpeed == 0)
	{
		sf::CircleShape eye1;
		eye1.setRadius(6);
		eye1.setFillColor(darkBlue);
		eye1.setPosition(dxpos+10, dypos+10);
		window->draw(eye1);

		sf::CircleShape eye2;
		eye2.setRadius(6);
		eye2.setFillColor(darkBlue);
		eye2.setPosition(dxpos+40, dypos+10);
		window->draw(eye2);
	}
	else
	{
		sf::RectangleShape eye1(sf::Vector2f(10.f, 4.f));
		eye1.setFillColor(darkBlue);
		eye1.setPosition(dxpos+13, dypos+13);
		window->draw(eye1);

		sf::RectangleShape eye2(sf::Vector2f(10.f, 4.f));
		eye2.setFillColor(darkBlue);
		eye2.setPosition(dxpos+43, dypos+13);
		window->draw(eye2);
	}
}
