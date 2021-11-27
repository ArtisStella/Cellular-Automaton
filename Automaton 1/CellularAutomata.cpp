#include "CellularAutomata.h"

#include <SFML/Graphics.hpp>

CellularAutomaton::CellularAutomaton(const Settings& settings)
	:m_settings(&settings)
{
	m_cellVertexPoints.reserve(settings.simGrid.x * settings.simGrid.y * 4);
	for (unsigned y = 0; y < settings.simGrid.y; y++) {
		for (unsigned x = 0; x < settings.simGrid.x; x++) {
			addQuad(x, y);
		}
	}
}

void CellularAutomaton::render(sf::RenderWindow& window) {
	window.draw(m_cellVertexPoints.data(), m_cellVertexPoints.size(), sf::Quads);
}

unsigned CellularAutomaton::getCellIndex(unsigned x, unsigned y) {
	return x + y * m_settings->simGrid.x;
}

void CellularAutomaton::setCellColour(int x, int y, sf::Color color) {
	auto index = getCellIndex(x, y) * 4;
	for (int i = 0; i < 4; i++) {
		m_cellVertexPoints[index + i].color = color;
	}
}

void CellularAutomaton::addQuad(unsigned xIndex, unsigned yIndex) {
    float cellSize = (float)m_settings->cellSize;
    sf::Vertex topLeft;
    sf::Vertex topRight;
    sf::Vertex bottomLeft;
    sf::Vertex bottomRight;

    float pixelX = xIndex * cellSize;
    float pixelY = yIndex * cellSize;

    topLeft.position        = { pixelX,               pixelY };
    topRight.position       = { pixelX + cellSize,    pixelY };
    bottomLeft.position     = { pixelX,               pixelY + cellSize };
    bottomRight.position    = { pixelX + cellSize,    pixelY + cellSize };

    topLeft.color       = m_settings->fgColour;
    topRight.color      = m_settings->fgColour;
    bottomLeft.color    = m_settings->fgColour;
    bottomRight.color   = m_settings->fgColour;

    m_cellVertexPoints.push_back(topLeft);
    m_cellVertexPoints.push_back(bottomLeft);
    m_cellVertexPoints.push_back(bottomRight);
    m_cellVertexPoints.push_back(topRight);
}
