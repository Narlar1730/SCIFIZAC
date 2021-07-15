/*class Map{
	public:
		vector<SlimeEnemy> SlimeEnemies;
		vector<tankEnemy>  TankEnemies;
		vector<SlimeKing>  KingEnemies;
		vector<obstacle>   pieces;
		sf::Color          background;
		sf::Color          complement;
		sf::Color          outlineCol;
		int                xpos, ypos;          // Room POS
		bool 		   discovered  = false; // Fog of war
		bool		   currentRoom = false;
		bool		   cleared     = false;	
		bool		   generated   = false;
		vector<char>       getSurroundingRooms();
		vector<char>	   getFreeSurroundingRooms();
		void               genRandMap();        // Generate Random Map
		void		   genSpecMap(char type);
		void		   openDoors();
};*/

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

vector<char> Map::getFreeSurroundingRooms()
{
	vector<char> all {'D', 'L', 'U', 'R'};
	vector<char> surrounding = getSurroundingRooms();
	int numAround = all.size();
	vector<char> out;
	for(int i = 0; i < numAround; i++)
	{
		char curVal = all[i];
		if(!count(surrounding.begin(), surrounding.end(), curVal))
		{
			out.push_back(curVal);
		}
	}
	return out;
}

vector<char> Map::getSurroundingRooms()
{
	vector<char> out;
	int numRooms = Floor.size();
	for(int i = 0; i < numRooms; i++)
	{
		Map curRoom = Floor[i];
		if(xpos - curRoom.xpos == -1 && ypos == curRoom.ypos)
		{
			out.push_back('R');
		}
		else if(xpos - curRoom.xpos == 1 && ypos == curRoom.ypos) 
		{
			out.push_back('L');		
		}
		else if(ypos - curRoom.ypos == -1 && xpos == curRoom.xpos)
		{
			out.push_back('D');
		}
		else if(ypos - curRoom.ypos == 1 && xpos == curRoom.xpos)
		{
			out.push_back('U');
		}
	}

	return out;
}

vector<Map> freeSlotRooms;

int numRoomsWithFreeSlots()
{
	freeSlotRooms.clear();
	int output = 0;
	int size   = Floor.size();
	for(int i = 0; i < size; i ++)
	{
		Map curRoom = Floor[i];
		vector<char> CurSur = curRoom.getSurroundingRooms();
		if(CurSur.size() < 4)
		{
			output += 1;
			freeSlotRooms.push_back(curRoom);
		}
	}

	return output;
	
}

void generateFloor()
{
	Floor.clear();
	int NumRooms = 6+(rand()%5+1);
	Map initRoom;
	initRoom.xpos = 0;
	initRoom.ypos = 0;
	initRoom.discovered  = true;
	initRoom.currentRoom = true;
	initRoom.cleared     = true;
	initRoom.generated   = true;
	//initRoom.genSpecMap('O');
	Floor.push_back(initRoom);

	for(int i = -1; i < 2; i+=2)
	{
		Map curRoom;
		Map curRoom2;
		curRoom.xpos  = i;
		curRoom2.xpos = 0;
		curRoom.ypos  = 0;
		curRoom2.ypos = i;
		Floor.push_back(curRoom);
		Floor.push_back(curRoom2);


	}
	
	for(int i = 0; i < NumRooms; i++)
	{
		Map curRoom;
		int numCurRooms = numRoomsWithFreeSlots();
		int whichRoom = rand() % numCurRooms;
		Map freeRoom = freeSlotRooms[whichRoom];
		//This makes sense that it is backwards
		vector<char> availableRooms = freeRoom.getFreeSurroundingRooms();
		int numFree = rand() % availableRooms.size();
		char direction = availableRooms[numFree];
		switch(direction)
		{
			case 'U':
				curRoom.xpos = freeRoom.xpos;
				curRoom.ypos = freeRoom.ypos-1;
				break;
			case 'D':
				curRoom.xpos = freeRoom.xpos;
				curRoom.ypos = freeRoom.ypos+1;
				break;
			case 'L':
				curRoom.xpos = freeRoom.xpos + 1;
				curRoom.ypos = freeRoom.ypos;
				break;
			case 'R':
				curRoom.xpos = freeRoom.xpos - 1;
				curRoom.ypos = freeRoom.ypos;
				break;
		}
		Floor.push_back(curRoom);
	}

	//Generate boss room
	Map bossRoom;
	int numCurRooms = numRoomsWithFreeSlots();
	int whichRoom = rand() % numCurRooms;
	Map freeRoom = freeSlotRooms[whichRoom];
	vector<char> availableRooms = freeRoom.getFreeSurroundingRooms();
	int numFree = rand() % availableRooms.size();
	char direction = availableRooms[numFree];
	switch(direction)
	{
		case 'U':
			bossRoom.xpos = freeRoom.xpos;
			bossRoom.ypos = freeRoom.ypos-1;
			break;
		case 'D':
			bossRoom.xpos = freeRoom.xpos;
			bossRoom.ypos = freeRoom.ypos+1;
			break;
		case 'L':
			bossRoom.xpos = freeRoom.xpos+1;
			bossRoom.ypos = freeRoom.ypos;
			break;
		case 'R':
			bossRoom.xpos = freeRoom.xpos-1;
			bossRoom.ypos = freeRoom.ypos;
			break;
	}

	//Boss room generation
	bossRoom.genSpecMap('B');
	bossRoom.discovered = true;
	bossRoom.generated  = true;
	// Add boss room in
	Floor.push_back(bossRoom);
	

	//Generate rooms
	int madeRooms = Floor.size();
	for(int i = 0; i < madeRooms; i ++)
	{
		Map curRoom = Floor[i];
		if(!curRoom.generated)
		{
			curRoom.genSpecMap('R');
			curRoom.discovered = true;
			curRoom.generated  = true;
			Floor[i] = curRoom;
		}
		else if(curRoom.currentRoom)
		{
			curRoom.genSpecMap('O');
			curRoom.discovered = true;
			curRoom.generated = true;
			curRoom.currentRoom = true;
			Floor[i] = curRoom;
		}
	}
}

