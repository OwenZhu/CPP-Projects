#include "a_star.h"

#include <iostream>
#include <random>
#include <chrono>

#include "eight_digits.h"


AStarAlgorithm::AStarAlgorithm()
{
	queue_ = new Queue();
	visited_queue_ = new Queue();

	// obtain a time-based seed
	const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	
	std::default_random_engine rng(seed);

	std::vector<int> init_digits = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	
	auto* init_gb = new GameBoard();

	std::cout << "Init Game Board" << std::endl;
	
	while (true)
	{
		std::shuffle(std::begin(init_digits), std::end(init_digits), rng);
		
		init_gb->Init(init_digits);
		
		if (init_gb->HasSolution())
		{
			break;
		}
	}

	queue_->Enqueue(init_gb);
}


void AStarAlgorithm::Run() const
{
	int count = 0;
	
	while (queue_->GetQueueLength() != 0) {
		
		auto* node = queue_->Dequeue();

		node->Display();
		
		visited_queue_->Enqueue(node);
		
		if (node->IsSolved()) {
			
			std::cout << "Searching Finish" << std::endl;
			
			break;
		}

		ExpandNode(node);

		count++;
		
		std::cout << count << " --- " << node->GetHValue() << std::endl;
	}
}


void AStarAlgorithm::ExpandNode(GameBoard* gb) const
{
	auto* new_gb = new GameBoard();
	new_gb->Init(*gb);
	new_gb->TakeMove(Move::kUp);
	if(!visited_queue_->IsInQueue(new_gb) && !queue_->IsInQueue(new_gb))
		queue_->Enqueue(new_gb);

	new_gb = new GameBoard();
	new_gb->Init(*gb);
	new_gb->TakeMove(Move::kDown);
	if (!visited_queue_->IsInQueue(new_gb) && !queue_->IsInQueue(new_gb))
		queue_->Enqueue(new_gb);

	new_gb = new GameBoard();
	new_gb->Init(*gb);
	new_gb->TakeMove(Move::kLeft);
	if (!visited_queue_->IsInQueue(new_gb) && !queue_->IsInQueue(new_gb))
		queue_->Enqueue(new_gb);

	new_gb = new GameBoard();
	new_gb->Init(*gb);
	new_gb->TakeMove(Move::kRight);
	if (!visited_queue_->IsInQueue(new_gb) && !queue_->IsInQueue(new_gb))
		queue_->Enqueue(new_gb);
}
