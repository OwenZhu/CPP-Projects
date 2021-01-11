#include "a_star.h"

#include <iostream>
#include <random>
#include <chrono>
#include <memory>
#include <array>

#include "eight_digits.h"


AStarAlgorithm::AStarAlgorithm()
	: queue_ (Queue()), visited_queue_ (Queue())
{
	// obtain a time-based seed
	const unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
	
	std::default_random_engine rng(seed);

	std::cout << "Init Game Board" << std::endl;

	std::shared_ptr<GameBoard> init_gb;

	std::array<int, 9> init_digits{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	
	while (true)
	{
		std::shuffle(std::begin(init_digits), std::end(init_digits), rng);

		init_gb = std::make_shared<GameBoard>(init_digits);
		
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
	std::shared_ptr<GameBoard> node;

	std::chrono::time_point<std::chrono::system_clock> start_time = std::chrono::system_clock::now();
	
	while (queue_.GetQueueLength() != 0) {
		
		node = queue_.Dequeue();

		std::cout << *node;
		
		visited_queue_.Enqueue(node);
		
		if (node->IsSolved()) {
			
			std::cout << "Searching Finish" << std::endl;
			
			break;
		}

		ExpandNode(node);

		count++;
		
		std::cout << count << " --- " << node->GetHValue() << std::endl;

		// Stop Timer For every 1000 steps
		if (count % 1000 == 0) 
		{
			std::chrono::time_point<std::chrono::system_clock> current_time = std::chrono::system_clock::now();
			const unsigned interval = 
				(unsigned)std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count();
			
			std::cout << "Time: " << interval << std::endl;
			
			system("pause");
		}
	}
}


void AStarAlgorithm::ExpandNode(std::shared_ptr<GameBoard> gb)
{

	for (const auto& m : MOVES)
	{
		std::shared_ptr<GameBoard> new_gb = std::make_shared<GameBoard>(*gb);
		
		new_gb->TakeMove(m);
		
		if (!visited_queue_.IsInQueue(new_gb) && !queue_.IsInQueue(new_gb))
			queue_.Enqueue(new_gb);
	}
}
