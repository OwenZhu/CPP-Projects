#pragma once

#include <iostream>
#include <array>


enum class Move { kLeft, kRight, kUp, kDown };


class GameBoard {

private:
	
	static const int row_ = 3, column_ = 3;

	static const int size_ = row_ * column_;

	std::array<int, row_ * column_> board_;

	int SumManhattanDistance() const;
	
	int h_value_ = 0; // heuristic value
	
	int g_value_ = 0;

public:

	GameBoard(const std::array<int, size_>& digits):
		board_(digits)
	{
		h_value_ = SumManhattanDistance();
		g_value_ = 0;
	};


	bool operator==(const GameBoard& rhs);

	// For Display
	friend std::ostream& operator<<(std::ostream& os, const GameBoard& gb);

	bool HasSolution() const;

	bool IsSolved() const;

	static bool OnRightBoundary(const int& pos) { return (pos + 1) % column_ == 0; }

	static bool OnLeftBoundary(const int& pos) { return pos % column_ == 0; }

	static bool OnTopBoundary(const int& pos) { return pos / column_ == 0; }

	static bool OnBottomBoundary(const int& pos) { return pos / column_ == row_ - 1; }

	inline void SetHeuristicValue();

	inline int GetSpacePosition() const;

	int GetHValue() const { return h_value_; }

	inline int GetGValue() const { return g_value_; }

	bool TakeMove(const Move&);

};
