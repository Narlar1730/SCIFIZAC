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


using namespace std;

sf::Font font;

bool MouseDown = false;


void performKeyPress()
{

	// Handle Key Press
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			cout << "User Quit Program\n";
			exit(0);
		}
	}
	

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		cout << "User Quit Program\n";
		exit(0);
	}

}

bool updateGame()
{
}

void drawBoard(sf::RenderWindow* window)
{

}

void runGame(sf::RenderWindow* window){
	bool gameRunning = true;

	while (window->isOpen() && gameRunning)
	{
		sf::Event event;
		sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
		
		// Handle Events
		int  MouseX        = pixelPos.x;
		int  MouseY        = pixelPos.y;
		//bool MouseReleased;
		
		while (window->pollEvent(event))
		{
			if(event.type == sf::Event::MouseButtonReleased)
			{
				cout << "Mouse Clicked at " << MouseX << " " << MouseY << "\n";
				MouseDown = false;
				//MouseReleased = true;
			}
			else if(event.type == sf::Event::MouseButtonPressed)
			{
				MouseDown = true;
			}
		}

//		drawBoard(window, MouseX, MouseY, MouseReleased);
//		drawButtons(window, MouseX, MouseY, MouseReleased);
		gameRunning = updateGame();
		drawBoard(window);
		window->display();
		window->clear();
	}

}

void drawGameOver(sf::RenderWindow* window)
{
}


// Thread handling graphics and drawing
void renderingThread(sf::RenderWindow* window)
{
	window->setActive(true);
	while(window->isOpen())
	{
		runGame(window);
		drawGameOver(window);	
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

	//sf::Thread keyPresses(&performKeyPress);
	//keyPresses.launch();

    	while (window.isOpen())
    	{
		performKeyPress();
    	}

    	return 0;
}

