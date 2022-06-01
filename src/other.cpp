#include "include.hpp"

void printTab(vector<int> tab, string sep) {
    for (size_t i = 0; i < tab.size(); i++)
        cout << tab[i] << sep;
    cout << endl;
}