#include "Game.h"

using namespace std;

// privatne funkcije
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Hero", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(144);
	// vsinc iskljucen
	this->window->setVerticalSyncEnabled(false);
}

void Game::initTextures()
{
	this->textures["METAK"] = new sf::Texture();
	this->textures["METAK"]->loadFromFile("Teksture/Metak1.png");
}

void Game::initGUI()
{
	//Load font
	if (!this->font.loadFromFile("Fonts/arial.ttf"))
	{
		cout << "ERROR::GAME::Failed to load font" << endl;
	}
	//Init point text
	this->pointText.setPosition(1750.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(20);
	this->pointText.setFillColor(sf::Color::White);
	this->pointText.setString("test");

	// Game Over
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(sf::Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	// Init playerGUI
	this->playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(sf::Color::Red);
	this->playerHpBar.setPosition(sf::Vector2f(20.f, 20.f));

	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));
}

void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Teksture/Background2.png"))
	{
		cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << endl;
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
}

void Game::initSistemi()
{
	this->bodovi = 0;
}

void Game::initIgrac()
{
	this->igrac = new Igrac();
}

void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;
	this->spawnTimer = this->spawnTimerMax;
}


// konstruktor i destruktor
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initGUI();
	this->initWorld();
	this->initSistemi();
	this->initIgrac();
	this->initEnemies();
}

Game::~Game()
{
	delete this->window;
	delete this->igrac;

	// izbrisati teksture
	for (auto &i : this->textures)
	{
		delete i.second;
	}
	
	// izbrisati metke
	for (auto& i : this->metak)
	{
		delete i;
	}

	// izbrisati enemy
	for (auto& i : this->enemies)
	{
		delete i;
	}
}

// funkcije
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		if (this->igrac->getHp() > 0)
		{
			this->update();
		}
		this->render();
	}
}

void Game::updatePollEvents()
{
	sf::Event event;
	while (this->window->pollEvent(event))
	{
		if (event.Event::type == sf::Event::Closed)
		{
			this->window->close();
		}
		// ako se klikne esc zatvorit ce se
		if (event.Event::KeyPressed && event.Event::key.code == sf::Keyboard::Escape)
		{
			this->window->close();
		}
	}
}

void Game::Kretanje()
{
	// pomici igraca
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		this->igrac->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		this->igrac->move(1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		this->igrac->move(0.f, -1.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		this->igrac->move(0.f, 1.f);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->igrac->canAttack())
	{
		this->metak.push_back(new Metak(this->textures["METAK"], 
			this->igrac->getPos().x, 
			this->igrac->getPos().y, 
			0.f,
			-1.f,
			5.f)
		);
	}
}

void Game::updateGUI()
{
	stringstream ss;
	ss << "Bodovi: " << this->bodovi;
	this->pointText.setString(ss.str());

	//update PlayerGUI
	float HpPercent = static_cast<float>(this->igrac->getHp()) / this->igrac->getHpMax();
	this->playerHpBar.setSize(sf::Vector2f(300.f * HpPercent, this->playerHpBar.getSize().y));
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{
	//lijeva strana svijeta collision ne mozes se maknut sa ekrana
	if (this->igrac->getBounds().left < 0.f)
	{
		this->igrac->setPosition(0.f, this->igrac->getBounds().top);
	}
	// desna strana (lijeva kordinata + width daju kordinate desne) ne moze if jer su predaleko lijeva i desna strana
	else if (this->igrac->getBounds().left + this->igrac->getBounds().width >= this->window->getSize().x)
	{
		//                              zelimo da se desna strana zabije sa desnim zidom zato -
		this->igrac->setPosition(this->window->getSize().x - this->igrac->getBounds().width, this->igrac->getBounds().top);
	}
	// gornja strana
	if (this->igrac->getBounds().top < 0.f)
	{
		this->igrac->setPosition(this->igrac->getBounds().left, 0.f);
	}
	// donja strana
	else if (this->igrac->getBounds().top + this->igrac->getBounds().height >= this->window->getSize().y)
	{
		this->igrac->setPosition(this->igrac->getBounds().left, this->window->getSize().y - this->igrac->getBounds().height);
	}
}

void Game::updateMetak()
{
	// da nejde ispod 0
	unsigned brojac = 0;
	for (auto* metci : this->metak)
	{
		metci->update();

		if (metci->getBounds().top + metci->getBounds().height < 0.f)
		{
			// izbrisan metak
			delete this->metak.at(brojac);
			this->metak.erase(this->metak.begin() + brojac);
			// broji kolko metaka je puknuto (ovaj cout)
			//cout << this->metak.size() << endl;
		}
		++brojac;
	}
}

void Game::updateEnemies()
{
	//spawning
	this->spawnTimer += 0.5f;
	// kad dode do 50 pada
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//update
	// da nejde ispod 0
	unsigned brojac = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();

		if (enemy->getBounds().top > this->window->getSize().y)
		{
			// izbrisan enemy
			delete this->enemies.at(brojac);
			this->enemies.erase(this->enemies.begin() + brojac);
		}
		// enemy player collision
		else if(enemy->getBounds().intersects(this->igrac->getBounds()))
		{
			this->igrac->loseHp(this->enemies.at(brojac)->getDamage());
			delete this->enemies.at(brojac);
			this->enemies.erase(this->enemies.begin() + brojac);
		}
		++brojac;
	}
}

void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->metak.size() && enemy_deleted == false; k++)
		{
			// collision found
			if (this->enemies[i]->getBounds().intersects(this->metak[k]->getBounds()))
			{
				this->bodovi += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->metak[k];
				this->metak.erase(this->metak.begin() + k);

				enemy_deleted = true;
			}
		}
	}
}

void Game::update()
{
	this->Kretanje();
	this->igrac->update();
	this->updateCollision();
	this->updateMetak();
	this->updateEnemies();
	this->updateCombat();
	this->updateGUI();
	this->updateWorld();
}

void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::render()
{
	// pocistimo stari frame
	this->window->clear();

	// nacrtaj svijet
	this->renderWorld();

	// crtaju se stvari
	this->igrac->render(*this->window);

	for (auto* metci : this->metak)
	{
		metci->render(this->window);
	}
	
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}

	this->renderGUI();

	//Game over screen
	if (this->igrac->getHp() <= 0)
	{
		this->window->draw(this->gameOverText);
	}

	// zavrseno crtanje
	this->window->display();
}
