#include "include.hpp"

Node *AStart(Game start, Game goal, sort_fct sortSearch, heuristique_fct h, int maxIter) {
    cout << "-------- AStart --------" << endl;
	vector<Node *> open;
	vector<Game::Grid> close;
	Node *root = new Node(start);
    Node *current = NULL;
	int weight = 10;

	open.push_back(root);
	root->HCost = h(root->game, goal) * weight;

    int i = 0;
	for (; i < maxIter; i++) {
		current = open.back();
		open.pop_back();
		close.push_back(current->game.grid);

		if (current->HCost == 0)
			break;

		current->expand();

		for (size_t i = 0; i < current->childs.size(); i++) {
			Node *child = current->childs[i];

			if (find(close.begin(), close.end(), child->game.grid) == close.end()) {
				child->HCost = h(child->game, goal) * weight;

				vector<Node *>::iterator it = upper_bound(open.begin(), open.end(), child, sortSearch);
				open.insert(it, child);
			}
		}

		if (open.empty()) {
            current = NULL;
			break;
        }
	}
    if (i == maxIter) { current = NULL; }

    // cout << "Opened nodes = " << open.size() << endl;
    // cout << "Closed nodes = " << close.size() << endl;
    // cout << "Total nodes = " << close.size() + open.size() << endl;
    cout << "Iteration count = " << i << endl;
	getSolution(current);
    cout << "------------------------" << endl;

	return current;
}

Node *AStart_withDepthUpdate(Game start, Game goal, sort_fct sortSearch, int (*h)(Game &, Game &), int maxIter) {
    cout << "-------- AStart with depth update --------" << endl;
	vector<Node *> open;
	vector<Node *> close;
	Node *root = new Node(start);
    Node *current = NULL;
	int weight = 10;

	open.push_back(root);
	root->HCost = h(root->game, goal) * weight;

    int i = 0;
	for (; i < maxIter; i++) {
		current = open.back();
		open.pop_back();
		close.push_back(current);

		if (current->HCost == 0)
			break;

		current->expand();

		for (size_t i = 0; i < current->childs.size(); i++) {
			Node *child = current->childs[i];
			vector<Node *>::iterator it = find_if(close.begin(), close.end(), [child](Node *n) {
				return n->game.grid == child->game.grid;
			});

			if (it == close.end()) {
				child->HCost = h(child->game, goal) * weight;
				vector<Node *>::iterator it = upper_bound(open.begin(), open.end(), child, sortSearch);
				open.insert(it, child);
			}
			else if ((*it)->depth > child->depth) {
					(*it)->setParent(current);
			}
		}

		if (open.empty()) {
            current = NULL;
			break;
        }
	}
    if (i == maxIter) { current = NULL; }

    // cout << "Opened nodes = " << open.size() << endl;
    // cout << "Closed nodes = " << close.size() << endl;
    // cout << "Total nodes = " << close.size() + open.size() << endl;
    cout << "Iteration count = " << i << endl;
	getSolution(current);
    cout << "------------------------" << endl;

	return current;
}
