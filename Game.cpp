#include "Game.hpp"

void Game::initVariables()
{
    this->window = nullptr;

    // Game logic
    this->points = 0;
    this->enemySpawnTimeMax = 100.f;
    this->enemySpawnTime = this->enemySpawnTimeMax;
    this->maxEnemies = 5;
}

void Game::initWindow()
{
    this->videoMode.height = 600;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, "Click Game", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setScale(sf::Vector2(0.5f, 0.5f));
    this->enemy.setFillColor(sf::Color::Green);
    this->enemy.setOutlineColor(sf::Color::Cyan);
    this->enemy.setOutlineThickness(1.f);
}

Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initEnemies();
}

Game::~Game()
{
    delete this->window;
}

const bool Game::getWindowIsOpen() const
{
    return this->window->isOpen();
}

void Game::updateEvents()
{

    while (this->window->pollEvent(this->events))
    {

        switch (this->events.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;

        case sf::Event::KeyPressed:
            if (this->events.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;

        default:
            break;
        }
    }
}

void Game::spawnEnemies()
{
    this->enemy.setPosition(static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 0.f);

    this->enemy.setFillColor(sf::Color::Green);

    this->enemies.push_back(this->enemy);
}

void Game::updateMousePos()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateEnemies()
{

    /**
         @return void

         Update the enemy spawn time and spawn enemies
         when the total amount of enemies is smaller than maximum


    */

    if (this->enemies.size() < maxEnemies)
    {
        if (this->enemySpawnTime >= this->enemySpawnTimeMax)
        {
            this->spawnEnemies();
            this->enemySpawnTime = 0.f;
        }
        else
        {
            this->enemySpawnTime += 1.f;
        }
    }

    for (int i = 0; i < this->enemies.size(); i++)
    {
        bool deleted = false;

        this->enemies[i].move(0.f, 1.f);

        // Check click them
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            if(this->enemies[i].getGlobalBounds().contains(this->mousePosView)) {
                deleted = true;
                this->points++;
                std::cout << "Points: " <<  this->points << std::endl;
            }
        }

        if(this->enemies[i].getPosition().y > this->window->getSize().y) {
            deleted = true;
        }

        if(deleted) {
            this->enemies.erase(this->enemies.begin() + i);
        }
    }
}

void Game::update()
{
    this->updateEvents();
    this->updateMousePos();
    this->updateEnemies();

    if(points >= 10) {
        this->window->close();
        std::cout << "You Win" << std::endl;
    }
}

void Game::renderEnemies()
{
    for (auto &e : this->enemies)
    {
        this->window->draw(e);
    }
}

void Game::render()
{
    this->window->clear();
    this->renderEnemies();
    this->window->display();
}