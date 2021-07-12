/*class Item{
	public:
		int xpos, ypos;
		char itemType;
		void drawItem(sf::RenderWindow* window);
		void drawStats(int, int, sf::RenderWindow* window);
		string name;
};*/

class weapon{
	public:
		int damage, firerate, range, bulletSize, bulletSpeed, extra, xpos, ypos;
		int inventoryIndex = -1;
		char itemType;
		string name;
		char style, rarity;
		void FireWeapon();
		void drawHeldWeapon(sf::RenderWindow*);
		void drawItem(sf::RenderWindow*);
		void drawGroundWeapon(sf::RenderWindow*);
		void setGun(int, int, int, char, int, int);
		void drawStats(int, int, sf::RenderWindow*);
};

/*class emptyItem: public Item{

	public:
		void drawItem(sf::RenderWindow* window);
		void initItem();
};

void emptyItem::initItem()
{
	xpos = 0;
	ypos = 0;
	itemType = 'E';
}

void emptyItem::drawItem(sf::RenderWindow* window)
{
	return;
}*/

/*weapon ConvertToWeapon(Item item)
{
	weapon w1;
	w1.damage      = item.damage;
	w1.firerate    = item.firerate;
	w1.range       = item.range;
	w1.bulletSize  = item.bulletSize;
	w1.bulletSpeed = item.bulletSpeed;
	w1.extra       = item.extra;
	w1.style       = item.style;
	w1.rarity      = item.rarity;
	return w1;
}*/


