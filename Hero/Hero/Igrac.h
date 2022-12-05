#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

class Igrac
{
private:

	sf::Sprite sprite;
	sf::Texture texture;

	float brzKretanja;

	float attCooldown;
	float attCooldownMax;

	int hp;
	int hpMax;

	// privatne funkcije
	void initVariables();
	void initTexture();
	void initSprite();

public:
	// konstruktor, destruktor
	Igrac();
	virtual ~Igrac();

	//accessor
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;

	//modifiers
	void setPosition(const sf::Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int Value);

	//funkcije
	void move(const float dirX, const float dirY); // x i y smjerovi
	const bool canAttack();

	void updateAttCooldown();
	void update();
	void render(sf::RenderTarget& target);
};

