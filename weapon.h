#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <math.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class projectile {
	public: 
		int xSpeed, ySpeed, xpos, ypos, radius, life, maxSpeed, colour;
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

char intToRar(int val)
{
	char output = ' ';
	switch(val)
	{
		case 0:
			output = 'R';
			break;
		case 1:
			output = 'O';
			break;
		case 2:
			output = 'Y';
			break;
		case 3:
			output = 'G';
			break;
		case 4:
			output = 'B';
			break;
		case 5:
			output = 'I';
			break;
		case 6:
			output = 'V';
			break;
		case 7:
			output = 'U';
			break;
		default:
			output = ' ';
			break;	
	}
	return output;
}

void spawnRandomGun(int x, int y)
{
	weapon newGun;
	int DamMod = rand () % 10;
	int FRMod = rand () % 5;
	int type = rand() % 4 + 1;
	int RangeMod = rand() % 6;
	int SizeMod = rand() % 10;
	int extra = rand() % 5; 
	int xrand = x;
	int yrand = y;
	//TODO - rarity is currently random. Need to add extra features based on randomness. 
	int rarity = rand() % 100;
	char rar;
	if(rarity < 60)
	{
		rar = 'R';
	}
	else if(rarity < 75)
	{
		rar = 'O';
	}
	else if(rarity < 85)
	{
		rar = 'Y';
	}
	else if(rarity < 90)
	{
		rar = 'G';
	}
	else if(rarity < 94)
	{
		rar = 'B';
	}
	else if(rarity < 97)
	{
		rar = 'I';
	}
	else
	{
		rar = 'V';
	}
	//Set Rarity
	newGun.rarity = rar;
	//char rar = intToRar(rand() % 8);
	switch(type)
	{
		case 1:
			newGun.setGun(100-5*DamMod, 50-5*FRMod, 75-4*RangeMod, 'S', 21 - 2*SizeMod, 5);
			break;
		case 2:
			newGun.setGun(50-2*DamMod, 10-FRMod, 100-4*RangeMod, 'M', 10-SizeMod, extra);
			break;
		case 3:
			newGun.setGun(150-10*DamMod, 50-5*FRMod, 150-4*RangeMod, 'R', 21 - 2*SizeMod, 5);
			break;
		case 4:
			newGun.setGun(DamMod+1, 100+10*FRMod, 0, 'L', 11-SizeMod, extra);
			
						
	}

	newGun.xpos = xrand;
	newGun.ypos = yrand;
	GroundWeapons.push_back(newGun);


}


void spawnRandomGun()
{
	int xrand = rand() % 1600;
	int yrand = rand() % 1600;
	spawnRandomGun(xrand, yrand);	
}

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

