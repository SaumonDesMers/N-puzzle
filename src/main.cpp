#include "include.hpp"

#define MAX_ITER 10000

	void test(Game start, Game goal, algo_fct algo, sort_fct sortSearch, heuristique_fct h) {
	cout << "#########################################\nStart = ";
	printTab(start);
	// start.print();
	// cout << "\nGoal = ";
	// printTab(goal);
	// goal.print();

	cout << (isSolvable(start, goal) ? "\nSolvable\n" : "\nNot solvable\n") << endl;

	(void)h;
	(void)sortSearch;
	algo(start, goal, uniformCostSearch, manhattanDistance, MAX_ITER);
	algo(start, goal, greedySearch, manhattanDistance, MAX_ITER);

	cout << "#########################################" << endl;
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;

	Game goal = goalGeneration(4, "snail");
	for (int i = 0; true; i++) {
		// Game start = randomGame(4);
		// Game start({4,8,5,7,1,0,6,3,2}); // Not solvable
		// Game start({5,0,1,2,4,7,8,3,6}); // Solvable
		
		Game start({5,7,11,15,1,4,14,9,12,10,13,2,8,3,6,0}); // Solvable
		

		if (!isSolvable(start, goal))
			continue;

		test(start, goal, AStart, uniformCostSearch, manhattanDistance);
		test(start, goal, AStart_withDepthUpdate, uniformCostSearch, manhattanDistance);
		break;
	}

	return 0;
}
