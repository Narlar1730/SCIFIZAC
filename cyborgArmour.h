void drawCyborgHead(sf::RenderWindow* window, int xpos, int ypos)
{
	sf::Texture maskTexture;
	if(!maskTexture.loadFromFile("resources//ground_icons//CyborgMask.png"))
	{
		cout << "Err";
	}
	sf::Sprite sprite(maskTexture);
	sf::Vector2u size = maskTexture.getSize();
	sprite.setOrigin(size.x/2, size.y/2);
	sprite.setPosition(xpos+50, ypos+50);
	window->draw(sprite);

}

void drawCyborgChest(sf::RenderWindow* window, int xpos, int ypos)
{
	sf::Texture maskTexture;
	if(!maskTexture.loadFromFile("resources//ground_icons//CyborgChest.png"))
	{
		cout << "Err";
	}
	sf::Sprite sprite(maskTexture);
	sf::Vector2u size = maskTexture.getSize();
	sprite.setOrigin(size.x/2, size.y/2);
	sprite.setPosition(xpos+50, ypos+50);
	window->draw(sprite);

}

void drawCyborgPants(sf::RenderWindow* window, int xpos, int ypos)
{
	sf::Texture maskTexture;
	if(!maskTexture.loadFromFile("resources//ground_icons//CyborgPants.png"))
	{
		cout << "Err";
	}
	sf::Sprite sprite(maskTexture);
	sf::Vector2u size = maskTexture.getSize();
	sprite.setOrigin(size.x/2, size.y/2);
	sprite.setPosition(xpos+50, ypos+50);
	window->draw(sprite);

}

void drawCyborgBoots(sf::RenderWindow* window, int xpos, int ypos)
{
	sf::Texture maskTexture;
	if(!maskTexture.loadFromFile("resources//ground_icons//CyborgBoots.png"))
	{
		cout << "Err";
	}
	sf::Sprite sprite(maskTexture);
	sf::Vector2u size = maskTexture.getSize();
	sprite.setOrigin(size.x/2, size.y/2);
	sprite.setPosition(xpos+50, ypos+50);
	window->draw(sprite);

}


void weapon::drawCyborgArmour(sf::RenderWindow* window)
{
	int xp = xpos;
	int yp = ypos;
	if(itemType == 'H')
	{
		drawCyborgHead(window, xp, yp);
	}
	else if(itemType == 'C')
	{
		drawCyborgChest(window, xp, yp);
	}
	else if(itemType == 'L')
	{
		drawCyborgPants(window, xp, yp);
	}
	else if(itemType == 'B')
	{
		drawCyborgBoots(window, xp, yp);
	}



}
