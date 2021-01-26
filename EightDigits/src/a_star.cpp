#include "a_star.h"

#include <iostream>
#include <random>
#include <chrono>
#include <memory>
#include <array>
#include <algorithm>

#include "eight_digits.h"


class Timer {

private:
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> end;
	std::chrono::time_point<std::chrono::system_clock> current;

public:
	Timer() {
		start = std::chrono::system_clock::now();
	}

	virtual ~Timer() {
		end = std::chrono::system_clock::now();
		auto duration =
			std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

		std::cout << "Time: " << duration << std::endl;
	}

	void Pause() {
		current = std::chrono::system_clock::now();
		auto duration =
			std::chrono::duration_cast<std::chrono::milliseconds>(current - start).count();

		std::cout << "Time: " << duration << std::endl;
	}
};


AStarAlgorithm::AStarAlgorithm()
{
	std::cout << "Init Game Board" << std::endl;
	
	// obtain a time-based seed
	const unsigned seed = (unsigned)std::chrono::system_clock::now().time_since_epoch().count();
	
	std::default_random_engine rng(seed);

	std::cout << "Init Game Board" << std::endl;

	std::shared_ptr<GameBoard> init_gb;

	GameBoardArray init_digits{ 4, 0, 1, 2, 5, 8, 7, 6, 3 };

	init_gb = std::make_shared<GameBoard>(init_digits);
	
	while (true)
	{
		std::shuffle(std::begin(init_digits), std::end(init_digits), rng);

		init_gb = std::make_shared<GameBoard>(init_digits);
		
		if (init_gb->HasSolution())
		{
			break;
		}
	}

	list_.Append(GameBoard(*init_gb));
}


AStarAlgorithm::AStarAlgorithm(GameBoardArray& digits)
{
	std::cout << "Init Game Board" << std::endl;
	list_.Append(GameBoard(digits));
}


void AStarAlgorithm::Sort(int index, GameBoard& elem)
{
	for (index++; index < list_.Length(); index++)
	{
		GameBoard temp = list_.Pop(index);
		if (elem.F() <= temp.F())
			break;
	}
	list_.Insert(elem, index);
}


void AStarAlgorithm::Printl(GameBoard& g)
{
	GameBoard tmp = g;
	std::vector<GameBoard> traj_list = {g};
	
	while (tmp.last != -1)
	{
		tmp = list_.Pop(tmp.last);
		traj_list.push_back(tmp);
	}

	std::reverse(traj_list.begin(), traj_list.end());
	for (auto& i : traj_list) {
		std::cout << i;
	}
}


void AStarAlgorithm::Run()
{
	Timer timer;

	int head = 0, tail = 0;
	while (head <= tail){
		
		GameBoard g = list_.Pop(head);
		
		if (g.H() == 0)
		{
			std::cout << "Done!" << std::endl;
			Printl(g);
			return;
		}

		for (const auto& m : MOVES)
		{
			GameBoard new_gb = g;

			if (new_gb.TakeMove(m))
			{
				int index = list_.Find(new_gb);

				if (index < head)
					continue;

				new_gb.last = head;

				if (index <= tail)
				{
					GameBoard temp = list_.Pop(index);
					if (temp.G() > new_gb.G())
						list_.Insert(new_gb, index);
					continue;
				}

				Sort(head, new_gb);

				tail++;
			}
		}

		head++;

		if (head % 100 == 0) {
			std::cout << head << " -> " << tail << std::endl;
			timer.Pause();
		}
	}
}
