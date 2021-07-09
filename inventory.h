/*Master list codex:
 E: empty
 W: weapon
*/
vector<char> masterlist;
vector<weapon> weaponInventory;

bool insertWeapon(weapon);
bool insertWeapon(weapon, int);
weapon getWeapon(int);

void initInventory()
{
	weaponInventory = {};
	for(int i = 0; i < 24; i++)
	{
		masterlist.push_back('E');
	}
}

void removeWeapon(weapon w)
{
	int index = w.inventoryIndex;
	int numWeps = weaponInventory.size();
	for(int i = 0; i < numWeps; i++)
	{
		if(weaponInventory[i].inventoryIndex == index)
		{
			weaponInventory.erase(weaponInventory.begin()+i);
		}
	}
	masterlist[index] = 'E';
}

bool insertWeapon(weapon w)
{
	bool output = false;
	
	int insertPos = -1;
	for(int i = 0; i < 24; i++)
	{
		char curVal = masterlist[i];
		if(curVal == 'E')
		{
			insertPos = i;
			break;
		}
	}

	if(insertPos != -1)
	{
		output = insertWeapon(w, insertPos);
		
	}
	


	return output;	
}

bool insertWeapon(weapon w, int i)
{
	bool output = false;

	if(masterlist[i] == 'E')
	{
		masterlist[i] = 'W';
		w.inventoryIndex = i;
		weaponInventory.push_back(w);
		output = true;
	}

	return output;
}

weapon getWeapon(int i)
{
	weapon w1;
	int numweps = weaponInventory.size();
	for(int j = 0; j < numweps; j++)
	{
		weapon curwep = weaponInventory[j];
		if(i == curwep.inventoryIndex)
		{
			w1 = curwep;
		}
	}

	return w1; 
}

void setWeapon(weapon w1, int index)
{
	int numWeps = weaponInventory.size();
	for(int i = 0; i < numWeps; i++)
	{
		weapon curWep = weaponInventory[i];
		if(curWep.inventoryIndex == index)
		{
			weaponInventory[i] = w1;	
		}
	}	
}

bool swapWeapon(int oldSlot, int newSlot)
{
	bool success = false;
	weapon w1;
	weapon w2;
	
	/*{
		printf("\x1b[31mERR: Insert Failed, could not insert into list\033[0m\n");
		exit(0);
	}*/
	
	
	w1 = getWeapon(oldSlot);
	w2 = getWeapon(newSlot);
	int w1Pos = w1.inventoryIndex;
	int w2Pos = w2.inventoryIndex;

	w1.inventoryIndex = w2Pos;
	w2.inventoryIndex = w1Pos;

	setWeapon(w1, w2Pos);
	setWeapon(w2, w1Pos);
	success = true;

		
	return success;
}

