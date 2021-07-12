class obstacle{
	public:
		int xpos, ypos;
		char type;
		void drawObstacle(sf::RenderWindow* window);
};

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
		case 'W':
			{
				sf::Color black {  0,   0,   0};
				sf::Color white {255, 255, 255};
				sf::Color brown { 77,  31,  10};

				sf::RectangleShape wall(sf::Vector2f(100.f, 100.f));
				wall.setPosition(xpos, ypos);
				wall.setFillColor(brown);
				wall.setOutlineColor(white);
				wall.setOutlineThickness(2);
				window->draw(wall);
			}
	}
}
