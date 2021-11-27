#pragma once

struct Settings {

    Settings() = default;
    Settings(const sf::Vector2u& winSize, unsigned cellSize)
        : windowSize(winSize)
        , cellSize(cellSize)
    {
        init();
    }

    void init()
    {
        windowSize.x -= windowSize.x % cellSize;
        windowSize.y -= windowSize.y % cellSize;

        simGrid.x = windowSize.x / cellSize;
        simGrid.y = windowSize.y / cellSize;
    }


    sf::Vector2u windowSize = { 1280, 720 };
    sf::Vector2u simGrid;
    unsigned cellSize = 4;

    sf::Color bgColour = { 150, 150, 150 };
    sf::Color fgColour = { 25, 25, 25 };
};
