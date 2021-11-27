#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "Settings.h"

class Application;

class CellularAutomaton
{
public:
    CellularAutomaton(const Settings& settings);
    virtual ~CellularAutomaton() = default;

    virtual void input(const sf::Event& e) {}
    virtual void update() = 0;
    void render(sf::RenderWindow& window);

protected:
    unsigned getCellIndex(unsigned x, unsigned y);

    void setCellColour(int x, int y, sf::Color colour);

    template<typename Func>
    void cellForEach(Func function);

    const Settings* const m_settings;
    void addQuad(unsigned xIndex, unsigned yIndex);
    std::vector<sf::Vertex> m_cellVertexPoints;
};

template<typename Func>
void CellularAutomaton::cellForEach(Func function)
{
    for (unsigned y = 0; y < m_settings->simGrid.y; y++) {
        for (unsigned x = 0; x < m_settings->simGrid.x; x++) {
            function(x, y);
        }
    }
}