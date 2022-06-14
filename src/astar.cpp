#include "include.hpp"
#include "config.hpp"

Node *AStar(Config cfg) {
    cout << "-------- AStar --------" << endl;
	multimap<int, Node *> open;
	unordered_map<string, Node *> close;
	Node *root = new Node(cfg.start);
    Node *current = NULL;

	auto start = chrono::system_clock::now();
	auto end = chrono::system_clock::now();

	root->HCost = cfg.h(root->game, cfg.goal) * cfg.weight;
	open.insert(make_pair(root->HCost, root));

    int i = 0;
	for (; i < cfg.maxIter; i++) {
		current = open.begin()->second;
		open.erase(open.begin());
		close[current->game] = current;

		if (current->HCost == 0)
			break;

		current->expand();

		for (size_t i = 0; i < current->childs.size(); i++) {
			Node *child = current->childs[i];

			unordered_map<string, Node *>::iterator it = close.find(child->game);

			if (it == close.end()) {
				child->HCost = cfg.h(child->game, cfg.goal) * cfg.weight;
				open.insert(make_pair(child->HCost, child));
			}
			else if (it->second->depth > child->depth) {
				it->second->setParent(current);
			}
		}

		if (open.empty()) {
            current = NULL;
			break;
        }
		// cout << "HCost = " << current->HCost << endl;
	}
    if (i == cfg.maxIter) { current = NULL; }

	end = chrono::system_clock::now();

    // cout << "Opened nodes = " << open.size() << endl;
    // cout << "Closed nodes = " << close.size() << endl;
    cout << "Total nodes = " << close.size() + open.size() << endl;
    cout << "Iteration count = " << i << endl;
	getSolution(current);
	printTime(end-start, "execution time = ");
    cout << "------------------------" << endl;

	return NULL;
}