#include "include.hpp"

Node *AStart(Game start, Game goal, int (*heuristique)(Game &, Game &), int maxIter) {
    cout << "-------- AStart --------" << endl;
	vector<Node *> open;
	vector<Game::Grid> close;
	Node *root = new Node(start);
    Node *current = NULL;

	open.push_back(root);

    int i = 0;
	for (; i < maxIter; i++) {
		current = open.back();
		open.pop_back();
		close.push_back(current->game.grid);

		if (heuristique(current->game, goal) == 0)
			break;

		current->expand();

		for (size_t i = 0; i < current->childs.size(); i++) {
			if (find(close.begin(), close.end(), current->childs[i]->game.grid) == close.end())
				open.push_back(current->childs[i]);
		}

		if (open.empty()) {
            current = NULL;
			break;
        }

		sort(open.begin(), open.end(), [heuristique, &goal](Node *n1, Node *n2) {
			return heuristique(n1->game, goal) > heuristique(n2->game, goal);
		});
	}
    if (i == maxIter)
        current = NULL;
    cout << "Opened nodes = " << open.size() << endl;
    cout << "Closed nodes = " << close.size() << endl;
    cout << "Total nodes = " << close.size() + open.size() << endl;
    cout << "Iteration count = " << i << endl;
    cout << "------------------------" << endl;
	return current;
}
