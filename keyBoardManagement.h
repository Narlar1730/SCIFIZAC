#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <X11/Xlib.h>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdlib.h>
#include <tuple>
#include <sstream>
#include <time.h>

using namespace std;

bool Dpressed = false;
bool Epressed = false;
bool Spressed = false;
bool Apressed = false;
bool Wpressed = false;
bool Lpressed = false;

bool UPpressed    = false;
bool DOWNpressed  = false;
bool LEFTpressed  = false;
bool RIGHTpressed = false;

bool MOUSEpressed = false;

void performKeyPress()
{
	// Reset Current Keys pressed

	// Handle Key Presses
	
	// Here we handle control pressed - this is usually to exit the program, maybe some other special things later on
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::C))
		{
			cout << "User Quit Program: CTRL + C\n";
			exit(0);
		}
	}
	
	// Here we handle the escape key - a special key to always exit
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		cout << "User Quit Program: Escape Key\n";
		exit(0);
	}
	
	//Get All other user input. Here we are grabbing the keys, adding them into the charPressed Array, which is declared in gamemain.h
		
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Dpressed = true;
	}
	else
	{
		Dpressed = false;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		Epressed = true;
	}
	else
	{
		Epressed = false;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Spressed = true;
	}
	else
	{
		Spressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Apressed = true;
	}
	else
	{
		Apressed = false;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Wpressed = true;
	}
	else
	{
		Wpressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
	{
		Lpressed = true;
	}
	else
	{
		Lpressed = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		UPpressed = true;
	}
	else
	{
		UPpressed = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		LEFTpressed = true;
	}
	else
	{
		LEFTpressed = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		RIGHTpressed = true;
	}
	else
	{
		RIGHTpressed = false;
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		DOWNpressed = true;
	}
	else
	{
		DOWNpressed = false;
	}

	//Here we handle the mouse
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		MOUSEpressed = true;
	}
	else
	{
		MOUSEpressed = false;
	}

}

