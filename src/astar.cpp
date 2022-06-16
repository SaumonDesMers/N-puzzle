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
		// printTree(root);
		// string str;
		// getline(cin, str);
		// system("clear");
		current = open.begin()->second;
		open.erase(open.begin());
		close[current->game] = current;

		if (current->HCost == 0)
			break;

		vector<Game> nextTurns = current->game.getNextTurns();

		for (size_t i = 0; i < nextTurns.size(); i++) {
			unordered_map<string, Node *>::iterator it = close.find(nextTurns[i]);

			if (it == close.end()) {
				Node *child = new Node(nextTurns[i], current, current->depth + 1);
				current->childs.push_back(child);

				child->HCost = cfg.h(child->game, cfg.goal) * cfg.weight;
				open.insert(make_pair(child->HCost, child));
			}
			else if (it->second->depth > current->depth + 1) {
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

	// printTree(root);
    cout << "Opened nodes = " << open.size() << endl;
    cout << "Closed nodes = " << close.size() << endl;
    cout << "Total nodes = " << close.size() + open.size() << endl;
    cout << "Iteration count = " << i << endl;
	getSolution(current);
	printTime(end-start, "execution time = ");
    cout << "------------------------" << endl;

	return NULL;
}
