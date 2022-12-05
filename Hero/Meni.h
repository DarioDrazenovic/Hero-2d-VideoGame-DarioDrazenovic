
#pragma once
#include "SFML\Graphics.hpp"

#define MAX_NUMBER_OF_ITEMS 4

class Meni
{
public:
	Meni(float width, float height);
	~Meni();

	void draw(sf::RenderWindow& window);

	// prema gore i dolje gumb
	void MoveUp();
	void MoveDown();
	int GetPressedItem() { return selectItemIndex; }

private:
	// stvar koja je izabrana trenutno
	int selectItemIndex;

	sf::Font font;
	sf::Text meni[MAX_NUMBER_OF_ITEMS];
};
