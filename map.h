class Map{
	public:
		vector<SlimeEnemy> SlimeEnemies;
		vector<tankEnemy>  TankEnemies;
		vector<obstacle>   pieces;
		sf::Color          background;
		sf::Color          complement;
		sf::Color          outlineCol;
		int                xpos, ypos;         // Room POS
		bool 		   discovered  = false; // Fog of war
		bool		   currentRoom = false;
		bool		   cleared     = false;	
		void               genRandMap();       // Generate Random Map
		void		   genSpecMap(char type);
		void		   openDoors();
};

vector<Map> Floor;

void Map::openDoors()
{
	int numTiles = pieces.size();
	vector<obstacle> output;
	for(int i = 0; i < numTiles; i++)
	{
		if(pieces[i].type != 'D')
		{
			output.push_back(pieces[i]);
		}
	}
	
	cleared = true;
	pieces = output;
	mapPiece = output;
}

void generateFloor()
{
	int NumRooms = 6+(rand()%5+1);
	Map initRoom;
	initRoom.xpos = 0;
	initRoom.ypos = 0;
	initRoom.discovered  = true;
	initRoom.currentRoom = true;
	initRoom.cleared     = true;
	initRoom.genSpecMap('O');
	Floor.push_back(initRoom);

	for(int i = -1; i < 2; i+=2)
	{
		Map curRoom;
		curRoom.xpos = i;
		curRoom.ypos = 0;
		curRoom.discovered = true;
		curRoom.genSpecMap('R');
		Floor.push_back(curRoom);

		Map curRoom2;
		curRoom2.xpos = 0;
		curRoom2.ypos = i;
		curRoom2.discovered = true;
		curRoom2.genSpecMap('R');
		Floor.push_back(curRoom2);
	}
		
}

void Map::genSpecMap(char type)
{

	for(int i = 0; i < 18; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			obstacle wall;
			wall.xpos = i*100;
			wall.ypos = j*1700;
			if(i != 8 && i != 9)
			{
				wall.type = 'W';
			}
			else
			{
				wall.type = 'D';
			}
			pieces.push_back(wall);
			wall.xpos = j*1700;
			wall.ypos = i*100;
			pieces.push_back(wall);
			
			
		}
	}


	switch(type)
	{
		case 'O':
			{
				break;
			}
		case 'R':
			{
				int numObst = rand() % 3 + 1;
				for(int i = 0; i < numObst; i++)
				{
					int rand1 = (rand()%14)*100 + 200;
					int rand2 = (rand()%14)*100 + 200;

					obstacle wall;
					wall.xpos = rand1;
					wall.ypos = rand2;
					wall.type = 'W';
					pieces.push_back(wall);
				}
				// Add slimes
				for(int i = 0; i < 2; i++)
				{
					for(int j = 0; j < 2; j++)
					{
						SlimeEnemy curslime;
						int radius = rand() % 30 + 20;
						int r      = rand() % 255;
						int g      = rand() % 255;
						int b      = rand() % 255;

						curslime.xpos      = 100 + i*1560;
						curslime.ypos      = 100 + j*1560;
						curslime.curRadius = radius;
						curslime.init_size = radius;
						curslime.r         = r;
						curslime.g         = g;
						curslime.b         = b;
						curslime.health    = 10*radius;
			
						SlimeEnemies.push_back(curslime);
				
					}
				}

				// Add tanks
				for(int i = 0; i < 3; i++)
				{
					for(int j = 0; j <3; j++)
					{
						if(i != j)
						{
							tankEnemy curTank;
							int radius = rand() % 20 + 40;
							int xpos   = 100 + i * 780;
							int ypos   = 100 + j * 780;
							int colour = rand() % 255;

							curTank.curRadius = radius;
							curTank.xpos      = xpos;
							curTank.ypos      = ypos;
							curTank.r         = colour;
							curTank.g         = colour;
							curTank.b         = colour;
				
							TankEnemies.push_back(curTank);
						}
					}
				}
			}				
	
	}
	
	//Set master lists
	SlimeList = SlimeEnemies;
	TankList  = TankEnemies;
	mapPiece  = pieces;

}

void Map::genRandMap()
{
	//Draw Random Map
	int numObst = rand() % 3 + 1;
	for(int i = 0; i < numObst; i++)
	{
		int rand1 = (rand()%14)*100 + 200;
		int rand2 = (rand()%14)*100 + 200;

		obstacle wall;
		wall.xpos = rand1;
		wall.ypos = rand2;
		wall.type = 'W';
		pieces.push_back(wall);
	}
	for(int i = 0; i < 18; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			obstacle wall;
			wall.xpos = i*100;
			wall.ypos = j*1700;
			wall.type = 'W';
			pieces.push_back(wall);

			wall.xpos = j*1700;
			wall.ypos = i*100;
			pieces.push_back(wall);
		}
	}
	
	// Add slimes
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			SlimeEnemy curslime;
			int radius = rand() % 30 + 20;
			int r      = rand() % 255;
			int g      = rand() % 255;
			int b      = rand() % 255;

			curslime.xpos      = 100 + i*1560;
			curslime.ypos      = 100 + j*1560;
			curslime.curRadius = radius;
			curslime.init_size = radius;
			curslime.r         = r;
			curslime.g         = g;
			curslime.b         = b;
			curslime.health    = 10*radius;

			SlimeEnemies.push_back(curslime);
			
		}
	}

	// Add tanks
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j <3; j++)
		{
			if(i != j)
			{
				tankEnemy curTank;
				int radius = rand() % 20 + 40;
				int xpos   = 100 + i * 780;
				int ypos   = 100 + j * 780;
				int colour = rand() % 255;

				curTank.curRadius = radius;
				curTank.xpos      = xpos;
				curTank.ypos      = ypos;
				curTank.r         = colour;
				curTank.g         = colour;
				curTank.b         = colour;
				
				TankEnemies.push_back(curTank);
			}
		}
	}

	//Set master lists
	SlimeList = SlimeEnemies;
	TankList  = TankEnemies;
	mapPiece  = pieces;


}
