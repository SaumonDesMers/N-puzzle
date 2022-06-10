#include "include.hpp"
#include "config.hpp"
#include <chrono>

void printTime(chrono::duration<double> elapsed_seconds, string msg) {
	cout << msg << elapsed_seconds.count() << "s" << endl;
}

Node *AStart(Config cfg) {
    cout << "-------- AStart --------" << endl;
	vector<Node *> open;
	// vector<Node *> close;
	unordered_map<Game::Grid, Node *> close;
	Node *root = new Node(cfg.start);
    Node *current = NULL;

	auto start = chrono::system_clock::now();
	auto end = chrono::system_clock::now();

	open.push_back(root);
	root->HCost = cfg.h(root->game, cfg.goal) * cfg.weight;

    int i = 0;
	for (; i < cfg.maxIter; i++) {
		current = open.back();
		open.pop_back();
		// close.push_back(current);
		close[current->game.grid];

		if (current->HCost == 0)
			break;

		start = chrono::system_clock::now();
		current->expand();
		end = chrono::system_clock::now();
		printTime(end-start, "expand: ");

		for (size_t i = 0; i < current->childs.size(); i++) {
			Node *child = current->childs[i];

			start = chrono::system_clock::now();
			// vector<Node *>::iterator it = find_if(close.begin(), close.end(), [child](Node *n) {
			// 	return n->game.grid == child->game.grid;
			// });
			unordered_map<Game::Grid, Node *>::iterator it = close.find(child->game.grid);
    		end = chrono::system_clock::now();
			printTime(end-start, "find in close vector: ");

			if (it == close.end()) {
				child->HCost = cfg.h(child->game, cfg.goal) * cfg.weight;
				start = chrono::system_clock::now();
				vector<Node *>::iterator it = upper_bound(open.begin(), open.end(), child, cfg.sortSearch);
				open.insert(it, child);
				end = chrono::system_clock::now();
				printTime(end-start, "insert in open: ");
			}
			else if ((*it)->depth > child->depth) {
				start = chrono::system_clock::now();
				(*it)->setParent(current);
				end = chrono::system_clock::now();
				printTime(end-start, "set parent: ");
			}
		}

		if (open.empty()) {
            current = NULL;
			break;
        }
	}
    if (i == cfg.maxIter) { current = NULL; }

    // cout << "Opened nodes = " << open.size() << endl;
    // cout << "Closed nodes = " << close.size() << endl;
    // cout << "Total nodes = " << close.size() + open.size() << endl;
    cout << "Iteration count = " << i << endl;
	getSolution(current);
    cout << "------------------------" << endl;

	return current;
}
