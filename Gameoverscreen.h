
using namespace std;

char drawGameOverScreen(int, int, bool, sf::RenderWindow*);

void gameOverScreen(sf::RenderWindow* window)
{
	bool screenRunning = true;
	char next;
	while(screenRunning)
	{

		sf::Event event;
		sf::Vector2i pixelPos = sf::Mouse::getPosition(*window);
		int MouseX = pixelPos.x;
		int MouseY = pixelPos.y;
		bool MouseReleased = false;
		
		//FIXME
		//This is only here to stop a warning, it doesn't do anything
		while(window->pollEvent(event))
		{
			if(event.type == sf::Event::MouseButtonReleased)
			{
				MouseReleased = true;
			}
		}

		next = drawGameOverScreen(MouseX, MouseY, MouseReleased, window);

		if(next != 's')
		{
			screenRunning = false;
		}
	}

	switch(next)
	{
		case 'b' :
			openingScreen(window);
			break;
		case 'q' :
			cout << "Quitting after game over :)\n";
			exit(0);
	}
}

char drawGameOverScreen(int mousex, int mousey, bool MouseReleased, sf::RenderWindow* window)
{
	//return s for stay on same screen and don't change screen. 
	char outPut = 's';

	window->clear();
	
	//Set Colours
	sf::Color backgroundColour {160, 160, 160, 50};
	sf::Color titleTextColour {255, 0, 0};
	sf::Color buttonColourNoHover {120, 120, 120};
	sf::Color buttonColourHover {140, 140, 140};
	sf::Color black {0, 0, 0};

	//Draw Background
	sf::RectangleShape background(sf::Vector2f(1800.f, 1800.f));
	background.setPosition(0, 0);
	background.setFillColor(backgroundColour);
	window->draw(background);
	
	//Draw Title!
	sf::Text title;
	title.setFont(font);
	title.setString("GAME OVER");
	title.setCharacterSize(60);
	title.setFillColor(titleTextColour);
	title.setStyle(sf::Text::Bold);
	title.setPosition(800, 100);
	window->draw(title);
	
	//Draw Top button, play!
	sf::RectangleShape b1(sf::Vector2f(800.f, 200.f));
	b1.setPosition(500, 400);
	b1.setFillColor(buttonColourNoHover);
	b1.setOutlineColor(black);
	b1.setOutlineThickness(4);
	sf::Text b1Text;
	b1Text.setFont(font);
	b1Text.setString("Main Menu");
	b1Text.setCharacterSize(40);
	b1Text.setFillColor(black);
	b1Text.setStyle(sf::Text::Bold);
	b1Text.setPosition(580, 480);
	
	//Draw Button 2, options?
	sf::RectangleShape b2(sf::Vector2f(800.f, 200.f));
	b2.setPosition(500, 700);
	b2.setFillColor(buttonColourNoHover);
	b2.setOutlineColor(black);
	b2.setOutlineThickness(4);
	sf::Text b2Text;
	b2Text.setFont(font);
	b2Text.setString("Stats");
	b2Text.setCharacterSize(40);
	b2Text.setFillColor(black);
	b2Text.setStyle(sf::Text::Bold);
	b2Text.setPosition(580, 780);

	//Draw Button 3, stuff
	sf::RectangleShape b3(sf::Vector2f(800.f, 200.f));
	b3.setPosition(500, 1000);
	b3.setFillColor(buttonColourNoHover);
	b3.setOutlineColor(black);
	b3.setOutlineThickness(4);
	sf::Text b3Text;
	b3Text.setFont(font);
	b3Text.setString("Quit");
	b3Text.setCharacterSize(40);
	b3Text.setFillColor(black);
	b3Text.setStyle(sf::Text::Bold);
	b3Text.setPosition(580, 1080);
	
	if(b1.getGlobalBounds().contains(mousex, mousey))
	{
		if(MouseReleased)
		{
			outPut = 'b';
		}
		b1.setFillColor(buttonColourHover);
	}
	else if(b2.getGlobalBounds().contains(mousex, mousey))
	{
		b2.setFillColor(buttonColourHover);
	}
	else if(b3.getGlobalBounds().contains(mousex, mousey))
	{
		if(MouseReleased)
		{
			outPut = 'q';
		}
		b3.setFillColor(buttonColourHover);
	}
	

	//Slap the buttons down
	window->draw(b1);
	window->draw(b2);
	window->draw(b3);
	
	//Slap the text down
	window->draw(b1Text);
	window->draw(b2Text);
	window->draw(b3Text);

	//Actually draw the screen
	window->display();
	window->clear();
	//Return current selection
	return outPut;
}


