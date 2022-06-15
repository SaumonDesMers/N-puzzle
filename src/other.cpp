#include "include.hpp"

void printTab(vector<int> tab, string sep) {
    for (size_t i = 0; i < tab.size(); i++)
        cout << tab[i] << sep;
    cout << endl;
}

void getSolution(Node *n) {
	if (n == NULL)
		cout << "No solution found" << endl;
	else {
		cout << "Solution found in "<< n->depth << " turn" << endl;
		n->clear();
	}
}

vector<string> split(string str, string delim) {
	vector<string> tab;
	char *c_str = const_cast<char *>(str.c_str());
	char *token = strtok(c_str, delim.c_str());
	while(token != NULL) {
		tab.push_back(token);
		token = strtok(NULL, delim.c_str());
	}
	return tab;
}

void printTime(chrono::duration<double> time, string msg) {
	cout << msg << setprecision(3) << time.count() << "s" << endl;
}

void printTree(string prefix, Node* node) {
	for (size_t i = 0; i < node->childs.size(); i++) {
		bool isLast = i == (node->childs.size() - 1);
		cout << prefix << (!isLast ? "├─" : "└─" ) << node->childs[i]->HCost << endl;
		printTree(prefix + (isLast ? "  " : "| "), node->childs[i]);
	}
}

void printTree(Node* node) {
	cout << node->HCost << endl;
    printTree("", node);
}
