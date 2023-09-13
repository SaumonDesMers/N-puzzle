#include "include.hpp"
#include "config.hpp"
#include <climits>
#include <unordered_map>


Node * recursiveBrainless(Node *current, Config cfg) {
	static int I = 0;
	if (I++ >= cfg.maxIter)
		return NULL;
	static unordered_map<string, Node *> explored;
	unordered_map<string, Node *>::iterator it = explored.find(current->game.hashKey);
	if (it == explored.end()) {
		current->HCost = cfg.h(current->game, cfg.goal);
		current->expand();
		explored[current->game.hashKey] = current;
	}
	else
		return NULL;

	if (current->HCost == 0)
		return current;
	
	sort(current->childs.begin(), current->childs.end(), [](Node *n1, Node *n2) {
		return n1->HCost < n2->HCost;
	});

	for (size_t i = 0; i < current->childs.size(); i++) {
		Node *n = recursiveBrainless(current->childs[i], cfg);
		if (n != NULL)
			return n;
	}
	return NULL;
}

Node *recursiveBrainless(Config cfg) {
    cout << "------- recusive brainless -------" << endl;
	Node *root = new Node(cfg.start);
	Node *n = recursiveBrainless(root, cfg);
	getSolution(n);
    cout << "----------------------------------" << endl;
	return NULL;
}

Node *iterativeBrainless(Config cfg) {
    cout << "------- iterative brainless -------" << endl;
	unordered_map<string, Node *> close;
	Node *root = new Node(cfg.start);
	Node *current = root;
	current->HCost = cfg.h(current->game, cfg.goal);
	int i = 0;
	for (; i < cfg.maxIter; i++) {

		cout << "HCost = " << current->HCost << endl;

		if (cfg.h(current->game, cfg.goal) == 0)
			break;
		
		if (close.count(current->game.hashKey) > 0) {
			cout << "Error loop reach" << endl;
			return NULL;
		}

		close[current->game.hashKey] = current;
		
		current->expand();
		for (size_t i = 0; i < current->childs.size(); i++)
			current->childs[i]->HCost = cfg.h(current->childs[i]->game, cfg.goal) * cfg.weight;
		
		current = *min_element(current->childs.begin(), current->childs.end(), [](Node *n1, Node *n2) {
			return n1->HCost < n2->HCost;
		});
	}
    if (i == cfg.maxIter) { current = NULL; }

	cout << "Iteration count = " << i << endl;
	getSolution(current);
    cout << "----------------------------------" << endl;
	return NULL;
}
