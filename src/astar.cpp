#include "include.hpp"
#include "config.hpp"

Node *AStar(Config &cfg) {
    cout << "-------- AStar --------" << endl;
	multiset<Node *, NodeCompare> open;
	unordered_map<string, Node *> close;
	Node *root = new Node(new Game(*cfg.start)); // copy of start to avoid double free (start and goal are deleted in Config destructor)
    Node *current = NULL;

	auto start = chrono::system_clock::now();
	auto end = chrono::system_clock::now();

	root->cost.H = cfg.h(root, cfg.goal) * cfg.weight;
	root->cost.F = cfg.sortSearch(root);
	open.insert(root);

    int i = 0;
	for (; i < cfg.maxIter; i++) {
		current = *open.begin();
		open.erase(open.begin());
		close[current->game->hashKey] = current;

		if (current->cost.H == 0)
			break;

		vector<Move> nextMoves = current->game->getMoves();

		for (size_t i = 0; i < nextMoves.size(); i++) {
			Game *nextTurn = new Game(*current->game, nextMoves[i]);
			unordered_map<string, Node *>::iterator it = close.find(nextTurn->hashKey);

			if (it == close.end()) {
				Node *child = new Node(nextTurn, current);
				current->childs.push_back(child);

				child->cost.H = cfg.h(child, cfg.goal) * cfg.weight;
				child->cost.F = cfg.sortSearch(child);
				open.insert(child);
				continue;
			}
			if (it->second->cost.G > current->cost.G + 1)
				it->second->setParent(current);
			
			delete nextTurn;
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
