#include "include.hpp"

Node *AStart(
	Game start,
	Game goal,
	sort_fct sortSearch,
	int (*h)(Game &, Game &),
	int maxIter
) {
    // cout << "-------- AStart --------" << endl;
	vector<Node *> open;
	vector<Game::Grid> close;
	Node *root = new Node(start);
    Node *current = NULL;

	open.push_back(root);
	root->HCost = h(root->game, goal);

    int i = 0;
	for (; i < maxIter; i++) {
		current = open.back();
		open.pop_back();
		close.push_back(current->game.grid);

		if (current->HCost == 0)
			break;

		current->expand();

		for (size_t i = 0; i < current->childs.size(); i++) {
			if (find(close.begin(), close.end(), current->childs[i]->game.grid) == close.end()) {
				open.push_back(current->childs[i]);
				current->childs[i]->HCost = h(current->childs[i]->game, goal);
			}
		}

		///   /!\ UPDATE GCOST

		if (open.empty()) {
            current = NULL;
			break;
        }

		sort(open.begin(), open.end(), sortSearch);
	}
    if (i == maxIter)
        current = NULL;
    // cout << "Opened nodes = " << open.size() << endl;
    // cout << "Closed nodes = " << close.size() << endl;
    // cout << "Total nodes = " << close.size() + open.size() << endl;
    // cout << "Iteration count = " << i << endl;
    // cout << "------------------------" << endl;
	return current;
}
