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

vector<string> split(string str) {
	vector<string> tab;
	char *c_str = const_cast<char *>(str.c_str());
	char *token = strtok(c_str, " ");
	while(token != NULL) {
		tab.push_back(token);
		token = strtok(NULL, " ");
	}
	return tab;
}
