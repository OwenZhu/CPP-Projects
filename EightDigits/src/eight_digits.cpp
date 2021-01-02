#include "eight_digits.h"

#include <iostream>

int GameBoard::SumManhattanDistance()
{
	auto sum = 0;
	for (auto i = 0; i < GetBoardSize(); i++)
	{
		if (board_[i]) {
			const auto x = board_[i] / row_;
			const auto y = board_[i] % row_;

			const auto x_target = (i - 1) / row_;
			const auto y_target = (i - 1) % row_;
			sum += abs(x - x_target) + abs(y - y_target);
		}
	}
	return sum;
}

void GameBoard::SetHeuristicValue()
{
	g_value_++;
	h_value_ = SumManhattanDistance() + g_value_;
}

bool GameBoard::TakeMove(const Move move)
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
			board_[space_pos] = board_[space_pos - column_];
			board_[space_pos - column_] = 0;
			break;

		case Move::kDown:
			if (OnBottomBoundary(space_pos))
				return false;
			board_[space_pos] = board_[space_pos + column_];
			board_[space_pos + column_] = 0;
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
	for (int i = 0; i < GetBoardSize(); ++i)
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

bool GameBoard::IsSolved() const
{
	for (int i = 0; i < GetBoardSize(); i++)
		if (board_[i] != i)
			return false;
	return true;
}


int GameBoard::GetSpacePosition() const
{
	for (int i = 0; i < GetBoardSize(); i++)
		if (!board_[i])
			return i;
	return -1;
}
