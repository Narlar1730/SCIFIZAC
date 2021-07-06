bool drawPauseScreen(int mousex, int mousey, bool MouseReleased, sf::RenderWindow* window)
{
	bool output = true;

	if(buttonClickTimer < 0)
	{
		buttonClickTimer = 0;
	}
	else
	{
		buttonClickTimer -= 1;
	}
	//Just removing warnings for things I will need later.
	if(mousex == mousey)
	{
	}
	else if(MouseReleased)
	{
	}
	
	//Set Colours
	sf::Color backgroundColour    {160, 160, 160, 160};
	sf::Color buttonColourNoHover {120, 120, 120};
	sf::Color softGrey            {180, 180, 180};
	sf::Color buttonColourHover   {140, 140, 140};
	sf::Color black               {  0,   0,   0};
	sf::Color white_opaque	      {255, 255, 255, 80};
	//Grey Overlay
	sf::RectangleShape background(sf::Vector2f(1800.f, 1800.f));
	background.setPosition(0, 0);
	background.setFillColor(backgroundColour);
	window->draw(background);
	
	//Draw interactive menu, minecraft style atm
	sf::RectangleShape outershell(sf::Vector2f(1300, 1300));
	outershell.setPosition(250, 250);
	outershell.setFillColor(softGrey);
	outershell.setOutlineColor(black);
	outershell.setOutlineThickness(2);
	window->draw(outershell);

	//draw inventory shells
	for(int i = 0; i < 8; i ++)
	{
		for(int j = 0; j < 3; j++)
		{
			sf::RectangleShape currentBox(sf::Vector2f(140, 140));
			currentBox.setPosition(305+i*150, 1055+j*150);
			currentBox.setFillColor(buttonColourNoHover);
			currentBox.setOutlineColor(black);
			currentBox.setOutlineThickness(2);
			if(currentBox.getGlobalBounds().contains(mousex, mousey))
			{
				currentBox.setFillColor(buttonColourHover);
			}
			window->draw(currentBox);
		}
	}

	//Draw Crafting Menu
	for(int i = 0; i < 2; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			sf::RectangleShape craft1(sf::Vector2f(150, 150));
			craft1.setPosition(320 + i*200, 320 + j*200);
			craft1.setFillColor(buttonColourNoHover);
			craft1.setOutlineColor(black);
			craft1.setOutlineThickness(2);
			if(craft1.getGlobalBounds().contains(mousex, mousey))
			{
				craft1.setFillColor(buttonColourHover);
			}
			window->draw(craft1);
		}
	}
	sf::RectangleShape craftFinal(sf::Vector2f(150, 150));
	craftFinal.setPosition(770, 420);
	craftFinal.setFillColor(buttonColourNoHover);
	craftFinal.setOutlineColor(black);
	craftFinal.setOutlineThickness(2);
	if(craftFinal.getGlobalBounds().contains(mousex, mousey))
	{
		craftFinal.setFillColor(buttonColourHover);
	}
	window->draw(craftFinal);
	
	//Draw W1 and W2
	for(int i = 0; i < 2; i++)
	{
		//Draw background box
		sf::RectangleShape wbox(sf::Vector2f(150, 150));
		wbox.setPosition(390+i*160, 850);
		wbox.setFillColor(buttonColourNoHover);
		wbox.setOutlineColor(black);
		wbox.setOutlineThickness(2);
		if(wbox.getGlobalBounds().contains(mousex, mousey))
		{
			wbox.setFillColor(buttonColourHover);
		}
		window->draw(wbox);

		//Draw numbers
		sf::Text t1;
		t1.setFont(font);
		t1.setString(std::to_string(i));
		t1.setPosition(420+i*160, 820);
		t1.setCharacterSize(160);
		t1.setFillColor(white_opaque);
		t1.setStyle(sf::Text::Bold);
		window->draw(t1);
	}

	//Draw x button
	sf::RectangleShape exitButton(sf::Vector2f(40.f, 30.f));
	exitButton.setPosition(10, 10);
	exitButton.setFillColor(buttonColourNoHover);
	exitButton.setOutlineColor(black);
	exitButton.setOutlineThickness(4);
	sf::Text exitText;
	exitText.setFont(font);
	exitText.setString("X");
	exitText.setCharacterSize(30);
	exitText.setFillColor(black);
	exitText.setStyle(sf::Text::Bold);
	exitText.setPosition(18, 8);

	//Dynamic buttons!
	if(exitButton.getGlobalBounds().contains(mousex, mousey))
	{
		exitButton.setFillColor(buttonColourHover);
		if(MouseReleased)
		{
			output = false;
		}
	}

	if(Epressed && buttonClickTimer == 0)
	{
		output = false;
		buttonClickTimer = 100;
	}
	//Actually draw the shit
	window->draw(exitButton);
	window->draw(exitText);
		
	//exit function
	return output;
}

