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
#include "titlescreen.h"

using namespace std;

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
	return true;
}

void drawBoard(sf::RenderWindow* window)
{
	cout << "drawing board\n";
}

void drawGameOver(sf::RenderWindow* window)
{

}


void runGame(sf::RenderWindow* window){
	bool gameRunning = true;

	while (gameRunning)
	{
		sf::Event event;
		sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
		
		// Handle Events
		int  MouseX        = pixelPos.x;
		int  MouseY        = pixelPos.y;
		bool MouseDown = false;
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
		case 'p' :
			break;
		case 'q' :
			cout << "User quit From main menu\n";
			exit(0);
	}
}

// Thread handling graphics and drawing
void renderingThread(sf::RenderWindow* window)
{
	window->setActive(true);
	while(window->isOpen())
	{
		openingScreen(window);
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

    	while (window.isOpen())
    	{
		performKeyPress();
    	}

    	return 0;
}

