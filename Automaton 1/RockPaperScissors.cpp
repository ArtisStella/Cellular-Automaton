#include "RockPaperScissors.h"
#include <random>
#include <iostream>

RockPaperScissors::RockPaperScissors(Settings& settings)
	: CellularAutomaton(settings)
	, m_cells(settings.simGrid.x * settings.simGrid.y)
{
	std::mt19937 randomness((unsigned)std::time(nullptr));
	cellForEach([&](unsigned x, unsigned y) 
	{
		unsigned index = getCellIndex(x, y);
		std::uniform_int_distribution<int> dist(0, 2);

		auto& cell = m_cells[index];

		cell = (Cell) dist(randomness);

		switch (cell){
		case Cell::Rock:
			CellularAutomaton::setCellColour(x, y, sf::Color::Blue);
			break;
		case Cell::Paper:
			CellularAutomaton::setCellColour(x, y, sf::Color::Green);
			break;
		case Cell::Scissors:
			CellularAutomaton::setCellColour(x, y, sf::Color::Red);
			break;
		}
	});
}

void RockPaperScissors::update(){
	std::vector<std::pair<sf::Vector2i, Cell>> updates;

	cellForEach([&](unsigned x, unsigned y)
	{
		sf::Vector2i position(x, y);
		unsigned r_count = 0, p_count = 0, s_count = 0;
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
				switch (cell) {
				case Cell::Rock:
					r_count++;
					break;
				case Cell::Paper:
					p_count++;
					break;
				case Cell::Scissors:
					s_count++;
					break;
				}
			}
		}
		
		auto cell = m_cells[getCellIndex(x, y)];

		if (canBeEaten(cell, r_count, p_count, s_count)) {
			switch (cell) {
			case Cell::Rock:
				updates.emplace_back(position, Cell::Paper);
				break;
			case Cell::Paper:
				updates.emplace_back(position, Cell::Scissors);
				break;
			case Cell::Scissors:
				updates.emplace_back(position, Cell::Rock);
				break;
			}
		}
	});
	

	for (auto& update : updates) {
		m_cells[getCellIndex(update.first.x, update.first.y)] = update.second;

		switch (update.second) {
		case Cell::Rock:
			CellularAutomaton::setCellColour(update.first.x, update.first.y, sf::Color::Blue);
			break;
		case Cell::Paper:
			CellularAutomaton::setCellColour(update.first.x, update.first.y, sf::Color::Green);
			break;
		case Cell::Scissors:
			CellularAutomaton::setCellColour(update.first.x, update.first.y, sf::Color::Red);
			break;
		}
	}
}


bool RockPaperScissors::canBeEaten(Cell cell, unsigned r_count, unsigned p_count, unsigned s_count) {

	unsigned threshold = 2;

	switch (cell) {
	case Cell::Rock:
		if (p_count > threshold)
			return true;
		break;
	case Cell::Paper:
		if (s_count > threshold)
			return true;
		break;
	case Cell::Scissors:
		if (r_count > threshold)
			return true;
		break;
	}

	return false;
}
