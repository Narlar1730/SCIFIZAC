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
#include "keyBoardManagement.h"
#include "titlescreen.h"
#include "optionsscreen.h"
#include "gamemain.h"

using namespace std;


void removeVectorDups(vector<char> vec)
{
	sort(vec.begin(), vec.end());
	vec.erase(unique(vec.begin(), vec.end()), vec.end());

}

void openingScreen(sf::RenderWindow* window)
{
	bool gameRunning = true;
	char next;
	while(gameRunning)
	{
		//Get Mouse information
		sf::Event event;
		sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);

		int MouseX = pixelPos.x;
		int MouseY = pixelPos.y;
		bool MouseDown = false;
		bool MouseReleased = false;
		
		//FIXME warning removal
		if(MouseDown)
		{
		
		}
		while(window->pollEvent(event))
		{
			if(event.type == sf::Event::MouseButtonReleased)
			{
				MouseReleased = true;
			}
			else if(event.type == sf::Event::MouseButtonPressed)
			{
				MouseDown = true;
			}
		}
		//Draw Graphics
		next = DrawMainMenu(MouseX, MouseY, MouseReleased, window);
		
		//Next is the next screen at this stage, s is stay, so we change next to be anything else, we
		//will have to stay on this screen
		if(next != 's')
		{
			gameRunning = false;
		}

	}
	//Figure out what the next screen is.
	switch(next)
	{
		case 'o':
			statsScreen(window);
			break;
		case 'p' :
			runningScreen = true;
			runningGame   = true;
			GameScreen(window);
			//runningScreen = true;
			gameOverScreen(window);
			break;
		case 'q' :
			cout << "User quit From main menu\n";
			exit(0);
			break;
	}
}

// Thread handling graphics and drawing
void renderingThread(sf::RenderWindow* window)
{
	window->setActive(true);
	while(window->isOpen())
	{
		openingScreen(window);
	}
}


int main()
{
	// Seed random
	srand ( time(NULL));
	// Start threads
	XInitThreads();
	// Setup window
	sf::RenderWindow window(sf::VideoMode(1800, 1800), "SCIFIZAC");
	window.setActive(false);
	//Loads font
	if(!font.loadFromFile("arial.ttf")){
		cout << "ERR, couldn't load font file\n";
		return 0;
	}

    	//Launches Graphics in new thread
    	sf::Thread thread(&renderingThread, &window);
    	thread.launch();

    	while (window.isOpen())
    	{
		performKeyPress();
    	}

    	return 0;
}



