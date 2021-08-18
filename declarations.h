class SlimeEnemy {
	public:
		int xpos, ypos, curRadius, init_size, r, g, b, xVel, yVel;
		int hitCounter = 0;
		int health = init_size*10;
		int speed = 10;
		bool growing;
		void spawnSlime();
		bool hurtSlime(int);
		void spawnSlime(int, int);
		void drawSlime(sf::RenderWindow*);
		void moveSlime();
};

class DeadSlime {
	public:
	        int xpos, ypos, radius, lifeSpan;
	        void spawnDead(int, int, int, int);
		void updateDead();
		void drawDead(sf::RenderWindow*);	       
};

class SlimeKing {
	public:
		int xpos, ypos, curRadius, init_size, r, g, b;
		int hitCounter = 0;
		int attackCounter = 0;
		int health = init_size*10;
		int speed = 10;
		bool growing;
		void spawnSlime();
		bool hurtSlime(int);
		void spawnSlime(int, int);
		void drawSlime(sf::RenderWindow*);
		void moveSlime();
};

class DeadKingSlime {
	public:
	        int xpos, ypos, radius, lifeSpan;
	        void spawnDead(int, int, int, int);
		void updateDead();
		void drawDead(sf::RenderWindow*);
};

class tankEnemy {
	public:
		int xpos, ypos, curRadius, init_size, r, g, b;
		int hitCounter = 0;
		int health = init_size*50;
		int countdownReset = 160;
		int countdown = countdownReset;
		int speed = 5;
		bool growing;
		void spawnTank();
		bool hurtTank(int);
		void spawnTank(int, int);
		void drawTank(sf::RenderWindow*);
		void moveTank();
		void fireTank();

};

class DeadTank {
	public:
	        int xpos, ypos, radius, lifeSpan;
	        void spawnDead(int, int, int, int);
		void updateDead();
		void drawDead(sf::RenderWindow*);
};

class weapon{
	public:
		int damage, firerate, range, bulletSize, bulletSpeed, extra, xpos, ypos;
		int inventoryIndex = -1;
		char itemType;
		bool animation = false;
		string name;
		char style, rarity;
		void FireWeapon();
		void drawShotgun(sf::RenderWindow*);
		void drawRifle(sf::RenderWindow*);
		void drawMiniGun(sf::RenderWindow*);
		void drawLaser(sf::RenderWindow*);
		void drawHeldWeapon(sf::RenderWindow*);
		void drawItem(sf::RenderWindow*);
		void drawGroundWeapon(sf::RenderWindow*);
		void setGun(int, int, int, char, int, int);
		void drawStats(int, int, sf::RenderWindow*);
		//Change this to something else?
		//
		//Handle Pets
		void drawSlimePet(sf::RenderWindow*);
		void moveSlimePet();

		//Handle Armour
		void drawCyborgArmour(sf::RenderWindow*);
};

class obstacle{
	public:
		int xpos, ypos;
		char type;
		void drawObstacle(sf::RenderWindow* window);
		void drawObstacle(sf::RenderWindow* window, sf::Color, sf::Color, sf::Color);
};


class Map{
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
		//Different Maps!
		void		   randomPieceMap();
		void		   swirlyPieceMap();
};
