void drawWornHead(sf::RenderWindow* window, int xpos, int ypos, weapon head)
{
	if(head.style == 'C')
	{
		sf::Texture texture;
		if(!texture.loadFromFile("resources//wear_icons//CyborgMask.png"))
		{
			cout << "DisErr";
		}
		xpos = xpos+30;
		ypos = ypos+40;
		sf::Sprite sprite(texture);
		sf::Vector2u size = texture.getSize();
		sprite.setOrigin(size.x/2, size.y/2);
		int rotation = 0;
		if(UPpressed && LEFTpressed)
		{
			rotation = 45;
			xpos += 5;
			ypos -= 5;
		}
		else if(UPpressed && RIGHTpressed)
		{
			rotation = 135;
			xpos += 15;
			ypos -= 5;
		}
		else if(DOWNpressed && LEFTpressed)
		{
			rotation = 315;
			xpos += 5;
			ypos += 5;
		}
		else if(DOWNpressed && RIGHTpressed)
		{
			rotation = 225;
			xpos += 15;
			ypos += 5;
		}
		else if(UPpressed)
		{
			rotation = 90;
			xpos += 10;
			ypos -= 10;
		}
		else if(DOWNpressed)
		{
			rotation = 270;
			xpos += 10;
			ypos += 10;

		}
		else if(LEFTpressed)
		{
			xpos = xpos;
			ypos = ypos;
			rotation = 0;
		}
		else
		{
			rotation = 180;
			xpos += 20;
			ypos += 0;
		}

		sprite.setPosition(xpos, ypos);
		sprite.setRotation(rotation);
		window->draw(sprite);
	}
}

void drawWornChest(sf::RenderWindow* window, int xpos, int ypos, weapon chest)
{
	if(chest.style == 'C')
	{
		sf::Texture texture;
		if(!texture.loadFromFile("resources//wear_icons//CyborgChest.png"))
		{
			cout << "DisErr";
		}
		xpos = xpos+30;
		ypos = ypos+40;
		sf::Sprite sprite(texture);
		sf::Vector2u size = texture.getSize();
		sprite.setOrigin(size.x/2, size.y/2);
		int rotation = 0;
		if(UPpressed && LEFTpressed)
		{
			rotation = 45;
			xpos += 5;
			ypos -= 5;
		}
		else if(UPpressed && RIGHTpressed)
		{
			rotation = 135;
			xpos += 15;
			ypos -= 5;
		}
		else if(DOWNpressed && LEFTpressed)
		{
			rotation = 315;
			xpos += 5;
			ypos += 5;
		}
		else if(DOWNpressed && RIGHTpressed)
		{
			rotation = 225;
			xpos += 15;
			ypos += 5;
		}
		else if(UPpressed)
		{
			rotation = 90;
			xpos += 10;
			ypos -= 10;
		}
		else if(DOWNpressed)
		{
			rotation = 270;
			xpos += 10;
			ypos += 10;

		}
		else if(LEFTpressed)
		{
			xpos = xpos;
			ypos = ypos;
			rotation = 0;
		}
		else
		{
			rotation = 180;
			xpos += 20;
			ypos += 0;
		}

		sprite.setPosition(xpos, ypos);
		sprite.setRotation(rotation);
		window->draw(sprite);
	}

}

void drawWornLeggings(sf::RenderWindow* window, int xpos, int ypos, weapon leggings)
{
	return;
}

void drawWornBoots(sf::RenderWindow* window, int xpos, int ypos, weapon boots)
{
	return;
}
