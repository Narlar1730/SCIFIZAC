bool drawPauseScreen(int mousex, int mousey, bool MouseReleased, bool mouseDown, sf::RenderWindow* window)
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
	
	
	int highlightedBox = -1;
	
	//Draw Player
	sf::RectangleShape pbox(sf::Vector2f(200, 200));
	pbox.setPosition(320, 320);
	pbox.setFillColor(buttonColourNoHover);
	pbox.setOutlineColor(black);
	pbox.setOutlineThickness(2);
	window->draw(pbox);

	Player inventPlayer = mainChar;
	inventPlayer.xpos = 380;
	inventPlayer.ypos = 380;
	inventPlayer.drawPlayer(window);

	//Draw Pettttts
	sf::RectangleShape petBox(sf::Vector2f(200, 200));
	petBox.setPosition(320, 540);
	petBox.setFillColor(buttonColourNoHover);
	petBox.setOutlineColor(black);
	petBox.setOutlineThickness(2);
	if(petBox.getGlobalBounds().contains(mousex, mousey))
	{
		highlightedBox = 36;
		petBox.setFillColor(buttonColourHover);
	}
	window->draw(petBox);

	//Write out player stats
	sf::Text health;
	health.setFont(font);
	health.setString("Health:");
	health.setCharacterSize(40);
	health.setFillColor(black);
	health.setPosition(560, 320);
	window->draw(health);

	sf::Text gold;
	gold.setFont(font);
	gold.setString("Gold:");
	gold.setCharacterSize(40);
	gold.setFillColor(black);
	gold.setPosition(560, 370);
	window->draw(gold);
	
	//Draw Pet stats
	sf::Text Petname;
	Petname.setFont(font);
	Petname.setString("Pet Name:");
	Petname.setCharacterSize(40);
	Petname.setFillColor(black);
	Petname.setPosition(560, 540);
	window->draw(Petname);

	sf::Text petDam;
	petDam.setFont(font);
	petDam.setString("Damage:");
	petDam.setCharacterSize(40);
	petDam.setFillColor(black);
	petDam.setPosition(560, 590);
	window->draw(petDam);

	//Draw Trash slot
	sf::RectangleShape trashbox(sf::Vector2f(150, 150));
	trashbox.setPosition(900, 850);
	trashbox.setFillColor(buttonColourNoHover);
	trashbox.setOutlineColor(black);
	trashbox.setOutlineThickness(2);
	if(trashbox.getGlobalBounds().contains(mousex, mousey))
	{
		highlightedBox = 35;
		trashbox.setFillColor(buttonColourHover);
	}
	window->draw(trashbox);

	sf::Text trash;
	trash.setFont(font);
	trash.setString("Trash");
	trash.setCharacterSize(30);
	trash.setFillColor(white_opaque);
	trash.setPosition(930, 910);
	window->draw(trash);

	//Draw Armour and equips
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 2; j++)
		{
			sf::RectangleShape curBox(sf::Vector2f(150, 150));
			curBox.setPosition(1150+j*170, 320+i*170);
			curBox.setFillColor(buttonColourNoHover);
			curBox.setOutlineColor(black);
			curBox.setOutlineThickness(2);
			if(curBox.getGlobalBounds().contains(mousex, mousey))
			{
				curBox.setFillColor(buttonColourHover);
				highlightedBox = 26 + j*4 + i;
			}
			window->draw(curBox);
		}
	}

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
			highlightedBox = 24+i;
		}
		window->draw(wbox);

		//Draw numbers
		sf::Text t1;
		t1.setFont(font);
		t1.setString(std::to_string(i+1));
		t1.setPosition(420+i*160, 820);
		t1.setCharacterSize(160);
		t1.setFillColor(white_opaque);
		t1.setStyle(sf::Text::Bold);
		window->draw(t1);
	}

	
	
	//draw inventory boxes
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
				highlightedBox = i+8*j;
			}			
			window->draw(currentBox);
			

		}
	}
	//draw inventory shells
	//
	//HANDLE MOUSE CLICKSKSKSKSSKS
	vector<weapon> itemsToDraw;
	for(int i = 0; i < 24; i++)
	{
		
		weapon curItem = getItem(i);
		curItem.xpos = 315 +(i % 8)*150;
		int j = 0;
		if(i >= 16)
		{
			j = 2;
		}
		else if(i >= 8)
		{
			j = 1;
		}
		curItem.ypos = 1065 + j*150;
		if(mouseDown && highlightedBox == i && mainChar.CurSel == -1 && inventory[i].itemType != 'E')
		{
			mainChar.CurSel = i;
		}
		else if(MouseReleased && mainChar.CurSel != -1 && highlightedBox == i)
		{
			if(mainChar.CurSel == 24)
			{
				if(inventory[highlightedBox].itemType == 'W')
				{
					swapWeapon(highlightedBox, mainChar.CurSel);
					mainChar.CurSel = -1;
				}
			}
			else if(mainChar.CurSel == 36)
			{
				if(inventory[highlightedBox].itemType == 'P' || inventory[highlightedBox].itemType == 'E')
				{
					swapWeapon(highlightedBox, mainChar.CurSel);
					mainChar.CurSel = -1;
				}
			}
			else
			{
				swapWeapon(highlightedBox, mainChar.CurSel);
				mainChar.CurSel = -1;	
			}
						
		}
		if(mainChar.CurSel == i)
		{
			curItem.xpos = mousex;
			curItem.ypos = mousey;
		}
		itemsToDraw.push_back(curItem);
		//curItem.drawItem(window);
	}
	//Draw w1 and w2 weapons and handle mouse inputs
	for(int i = 24; i < 26; i++)
	{
		weapon curItem = getItem(i);
		curItem.xpos = 420+(i-24)*160;
		curItem.ypos = 880;
		if(mouseDown && highlightedBox == i && mainChar.CurSel == -1 && inventory[i].itemType != 'E')
		{
			mainChar.CurSel = i;
		}
		else if(MouseReleased && mainChar.CurSel != -1 && highlightedBox == i)
		{
			swapWeapon(highlightedBox, mainChar.CurSel);
			mainChar.CurSel = -1;	
						
		}
		if(mainChar.CurSel == i)
		{
			curItem.xpos = mousex;
			curItem.ypos = mousey;
		}
		itemsToDraw.push_back(curItem);

	}

	//Draaaaaaaaaaaaaaw pet
	
	if(inventory[36].itemType == 'P' || inventory[36].itemType == 'E')
	{
		weapon slimePet = inventory[36];
		slimePet.xpos = 320;
		slimePet.ypos = 540;
		if(mouseDown && highlightedBox == 36 && mainChar.CurSel == -1 && inventory[36].itemType != 'E')
		{
			mainChar.CurSel = 36;
		}
		else if(MouseReleased && mainChar.CurSel != -1 && highlightedBox == 36 && (inventory[mainChar.CurSel].itemType == 'P' || inventory[mainChar.CurSel].itemType == 'E'))
		{
			swapWeapon(highlightedBox, mainChar.CurSel);
			mainChar.CurSel = -1;	
						
		}
		if(mainChar.CurSel == 36)
		{
			slimePet.xpos = mousex;
			slimePet.ypos = mousey;
		}
		
		if(inventory[36].itemType == 'P')
		{
			slimePet.drawSlimePet(window);
		}
	}
	/*if(MouseReleased)
	{
		printItems();
	}*/
	if(MouseReleased)
	{
		mainChar.CurSel = -1;
		FirstGun = inventory[24];
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
	
	//Draw items in inventory.
	for(int i = 0; i < 26; i++)
	{
		weapon curItem = itemsToDraw[i];
		if(curItem.itemType!='P')
		{
			curItem.drawItem(window);
		}
		else
		{
			curItem.drawSlimePet(window);
		}
	}
	//Here we are drawing the overlay boxes. I don't like that I am looping twice through the same loop but there has to be a solution
	if(!MOUSEpressed)
	{
		if(highlightedBox == 24)
		{
			weapon curGun = getItem(24);
			int xpos = 980;
			int ypos = 850;
			curGun.drawStats(xpos, ypos, window);
		}
		for(int i = 0; i < 24; i++)
		{
			char curVal = inventory[i].itemType;
			if(curVal == 'W')
			{
				weapon curGun = getItem(i);
				int xpos = 315 + (i%8)*150;
				int j = 0;
				if(i >= 16)
				{
					j = 2;
				}
				if(i >= 8)
				{
					j = 1;
				}
				int ypos = 1065 + j*150;
				if(ypos > 1200)
				{
					ypos = 1200;
				}
				if(highlightedBox == i)
				{
					if(xpos < 600)
					{
						curGun.drawStats(xpos+570, ypos - 10, window);
					}
					else
					{
					
						curGun.drawStats(xpos+10, ypos - 10, window);
					}
				}
			}
		}
	}

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

