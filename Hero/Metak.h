#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Metak
{
private:
	sf::Sprite shape;


	sf::Vector2f direction;
	float brzKretanja;


public:
	Metak();
	Metak(sf::Texture* texture, float pos_x, float pos_y, float dir_X, float dir_Y, float brz_Kretanja);
	virtual ~Metak();

	const sf::FloatRect getBounds() const;

	void update();
	void render(sf::RenderTarget* target);
};

