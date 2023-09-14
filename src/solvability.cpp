#include "include.hpp"

static int countInversion(vector<int> &tab, vector<int> &goal) {
    int count = 0;
    for (size_t i = 0; i < tab.size() - 1; i++) {
        for (size_t j = i + 1; j < tab.size(); j++) {
            if (tab[i] && tab[j]) {
                // cout << tab[i] << " - " << tab[j] << endl;

                // vector<int>::iterator it_a = find(goal.begin(), goal.end(), tab[i]);
                // vector<int>::iterator it_b = find(goal.begin(), goal.end(), tab[j]);
                // cout << boolalpha << (it_a == goal.end()) << " & " << (it_b == goal.end()) << endl;
                // cout << *it_a << " ~ " << *it_b << endl;

                size_t index_a = distance(goal.begin(), find(goal.begin(), goal.end(), tab[i]));
                size_t index_b = distance(goal.begin(), find(goal.begin(), goal.end(), tab[j]));
                // cout << "index a = " << index_a << endl;
                // cout << "index b = " << index_b << endl;
                if (index_a > index_b)
                    count++;
            }
        }
    }
    return count;
}

static int emptyPosFromBottom(vector<int> tab) {
    int size = sqrt(tab.size());
    int emptyIndex = distance(tab.begin(), find(tab.begin(), tab.end(), 0));
    return size - emptyIndex / size;
}

bool isSolvable(vector<int> start, vector<int> goal) {
    int inversionCount = countInversion(start, goal);
    int emptyPos = emptyPosFromBottom(start);
    int size = sqrt(start.size());
	cout << "inversionCount = " << inversionCount << endl;
	cout << "emptyPos = " << emptyPos << endl;
	cout << "size = " << size << endl;
    return (size % 2 == 0 && emptyPos % 2 != inversionCount % 2)
        || (size % 2 == 1 && inversionCount % 2 == 0);
}