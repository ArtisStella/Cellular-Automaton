#include "GameOfLife.h"
#include <random>
#include <iostream>

GameOfLife::GameOfLife(Settings& settings)
	: CellularAutomaton(settings)
	, m_cells(settings.simGrid.x* settings.simGrid.y)
{
	std::mt19937 randomness((unsigned)std::time(nullptr));
	cellForEach([&](unsigned x, unsigned y)
	{
		unsigned index = getCellIndex(x, y);
		std::uniform_int_distribution<int> dist(0, 1);

		auto& cell = m_cells[index];

		cell = (Cell)dist(randomness);

		switch (cell) {
		case Cell::Alive:
			CellularAutomaton::setCellColour(x, y, sf::Color::Black);
			break;
		case Cell::Dead:
			CellularAutomaton::setCellColour(x, y, sf::Color::White);
			break;
		}
	});
}

void GameOfLife::update() {
	std::vector<std::pair<sf::Vector2i, Cell>> updates;

	cellForEach([&](unsigned x, unsigned y) {

		sf::Vector2i position(x, y);

		unsigned count = 0;

		for (int nX = -1; nX <= 1; nX++) {
			for (int nY = -1; nY <= 1; nY++)
			{
				int newX = nX + x;
				int newY = nY + y;

				if (newX == -1 || newX == (int)m_settings->simGrid.x ||
					newY == -1 || newY == (int)m_settings->simGrid.y ||
					(nX == 0 && nY == 0))
				{
					continue;
				}

				auto cell = m_cells[getCellIndex(newX, newY)];
				if (cell == Cell::Alive) {
					count++;
				}
			}
		}

		auto cell = m_cells[getCellIndex(x, y)];

		if (cell == Cell::Alive && count > 3) {
			updates.emplace_back(position, Cell::Dead);
		} 
		else if (cell == Cell::Dead && count == 3) {
			updates.emplace_back(position, Cell::Alive);
		}
		else if (cell == Cell::Alive && count < 2) {
			updates.emplace_back(position, Cell::Dead);
		}
	});


	for (auto& update : updates) {
		m_cells[getCellIndex(update.first.x, update.first.y)] = update.second;

		switch (update.second) {
		case Cell::Alive:
			CellularAutomaton::setCellColour(update.first.x, update.first.y, sf::Color::Black);
			break;
		case Cell::Dead:
			CellularAutomaton::setCellColour(update.first.x, update.first.y, sf::Color::White);
			break;
		}
	}
}
