#include "a_star.h"

#include <iostream>
#include <random>
#include <chrono>

#include "eight_digits.h"


AStarAlgorithm::AStarAlgorithm()
	: queue_ (Queue()), visited_queue_ (Queue())
{
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

	queue_.Enqueue(init_gb);
}


void AStarAlgorithm::Run()
{
	int count = 0;
	
	while (queue_.GetQueueLength() != 0) {
		
		auto* node = queue_.Dequeue();

		std::cout << *node;
		
		visited_queue_.Enqueue(node);
		
		if (node->IsSolved()) {
			
			std::cout << "Searching Finish" << std::endl;
			
			break;
		}

		ExpandNode(node);

		count++;
		
		std::cout << count << " --- " << node->GetHValue() << std::endl;

		delete node;
	}
}


void AStarAlgorithm::ExpandNode(GameBoard* gb)
{

	for (const auto& m : MOVES)
	{
		auto* new_gb = new GameBoard();
		
		new_gb->Init(*gb);
		
		new_gb->TakeMove(m);
		
		if (!visited_queue_.IsInQueue(new_gb) && !queue_.IsInQueue(new_gb))
			queue_.Enqueue(new_gb);
	}
}
