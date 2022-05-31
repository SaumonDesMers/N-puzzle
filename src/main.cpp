#include "include.hpp"

int manhattanDistance(Game &game, Game &goal) {
	int val = 0;
	for (int i = 1; i < game.size * game.size; i++) {
		vec2 pos = game.find(i);
		vec2 goalPos = goal.find(i);
		val += abs(pos.row - goalPos.row) + abs(pos.col - goalPos.col);
	}
	return val;
}

Node *AStart(Game start, Game goal, int (*heuristique)(Game &, Game &), int nb = -1) {
	vector<Node *> open;
	vector<Game::Grid> closed;
	Node *root = new Node(start);

	open.push_back(root);

	while (--nb) {
		Node *current = open.back();
		open.pop_back();
		closed.push_back(current->game.grid);

		if (heuristique(current->game, goal) == 0)
			return current;

		current->expand();

		for (size_t i = 0; i < current->childs.size(); i++) {
			if (find(closed.begin(), closed.end(), current->childs[i]->game.grid) == closed.end())
				open.push_back(current->childs[i]);
		}

		if (open.empty())
			break;

		sort(open.begin(), open.end(), [heuristique, &goal](Node *n1, Node *n2) {
			return heuristique(n1->game, goal) > heuristique(n2->game, goal);
		});

		// cout << "\rTurn " << abs(nb);
	}
	// cout << "Stop after " << abs(nb) << " turn" << endl;
	return NULL;
}

Node *testSize3() {
	vector<int> goal_std = {1,2,3,4,5,6,7,8,0};
	vector<int> goal_snail = {1,2,3,8,0,4,7,6,5};

	vector<int> start = {2,1,3,
						 5,8,4,
						 7,6,0};
	
	Node *n = AStart(Game(start), Game(goal_std), manhattanDistance, 1000);
	return n;
}

Node *testSize4() {
	vector<int> goal_std = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
	vector<int> goal_snail = {1,2,3,4,12,13,14,5,11,0,15,6,10,9,8,7};

	// vector<int> start = {1,3,6,9,
	// 					 15,2,12,5,
	// 					 14,10,13,8,
	// 					 7,4,11,0};
	Game start = shuffleGame(Game(goal_std), 100);

	cout << "Start game: " << endl;
	start.print();
	
	Node *n = AStart(start, Game(goal_std), manhattanDistance, 1000);
	return n;
}

int main(int argc, char const *argv[])
{
	(void)argc;
	(void)argv;

	// Node *n = testSize4();

	// if (n == NULL)
	// 	cout << "No solution found after 1000 iterations" << endl;
	// else {
	// 	cout << "Solution found in ";
	// 	Node *tmp = n;
	// 	int nb = 0;
	// 	while (tmp) {
	// 		tmp = tmp->parent;
	// 		nb++;
	// 	}
	// 	cout << nb << " turn" << endl;
	// 	n->clear();
	// }

	vector<int> goal_std = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
	vector<int> goal_snail = {1,2,3,4,12,13,14,5,11,0,15,6,10,9,8,7};

	for (int i = 0; i < 10; i++) {
		Game start = randomGame(3);
		bool b = isSolvable(start, goal_std);
		Node *n = AStart(start, goal_std, manhattanDistance, 1000);

		cout << boolalpha;
		cout << b << "\t" << (n != NULL) << endl;
	}
	return 0;
}
