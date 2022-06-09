#include "include.hpp"

#define MAX_ITER 10000

	void test(Game start, Game goal, algo_fct algo, sort_fct sortSearch, heuristique_fct h) {
	cout << "#########################################\nStart = ";
	printTab(start);
	start.print();
	// start.print();
	// cout << "\nGoal = ";
	// printTab(goal);
	// goal.print();

	(void)h;
	(void)sortSearch;
	cout << "\nUniformCost:" << endl;
	algo(start, goal, uniformCostSearch, h, MAX_ITER);
	cout << "Greedy:" << endl;
	algo(start, goal, greedySearch, h, MAX_ITER);

	cout << "#########################################" << endl;
}

int main(int argc, char const *argv[])
{
	Game start;
	if (argc == 1) {
		// start = randomGame(4);
		// start = {4,8,5,7,1,0,6,3,2}; // Not solvable
		// start = {5,0,1,2,4,7,8,3,6}; // Solvable
		
		start = {5,7,11,15,1,4,14,9,12,10,13,2,8,3,6,0}; // Solvable
	}
	else if (!parseGame(argv[1], start)) {
		cout << "There is a problem with the input file" << endl;
		return 1;
	}

	Game goal = goalGeneration(start.size, "snail");

	// if (isSolvable(start, goal)) {
	// 	cout << "Start solving..." << endl;
	// 	test(start, goal, AStart, uniformCostSearch, manhattanDistance);
	// 	test(start, goal, AStart, uniformCostSearch, manDist_linCon);
	// 	// test(start, goal, AStart_withDepthUpdate, uniformCostSearch, manhattanDistance);
	// }
	// else {
	// 	cout << "Game not solvable" << endl;
	// }
	
	return 0;
}