void Map::genSpecMap(char type)
{
	vector<char> around = getSurroundingRooms();
	
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
				pieces.push_back(wall);
				wall.xpos = j*1700;
				wall.ypos = i*100;
				pieces.push_back(wall);
			}
			else
			{
				if(j == 0)
				{
					if(count(around.begin(), around.end(), 'U'))
					{
						wall.type = 'D';
						pieces.push_back(wall);
					}
					else
					{
						wall.type = 'W';
						pieces.push_back(wall);
					}
					if(count(around.begin(), around.end(), 'L'))
					{
						wall.type = 'D';
						wall.xpos = j*1700;
						wall.ypos = i*100;
						pieces.push_back(wall);
					}
					else
					{
						wall.type = 'W';
						wall.xpos = j*1700;
						wall.ypos = i*100;
						pieces.push_back(wall);
					}
				}
				else
				{
					if(count(around.begin(), around.end(), 'D'))
					{
						wall.type = 'D';
						pieces.push_back(wall);
					}
					else
					{
						wall.type = 'W';
						pieces.push_back(wall);
					}
					if(count(around.begin(), around.end(), 'R'))
					{
						wall.type = 'D';
						wall.xpos = j*1700;
						wall.ypos = i*100;
						pieces.push_back(wall);
					}
					else
					{
						wall.type = 'W';
						wall.xpos = j*1700;
						wall.ypos = i*100;
						pieces.push_back(wall);
					}
	
				}
			}
		}
	}


	switch(type)
	{
		case 'O':
			{
				break;
			}
		case 'B':
			{
			//	cout << "Spawned King Room\n";
				SlimeKing kingSlime;
				int radius       = 200;
				int r            = rand() % 255;
				int g            = rand() % 255;
				int b            = rand() % 255;

				kingSlime.xpos = 860;
				kingSlime.ypos = 800;
				kingSlime.curRadius = radius;
				kingSlime.init_size = radius;
				kingSlime.r         = r;
				kingSlime.g         = g;
				kingSlime.b         = b;
				kingSlime.health    = 10000;

				KingEnemies.push_back(kingSlime);
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

						curslime.xpos      = 800 + i*100;
						curslime.ypos      = 800 + j*11;
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
				for(int i = 0; i < 2; i++)
				{
					for(int j = 0; j <2; j++)
					{
						
						tankEnemy curTank;
						int radius = rand() % 20 + 40;
						int xpos   = 150 + i * 1460;
						int ypos   = 150 + j * 1460;
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
