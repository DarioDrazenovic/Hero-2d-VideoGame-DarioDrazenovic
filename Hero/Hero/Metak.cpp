#include "Metak.h"

Metak::Metak()
{
}


Metak::Metak(sf::Texture* texture, float pos_x, float pos_y, float dir_X, float dir_Y, float brz_Kretanja)
{
	this->shape.setTexture(*texture);
	
	this->shape.setPosition(pos_x, pos_y);
	this->direction.x = dir_X;
	this->direction.y = dir_Y;
	this->brzKretanja = brz_Kretanja;
}

Metak::~Metak()
{

}

const sf::FloatRect Metak::getBounds() const
{
	return this->shape.getGlobalBounds();
}

void Metak::update()
{
	// updateanje kretanja
	this->shape.move(this->brzKretanja * this->direction);
}

void Metak::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
