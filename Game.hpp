#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>


#ifndef GAME_H
#define GAME_H

class Game {
    private:
        // Variables
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event events;

        // Game Logic
        int points;
        float enemySpawnTime;
        float enemySpawnTimeMax;
        int maxEnemies;


        // Game Object
        std::vector<sf::RectangleShape> enemies;
        sf::RectangleShape enemy;

        // Mouse positions
        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;



        void initVariables();
        void initWindow();
        void initEnemies();

    public:
        // Constructors and Desctructors
        Game();

        virtual ~Game();

        // Accessor
        const bool getWindowIsOpen() const;

        // Functions
        void spawnEnemies();
        void updateEvents();
        void updateMousePos();
        void updateEnemies();
        void update();
        void renderEnemies();
        void render();
};

#endif // GAME_H