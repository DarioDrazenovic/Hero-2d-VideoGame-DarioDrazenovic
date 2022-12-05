
#include "Meni.h"

Meni::Meni(float width, float height)
{
	if (font.loadFromFile("arial.ttf"))
	{

	}

	meni[0].setFont(font);
	meni[0].setFillColor(sf::Color::Blue);
	meni[0].setString("Play");
	// pozicija itema														   1 po redu
	meni[0].setPosition(sf::Vector2f(width / 2.2, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));

	meni[1].setFont(font);
	meni[1].setFillColor(sf::Color::White);
	meni[1].setString("Options");											// 2 po redu
	meni[1].setPosition(sf::Vector2f(width / 2.2, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));

	meni[2].setFont(font);
	meni[2].setFillColor(sf::Color::White);
	meni[2].setString("HighScore");											// 3 po redu
	meni[2].setPosition(sf::Vector2f(width / 2.2, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));

	meni[3].setFont(font);
	meni[3].setFillColor(sf::Color::White);
	meni[3].setString("Exit");												// 4 po redu
	meni[3].setPosition(sf::Vector2f(width / 2.2, height / (MAX_NUMBER_OF_ITEMS + 1) * 4));

	selectItemIndex = 0;
}

Meni::~Meni()
{
}

void Meni::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(meni[i]);
	}
}

void Meni::MoveUp()
{
	if (selectItemIndex - 1 >= 0)
	{
		meni[selectItemIndex].setFillColor(sf::Color::White);
		selectItemIndex--;
		// novi odabrani
		meni[selectItemIndex].setFillColor(sf::Color::Blue);
	}
}

void Meni::MoveDown()
{
	if (selectItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		meni[selectItemIndex].setFillColor(sf::Color::White);
		selectItemIndex++;
		// novi odabrani
		meni[selectItemIndex].setFillColor(sf::Color::Blue);
	}
} 