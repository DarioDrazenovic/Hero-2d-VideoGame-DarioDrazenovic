#pragma once
#include <SFML/Graphics.hpp>

class Enemy
{
private:
	unsigned BrojacBodova;
	sf::CircleShape shape;
	int type;
	float brzina;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initVariables();
	void initShape();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();

	// accessors
	const sf::FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;

	//funkcije
	void update();
	void render(sf::RenderTarget* target);
};

