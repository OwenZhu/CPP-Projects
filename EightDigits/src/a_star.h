#pragma once

#include "eight_digits.h"


const Move MOVES[] = { Move::kUp, Move::kDown, Move::kLeft, Move::kRight };


class Queue {

public:
	
	Queue() { queue_ = {}; };

	int GetQueueLength() const { return queue_.size(); }

	void Enqueue( GameBoard* b) { queue_.push_back(b); }
	
	GameBoard* Dequeue() {
		auto* gb = queue_[0];
		int pos = 0;

		for (int i = 0; i < queue_.size(); i++) {
			if (queue_[i]->GetHValue() < gb->GetHValue()) {
				gb = queue_[i];
				pos = i;
			}
		}

		queue_.erase(queue_.begin() + pos);

		return gb;
	}

	bool IsInQueue(const GameBoard* gb) const {
		for (auto* i : queue_) {
			if (gb->GetBoard() == i->GetBoard()) {
				return true;
			}
		}
		return false;
	}

private:
	std::vector<GameBoard*> queue_;
};


class AStarAlgorithm {

public:
	AStarAlgorithm();
	void Run() const;
	
private:
	Queue* queue_;
	Queue* visited_queue_;

	void ExpandNode(GameBoard*) const;
};
