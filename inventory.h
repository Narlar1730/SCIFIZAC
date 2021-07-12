/*Master list codex:
 E: empty
 W: weapon
*/
vector<char> masterlist;
vector<weapon> weaponInventory;
vector<weapon> inventory;

void swapWeapon(int, int);
bool insertWeapon(weapon);
bool insertWeapon(weapon, int);
weapon getWeapon(int);
void removeItem(int);

void printItems()
{
	for(int i = 0; i < 24; i++)
	{
		if(i < 10)
		{
			cout << "Item at index: " << i << "  is: " << inventory[i].name << "\n";
		}
		else
		{
			cout << "Item at index: " << i << " is: " << inventory[i].name << "\n";
		}
	}
	cout << "\n";
}

void removeItem(int index)
{
	weapon newItem;
	newItem.itemType = 'E';
	inventory[index] = newItem;
}

weapon getItem(int index)
{
	weapon curItem = inventory[index];
	return curItem;
}

void initInventory()
{
	weaponInventory = {};
	for(int i = 0; i < 24; i++)
	{
		weapon newItem;
		newItem.itemType = 'E';
		inventory.push_back(newItem);
	}
}

/*bool insertWeapon(weapon w)
{

}*/

bool insertWeapon(weapon w)
{
	bool output = false;
	for(int i = 0; i < 24; i++)
	{
		weapon curItem = inventory[i];
		if(curItem.itemType == 'E')
		{
			inventory[i] = w;
			output = true;
			break;
		}
	}
	return output;
}

bool insertWeapon(weapon w, int index)
{
	inventory[index] = w;
	return true;
}

void swapWeapon(int w1, int w2)
{
	//printItems();

	//cout << "Swap Items\n";

	weapon weapon1 = inventory[w1];
	weapon weapon2 = inventory[w2];

	inventory[w1] = weapon2;
	inventory[w2] = weapon1;

	//printItems();
}


