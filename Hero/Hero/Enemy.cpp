#include "Enemy.h"

void Enemy::initVariables()
{
	// rand -> između 0 i 7 ako dobijemo 0 jos + 3 i to je min value, a max 10
	this->BrojacBodova = rand() % 8 + 3;
	this->type = 0;
	this->brzina = static_cast<float>(this->BrojacBodova / 3);
	this->hpMax = static_cast<int>(this->BrojacBodova);
	this->hp = this->hpMax;
	this->damage = this->BrojacBodova;
	this->points = this->BrojacBodova;
}

void Enemy::initShape()
{
	// shape radius (velicina oblika)
	this->shape.setRadius(this->BrojacBodova * 5);
	this->shape.setPointCount(this->BrojacBodova);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
}

Enemy::~Enemy()
{

}

// accessors
const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

// funkcije
void Enemy::update()
{
	this->shape.move(0.f, this->brzina);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}