sf::Color colourSelectorNoOpaque(char Choice)
{
	sf::Color output;
	switch(Choice)
		{
			case 'R':
				{
					output = {255,   0,   0};
					break;
				}
			case 'O':
				{
					output = {255, 165,   0};
					break;
				}
			case 'Y':
				{
					output = {255, 255,   0};
					break;
				}
			case 'G':
				{
					output = {  0,  255,  0};
					break;
				}
			case 'B':
				{
					output = {  0,   0, 255};
					break;
				}
			case 'I':
				{
					output = { 75,   0, 130};
					break;
				}
			case 'V':
				{
					output = {248, 130, 238};
					break;
				}
		}
	return output;


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

string charToRarity(char c)
{
	string output;
	switch(c)
	{
			case 'R':
				output = "Common";
				break;
			case 'O':
				output = "Uncommon";
				break;
			case 'Y':
				output = "Rare";
				break;
			case 'G':
				output = "Ultra rare";
				break;
			case 'B':
				output = "Legendary";
				break;
			case 'I':
				output = "Demonic";
				break;
			case 'V':
				output = "Godlike";
				break;

	}
	return output;
}

void weapon::drawStats(int x, int y, sf::RenderWindow* window)
{
	sf::Color backGroundGrey { 40,  40,  40, 200};
	sf::Color black          {  0,   0,   0};
	sf::Color white          {255, 255, 255};
	// Draw background
	sf::RectangleShape backBlock(sf::Vector2f(400.f, 600.f));
	backBlock.setFillColor(backGroundGrey);
	backBlock.setOutlineColor(black);
	backBlock.setOutlineThickness(2);
	backBlock.setPosition(x-430, y);
	window->draw(backBlock);

	// Draw Name
	sf::Text name1;
	name1.setFont(font);
	name1.setString(name);
	name1.setCharacterSize(30);
	name1.setFillColor(colourSelectorNoOpaque(rarity));
	name1.setPosition(x-410, y+10);
	window->draw(name1);

	// Display stats
	sf::Text Text1;
	Text1.setFont(font);
	Text1.setString("Damage: " + std::to_string(damage));
	Text1.setCharacterSize(30);
	Text1.setFillColor(white);
	Text1.setPosition(x-410, y+90);
	window->draw(Text1);

	sf::Text Text4;
	Text4.setFont(font);
	Text4.setString("Bullet size: " + std::to_string(bulletSize));
	Text4.setCharacterSize(30);
	Text4.setFillColor(white);
	Text4.setPosition(x-410, y+130);
	window->draw(Text4);

	sf::Text Text2;
	Text2.setFont(font);
	Text2.setString("Fire rate: " + std::to_string(firerate));
	Text2.setCharacterSize(30);
	Text2.setFillColor(white);
	Text2.setPosition(x-410, y+170);
	window->draw(Text2);

	sf::Text Text3;
	Text3.setFont(font);
	Text3.setString("Range: " + std::to_string(range));
	Text3.setCharacterSize(30);
	Text3.setFillColor(white);
	Text3.setPosition(x-410, y+210);
	window->draw(Text3);




}

void weapon::drawGroundWeapon(sf::RenderWindow* window)
{
	sf::Color GunGrey  	{100, 100, 100};
	sf::Color bandGrey 	{ 80,  80,  80};
	sf::Color black    	{  0,   0,   0};
	sf::Color handleBrown   { 87,  65,  47};
	sf::Color white         {255, 255, 255};
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
		case 'L':
			{
				int xOffset = 30;
				int yOffset = 30;

				for(int i = 0; i < 3; i++)
				{
					sf::RectangleShape nodule(sf::Vector2f(6.f, 8.f));
					nodule.setPosition(xpos+xOffset+10+8*i, ypos + yOffset);
					nodule.setFillColor(white);
					nodule.setOutlineColor(black);
					nodule.setOutlineThickness(1);
					window->draw(nodule);
				}
				
				sf::RectangleShape laser(sf::Vector2f(60.f, 8.f));
				laser.setPosition(xpos+xOffset+5, ypos+yOffset+2);
				sf::Color LaserColor = colourSelector((intToRar(extra % 7)));
				laser.setFillColor(LaserColor);
				window->draw(laser);
				

				sf::RectangleShape barrel(sf::Vector2f(60.f, 12.f));
				barrel.setPosition(xpos+xOffset, ypos+yOffset);
				barrel.setFillColor(black);
				window->draw(barrel);
				break;
			}
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
		case 'R':
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

				
				sf::RectangleShape barrel(sf::Vector2f(70.f, 6.f));
				barrel.setPosition(xpos+xOffset, ypos+yOffset);
				barrel.setFillColor(GunGrey);
				barrel.setOutlineColor(black);
				barrel.setOutlineThickness(1);
				window->draw(barrel);
				
				sf::RectangleShape scope(sf::Vector2f(20.f, 6.f));
				scope.setPosition(xpos+xOffset+15, ypos+yOffset-5);
				scope.setFillColor(GunGrey);
				scope.setOutlineColor(black);
				scope.setOutlineThickness(1);
				window->draw(scope);
				
				break;

			}
	}
}

string generateName(char style, char rarity)
{
	string output = charToRarity(rarity);
	string words[10] = {"pain", "suffering", "happiness", "thunder", "speed", "power", "fire", "love", "bullets", "damage"};
	switch(style)
	{
		case 'S':
			output += " shotgun of ";
			break;
		case 'R':
			output += " rifle of ";
			break;
		case 'M':
			output += " minigun of ";
			break;
		case 'L':
			output += " laser of ";
			break;
	}

	int index = rand() % 10;
	output += words[index];

	return output;
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

	name = generateName(S, rarity);
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
			case 'L':
				{
				int siz = bulletSize;
				int rang = 15;
				int FireSet = 20;
				if(RIGHTpressed)
				{
					for(int i = 0; i < 200; i++)
					{
						projectile Bullet;
						Bullet.spawnProjectile(mainChar.xpos+i*FireSet, mainChar.ypos, 0, 0, siz, rang);
						Bullet.colour=extra;
						AllProjectiles.push_back(Bullet);
					}
				}
				else if(LEFTpressed)
				{
					for(int i = 0; i < 200; i++)
					{
						projectile Bullet;
						Bullet.spawnProjectile(mainChar.xpos-i*FireSet, mainChar.ypos, 0, 0, siz, rang);
						Bullet.colour=extra;
						AllProjectiles.push_back(Bullet);
					}

				}
				else if(UPpressed)
				{
					for(int i = 0; i < 200; i++)
					{
						projectile Bullet;
						Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos-i*FireSet, 0, 0, siz, rang);
						Bullet.colour=extra;
						AllProjectiles.push_back(Bullet);
					}

				}
				else if(DOWNpressed)
				{
					for(int i = 0; i < 200; i++)
					{
						projectile Bullet;
						Bullet.spawnProjectile(mainChar.xpos, mainChar.ypos+i*FireSet, 0, 0, siz, rang);
						Bullet.colour=extra;
						AllProjectiles.push_back(Bullet);
					}

				}
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
	colour = -1;
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
	if(colour != -1)
	{
		bulletColour = colourSelector(intToRar(colour%7));
		bullet.setOutlineThickness(1);
	}
	bullet.setRadius(radius);
	bullet.setFillColor(bulletColour);
	bullet.setOutlineColor(black);
	bullet.setPosition(xpos, ypos);

	window->draw(bullet);
}
