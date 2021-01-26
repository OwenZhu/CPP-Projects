#include "eight_digits.h"

#include <iostream>


bool GameBoard::operator==(const GameBoard& rhs)
{
	return this->board_ == rhs.board_;
}

int GameBoard::SumManhattanDistance() const
{
	int sum = 0;
	for (auto i = 0; i < NUM; i++)
	{
		int x = board_[i] / 3;
		int y = board_[i] % 3;

		int target_x = i / 3;
		int target_y = i % 3;
		sum += abs(x - target_x) + abs(y - target_y);
	}
	return sum;
}


void GameBoard::SetHeuristicValue()
{
	g_value_++;
	h_value_ = SumManhattanDistance();
}


bool GameBoard::TakeMove(const Move& move)
{
	const auto space_pos = GetSpacePosition();

	switch (move)
	{
		case Move::kRight:
			if (OnRightBoundary(space_pos))
				return false;
			board_[space_pos] = board_[space_pos + 1];
			board_[space_pos + 1] = 0;
			break;

		case Move::kLeft:
			if (OnLeftBoundary(space_pos))
				return false;
			board_[space_pos] = board_[space_pos - 1];
			board_[space_pos - 1] = 0;
			break;

		case Move::kUp:
			if (OnTopBoundary(space_pos))
				return false;
			board_[space_pos] = board_[space_pos - 3];
			board_[space_pos - 3] = 0;
			break;

		case Move::kDown:
			if (OnBottomBoundary(space_pos))
				return false;
			board_[space_pos] = board_[space_pos + 3];
			board_[space_pos + 3] = 0;
			break;

		default:
			return false;
	}
	SetHeuristicValue();
	return true;
}


bool GameBoard::HasSolution() const
{
	int count = 0;
	for (int i = 0; i < NUM; ++i)
	{
		int current_digit = board_[i];
		for (int j = 0; j < i; j++) {
			int prev_digit = board_[j];
				if (current_digit && prev_digit && current_digit < prev_digit)
					count++;
		}
	}
	return count % 2 ? false : true;
}


int GameBoard::GetSpacePosition() const
{
	for (int i = 0; i < NUM; i++)
		if (!board_[i])
			return i;
	return -1;
}

std::ostream& operator<<(std::ostream& os, const GameBoard& gb)
{
	int digit;

	os << std::endl;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			digit = gb.board_[i * 3 + j];

			if (digit == 0)
				os << '*' << ' ';
			else
				os << digit << ' ';
		}
		os << std::endl;
	}
	os << std::endl;

	return os;
};
