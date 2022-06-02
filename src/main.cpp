#include "include.hpp"

void getSolution(Node *n) {
	if (n == NULL)
		cout << "No solution found" << endl;
	else {
		cout << "Solution found in ";
		Node *tmp = n;
		int nb = 0;
		while (tmp) {
			tmp = tmp->parent;
			nb++;
		}
		cout << nb << " turn" << endl;
		n->clear();
	}
}

void test(
	Game start,
	Game goal,
	algo_fct algo,
	sort_fct sortSearch,
	heuristique_fct h
) {
	cout << "#########################################\nStart = ";
	printTab(start);
	// start.print();
	// cout << "\nGoal = ";
	// printTab(goal);
	// goal.print();

	cout << (isSolvable(start, goal) ? "\nSolvable\n" : "\nNot solvable\n") << endl;

	(void)sortSearch;
	Node *n = algo(start, goal, uniformCostSearch_withCost, h, 2000);
	getSolution(n);
	n = algo(start, goal, uniformCostSearch_withDepth, h, 2000);
	getSolution(n);
	n = algo(start, goal, greedySearch, h, 2000);
	getSolution(n);

	cout << "#########################################" << endl;;
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;

	Game goal = goalGeneration(3);
	for (int i = 0; i < 10; i++) {
		Game start = randomGame(3);
		// Game start({2,6,4,8,1,5,3,0,7});

		test(start, goal, AStart, uniformCostSearch_withCost, manhattanDistance);
	}

	return 0;
}
