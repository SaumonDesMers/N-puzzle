#include "include.hpp"

void test(Game start, Game goal,
		Node *(*algo)(Game start, Game goal, int (*heuristique)(Game &, Game &), int nb),
		int (*heuristique)(Game &, Game &)) {

	cout << "Start = ";
	printTab(start);
	start.print();
	cout << "\nGoal = ";
	printTab(goal);
	goal.print();

	cout << (isSolvable(start, goal) ? "\nSolvable\n" : "\nNot solvable\n") << endl;

	Node *n = algo(start, goal, heuristique, 1000);

	if (n == NULL)
		cout << "\nNo solution found" << endl;
	else {
		cout << "\nSolution found in ";
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

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;

	Game goal = goalGeneration(3);
	Game start = randomGame(3);

	test(start, goal, AStart, manhattanDistance);

	return 0;
}
