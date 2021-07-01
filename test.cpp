#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <X11/Xlib.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <tuple>
#include <string>
#include <sstream>
#include <time.h>
//#include "board.h"
//#include "titlescreen.h"
//#include "optionsscreen.h"
//#include "gamemain.h"
//#include "keyBoardManagement.h"
#include "weapon.h"

using namespace std;

/*Colours

Name            FG  BG
Black           30  40
Red             31  41
Green           32  42
Yellow          33  43
Blue            34  44
Magenta         35  45
Cyan            36  46
White           37  47
Bright Black    90  100
Bright Red      91  101
Bright Green    92  102
Bright Yellow   93  103
Bright Blue     94  104
Bright Magenta  95  105
Bright Cyan     96  106
Bright White    97  107

*/

void testingProjectilesClass()
{
	printf("\x1b[95mRunning Automated testing of class: projectile \033[0m\n");

	//new1 and new2 are the same, new2 will be differnet. 
	projectile new1;
	projectile new2;
	projectile new3;
	
	new1.spawnProjectile(2, 2, 3, 3, 4, 50);
	new2.spawnProjectile(2, 2, 3, 3, 4, 50);
	new3.spawnProjectile(1, 1, 1, 1, 1, 10);

	printf("\x1b[95mRunning test of boolean operators, == and !=\033[0m\n");
	
	printf("\x1b[33mTesting equality one way\033[0m\n");
	if(new1 == new2)
	{
		printf("\x1b[32mTest Passed, equality works one way n1 == n2. \033[0m\n");
	}
	else
	{
		printf("\x1b[31mTest Failed. Equality is not working n1 == n2 \033[0m\n");
	
	}
	printf("\n");
	printf("\x1b[33mTesting equality other way\033[0m\n");
	if(new2 == new1)
	{
		printf("\x1b[32mTest passed, equality works other way, n2 == n1\033[0m\n");
	}
	else
	{
		printf("\x1b[31mTest failed, equality does not work n2 == n1\033[0m\n");
	}
	printf("\n");
	
	printf("\x1b[33mTesting inequality one way, n1 != n3\033[0m\n");
	if(new1 != new3)
	{
		printf("\x1b[32mTest passed, inequality does work n1 != n3\033[0m\n");
	}
	else
	{
		printf("\x1b[31mTest failed, inequality does work n1 != n3\033[0m\n");
	}
	printf("\n");
	
	printf("\x1b[33mTesting inequality second way, n2 != n3\033[0m\n");
	if(new2 != new3)
	{
		printf("\x1b[32mTest passed, inequality does work n2 != n3\033[0m\n");	
	}
	else
	{
		printf("\x1b[31mTest failed, inequality does work n2 != n3\033[0m\n");
	}
	printf("\n");

	printf("\x1b[33mTesting inequality reversed, n3 != n2\033[0m\n");
	if(new3 != new2)
	{
		printf("\x1b[32mTest passed, inequality does work n3 != n2\033[0m\n");	
	}
	else
	{
		printf("\x1b[31mTest Failed, inequality does not work n3 != n2\033[0m\n");	
	}
	
	printf("\n");
	printf("\x1b[95mTesting Module for projectiles completed.\033[0m\n");

	
}

int main()
{
	testingProjectilesClass();
	
	return 0;
}
