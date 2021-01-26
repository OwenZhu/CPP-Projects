#pragma once

#include <vector>
#include <memory>

#include "eight_digits.h"
#include "list.hpp"


const Move MOVES[] = { Move::kUp, Move::kDown, Move::kLeft, Move::kRight };


class AStarAlgorithm {

	using GameBoardArray = std::array<int, 9>;

public:

	AStarAlgorithm();

	AStarAlgorithm(GameBoardArray&);

	void Run();
	
private:

	List<GameBoard> list_;

	void Sort(int, GameBoard&);

	void Printl(GameBoard& g);
};
