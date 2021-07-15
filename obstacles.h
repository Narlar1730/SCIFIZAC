/*class obstacle{
	public:
		int xpos, ypos;
		char type;
		void drawObstacle(sf::RenderWindow* window);
		void drawObstacle(sf::RenderWindow* window, sf::Color, sf::Color, sf::Color);
};*/

vector<obstacle> mapPiece;

void initMap()
{
	int numObst = rand()%4;
	cout << numObst << "\n";
	for(int i = 0; i < numObst; i++)
	{
		int rand1 = (rand()%16)*100 + 100;
		int rand2 = (rand()%16)*100 + 100;
		obstacle wall;
		wall.xpos = rand1;
		wall.ypos = rand2;
		wall.type = 'W';
		mapPiece.push_back(wall);
	}

	for(int i = 0; i < 18; i++)
	{
		for(int j = 0; j < 2; j ++)
		{
			obstacle wall;
			wall.xpos = i*100;
			wall.ypos = j*1700;
			wall.type = 'W';
			mapPiece.push_back(wall);	

			wall.xpos = j*1700;
			wall.ypos = i*100;
			mapPiece.push_back(wall);
		}
	}

}

void obstacle::drawObstacle(sf::RenderWindow* window, sf::Color background, sf::Color complement, sf::Color outlineCol)
{
	switch(type)
	{
		case 'T':
			{
				int angle = 360;
				sf::Color green { 48, 183,   0};
				sf::Color brown { 77,  31,  10};
				sf::CircleShape trunk;
				trunk.setRadius(20);
				trunk.setPosition(xpos+25, ypos+25);
				trunk.setFillColor(brown);
				window->draw(trunk);
				for(int i = 0; i <20; i++)
				{
					sf::RectangleShape branch(sf::Vector2f(50.f, 4.f));
					branch.setPosition(xpos+50, ypos+50);
					branch.setFillColor(green);
					branch.setRotation(angle - 18*i);
					window->draw(branch);
				}
				break;
			}
		case 'W':
			{
				sf::Color black {  0,   0,   0};
				sf::Color white {255, 255, 255};
				sf::Color brown { 77,  31,  10};

				sf::RectangleShape wall(sf::Vector2f(100.f, 100.f));
				wall.setPosition(xpos, ypos);
				wall.setFillColor(background);
				wall.setOutlineColor(outlineCol);
				wall.setOutlineThickness(2);
				window->draw(wall);
			}
	}
}

void obstacle::drawObstacle(sf::RenderWindow* window)
{
	switch(type)
	{
		case 'T':
			{
				int angle = 360;
				sf::Color green { 48, 183,   0};
				sf::Color brown { 77,  31,  10};
				sf::CircleShape trunk;
				trunk.setRadius(20);
				trunk.setPosition(xpos+25, ypos+25);
				trunk.setFillColor(brown);
				window->draw(trunk);
				for(int i = 0; i <20; i++)
				{
					sf::RectangleShape branch(sf::Vector2f(50.f, 4.f));
					branch.setPosition(xpos+50, ypos+50);
					branch.setFillColor(green);
					branch.setRotation(angle - 18*i);
					window->draw(branch);
				}
				break;
			}
		case 'D':
			{
				sf::Color brown     {  77,  31,  10};
				sf::Color darkBrown { 101,  67,  33};
				sf::Color gold      { 255, 215,   0};

				sf::RectangleShape door(sf::Vector2f(100.f, 100.f));
				door.setPosition(xpos, ypos);
				door.setFillColor(brown);
				window->draw(door);
				sf::RectangleShape feature(sf::Vector2f(70.f, 70.f));
				feature.setPosition(xpos+15, ypos+15);
				feature.setFillColor(darkBrown);
				window->draw(feature);
				sf::CircleShape handle;
				handle.setRadius(6);
				handle.setPosition(xpos+1, ypos+47);
				window->draw(handle);
				break;
			}
		case 'W':
			{
				sf::Color black {  0,   0,   0};
				sf::Color white {255, 255, 255};
				sf::Color brown { 77,  31,  10};

				sf::RectangleShape wall(sf::Vector2f(100.f, 100.f));
				wall.setPosition(xpos, ypos);
				wall.setFillColor(brown);
				window->draw(wall);
				
				//Find mod
				int modulo = (ypos/100) % 2;
				if(modulo == 0)
				{
					//Cross lines
					sf::RectangleShape cement(sf::Vector2f(100.f, 2.f));
					cement.setPosition(xpos, ypos + 33);
					cement.setFillColor(white);
					window->draw(cement);
					cement.setPosition(xpos, ypos + 66);
					window->draw(cement);
					cement.setPosition(xpos, ypos);
					window->draw(cement);
					cement.setPosition(xpos, ypos+100);
					window->draw(cement);

					//Down lines
					sf::RectangleShape downLine(sf::Vector2f(2.f, 33.f));
					downLine.setPosition(xpos, ypos);
					downLine.setFillColor(white);
					window->draw(downLine);
					downLine.setPosition(xpos+100, ypos);
					window->draw(downLine);
					downLine.setPosition(xpos+50, ypos+33);
					window->draw(downLine);
					downLine.setPosition(xpos, ypos+66);
					window->draw(downLine);
					downLine.setPosition(xpos+100, ypos+66);
					window->draw(downLine);
				}
				else
				{
					//Cross lines
					sf::RectangleShape cement(sf::Vector2f(100.f, 2.f));
					cement.setPosition(xpos, ypos + 33);
					cement.setFillColor(white);
					window->draw(cement);
					cement.setPosition(xpos, ypos + 66);
					window->draw(cement);
					cement.setPosition(xpos, ypos);
					window->draw(cement);
					cement.setPosition(xpos, ypos+100);
					window->draw(cement);

					//Down lines
					sf::RectangleShape downLine(sf::Vector2f(2.f, 33.f));
					downLine.setFillColor(white);
					downLine.setPosition(xpos+50, ypos);
					window->draw(downLine);
					downLine.setPosition(xpos+100, ypos+33);
					window->draw(downLine);
					downLine.setPosition(xpos, ypos+33);
					window->draw(downLine);
					downLine.setPosition(xpos+50, ypos+66);
					window->draw(downLine);			
				}
			}
	}
}

