#pragma once

#include <iostream>
#include <vector>


enum class Move { kLeft, kRight, kUp, kDown };

class GameBoard {

public:

	// For Display
	friend std::ostream& operator<<(std::ostream& os, const GameBoard& gb)
	{
		os << std::endl;
		for (int i = 0; i < gb.row_; ++i)
		{
			for (int j = 0; j < gb.column_; ++j)
			{
				int current_digit = gb.board_[i * gb.row_ + j];
				if (current_digit == 0)
					os << '*' << ' ';
				else
					os << current_digit << ' ';
			}
			os << std::endl;
		}
		os << std::endl;

		return os;
	};

	bool HasSolution();
	bool IsSolved();

	static bool OnRightBoundary(const int pos) { return (pos + 1) % column_ == 0; }

	static bool OnLeftBoundary(const int pos) { return pos % column_ == 0; }

	static bool OnTopBoundary(const int pos) { return pos / column_ == 0; }

	static bool OnBottomBoundary(const int pos) { return pos / column_ == row_ - 1; }

	std::vector<int> GetBoard() const { return board_; }

	inline void SetHeuristicValue();

	inline int GetSpacePosition();

	int GetHValue() const { return h_value_; }
	
	static int GetBoardSize() { return row_ * column_; }

	inline int GetGValue() const { return g_value_; }

	bool TakeMove(Move);
	
	void Init(const std::vector<int>& digits)
	{
		board_ = digits;
		h_value_ = SumManhattanDistance();
		g_value_ = 0;
	};

	void Init(const GameBoard& rhs)
	{
		board_ = rhs.GetBoard();
		h_value_ = rhs.GetHValue();
		g_value_ = rhs.GetGValue();
	}

private:
	static const int row_ = 3, column_ = 3;
	std::vector<int> board_;

	int SumManhattanDistance();
	int h_value_ = 0; // heuristic value
	int g_value_ = 0;
};
