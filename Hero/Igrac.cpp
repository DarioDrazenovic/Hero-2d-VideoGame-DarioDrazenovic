#include "Igrac.h"
#include <iostream>
using namespace std;

void Igrac::initVariables()
{
	this->brzKretanja = 7.f;
	this->attCooldownMax = 10.f;
	this->attCooldown = this->attCooldownMax;

	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Igrac::initTexture()
{
	//load teksturu iz filea
	if (!this->texture.loadFromFile("Teksture/Hero1.png"))
	{
		cout << "ERROR::IGRAC::INITTEXTURE::Could not load texture file!" << endl;
	}
}

void Igrac::initSprite()
{
	// postaviti teksturu na sprite
	this->sprite.setTexture(this->texture);

	//promijeniti velicinu spritea
	this->sprite.scale(0.5f, 0.5f);
}

Igrac::Igrac()
{
	
	this->initVariables();
	this->initTexture();
	this->initSprite();
}

Igrac::~Igrac()
{

}

const sf::Vector2f& Igrac::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Igrac::getBounds() const
{
	// vraca kopiju
	return this->sprite.getGlobalBounds();
}

const int& Igrac::getHp() const
{
	return this->hp;
}

const int& Igrac::getHpMax() const
{
	return this->hpMax;
}

void Igrac::setPosition(const sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Igrac::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Igrac::setHp(const int hp)
{
	this->hp = hp;
}

void Igrac::loseHp(const int Value)
{
	this->hp -= Value;
	if (this->hp < 0)
	{
		this->hp = 0;
	}
}

void Igrac::move(const float dirX, const float dirY)
{
	this->sprite.move(this->brzKretanja * dirX, this->brzKretanja * dirY);
}

const bool Igrac::canAttack()
{
	if (this->attCooldown >= this->attCooldownMax)
	{
		this->attCooldown = 0.5f;
		return true;
	}
	return false;
}

void Igrac::updateAttCooldown()
{
	if (this->attCooldown < this->attCooldownMax)
	{
		this->attCooldown += 1.f;
	}
}

// funkcije
void Igrac::update()
{
	this->updateAttCooldown();
}

void Igrac::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);
}
