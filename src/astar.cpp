#include "include.hpp"
#include "config.hpp"

Node *AStar(Config &cfg) {
    cout << "-------- AStar --------" << endl;
	multimap<int, Node *> open;
	unordered_map<string, Node *> close;
	Node *root = new Node(new Game(*cfg.start));
    Node *current = NULL;

	auto start = chrono::system_clock::now();
	auto end = chrono::system_clock::now();

	root->HCost = cfg.h(root->game, cfg.goal) * cfg.weight;
	open.insert(make_pair(cfg.sortSearch(root), root));

    int i = 0;
	for (; i < cfg.maxIter; i++) {
		// printTree(root);
		// string str;
		// getline(cin, str);
		// system("clear");
		current = open.begin()->second;
		open.erase(open.begin());
		close[current->game->hashKey] = current;

		if (current->HCost == 0)
			break;

		vector<Game *> nextTurns = current->game->getNextTurns();

		for (size_t i = 0; i < nextTurns.size(); i++) {
			unordered_map<string, Node *>::iterator it = close.find(nextTurns[i]->hashKey);

			if (it == close.end()) {
				Node *child = new Node(nextTurns[i], current, current->depth + 1);
				current->childs.push_back(child);

				child->HCost = cfg.h(child->game, cfg.goal) * cfg.weight;
				open.insert(make_pair(cfg.sortSearch(child), child));
				continue;
			}
			if (it->second->depth > current->depth + 1)
				it->second->setParent(current);
			
			delete nextTurns[i];
		}

		if (open.empty()) {
            current = NULL;
			break;
        }
	}
    if (i == cfg.maxIter) { current = NULL; }

	end = chrono::system_clock::now();

    cout << "Opened nodes = " << open.size() << endl;
    cout << "Closed nodes = " << close.size() << endl;
    cout << "Total nodes = " << close.size() + open.size() << endl;
    cout << "Iteration count = " << i << endl;
	getSolution(current);
	printTime(end-start, "execution time = ");
    cout << "------------------------" << endl;

	root->clear();
	return NULL;
}
