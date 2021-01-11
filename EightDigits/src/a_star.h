#pragma once

#include <vector>

#include "eight_digits.h"


const Move MOVES[] = { Move::kUp, Move::kDown, Move::kLeft, Move::kRight };


class Queue {

public:
	
	Queue() : queue_({}) { queue_.reserve(10000); }

	~Queue() { queue_.clear(); }

	int GetQueueLength() const { return queue_.size(); }

	void Enqueue(const std::shared_ptr<GameBoard>& b) { queue_.push_back(b); }
	
	std::shared_ptr<GameBoard> Dequeue() {
		std::shared_ptr<GameBoard> gb = queue_[0];
		int pos = 0;

		for (unsigned int i = 0; i < queue_.size(); i++) {
			if (queue_[i]->GetHValue() < gb->GetHValue()) {
				gb = queue_[i];
				pos = i;
			}
		}

		queue_.erase(queue_.begin() + pos);

		return gb;
	}

	bool IsInQueue(const std::shared_ptr<GameBoard> gb) const {
		for (const std::shared_ptr<GameBoard>& i : queue_) {
			if (*gb == *i) return true;
		}
		return false;
	}

private:
	std::vector<std::shared_ptr<GameBoard>> queue_;
};


class AStarAlgorithm {

public:

	AStarAlgorithm();

	void Run();
	
private:

	Queue queue_;
	
	Queue visited_queue_;

	void ExpandNode(std::shared_ptr<GameBoard>);
};
