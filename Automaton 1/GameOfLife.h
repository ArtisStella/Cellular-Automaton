#pragma once

#include <vector>
#include "CellularAutomata.h"
#include "Settings.h"

class GameOfLife : public CellularAutomaton {
	enum class Cell {
		Alive, Dead
	};
public:
	GameOfLife(Settings&);
	void update() override;

private:
	std::vector<Cell> m_cells;
};