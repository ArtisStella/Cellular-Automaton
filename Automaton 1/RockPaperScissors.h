#pragma once

#include <vector>
#include "CellularAutomata.h"
#include "Settings.h"

class RockPaperScissors : public CellularAutomaton {
	enum class Cell {
		Rock,
		Paper,
		Scissors
	};
	public:
		RockPaperScissors(Settings&);
		void update() override;

	private:
		std::vector<Cell> m_cells;

		bool canBeEaten(Cell, unsigned, unsigned, unsigned);
};
