#pragma once
#include "Igrac.h"
#include <map>
#include <iostream>
#include <string>
#include "Enemy.h"
#include "Metak.h"
#include <sstream>

using namespace std;

class Game
{
private:
	// window
	sf::RenderWindow* window;

	// resources
	map<string, sf::Texture*> textures; 	// za svaki string bit ce tekstura
	vector<Metak*> metak;


	// GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	// World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Sistemi
	unsigned bodovi;

	// Igrac
	Igrac* igrac;

	// IgracGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	// stvara neprijatelje
	float spawnTimer;
	float spawnTimerMax;
	vector<Enemy*> enemies;

	// privatne funkcije
	void initWindow(); // (initialise window)
	void initTextures();
	void initGUI();
	void initWorld();
	void initSistemi();

	void initIgrac();
	void initEnemies();

public:
	// konstruktor, destruktor
	Game();
	virtual ~Game();


	// funkcije
	void run();

	void updatePollEvents();
	void Kretanje();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateMetak();
	void updateEnemies();
	void updateCombat();
	void update();
	void renderGUI();
	void renderWorld();
	// nacrta sve u updateanim pozicijama
	void render();
};

