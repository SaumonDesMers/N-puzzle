#include "include.hpp"

static int countInversion(vector<int> tab, vector<int> ref) {
    int nb = 0;
    for (size_t i = 0; i < tab.size() - 1; i++) {
        for (size_t j = i + 1; j < tab.size(); j++) {
            if (tab[i] && tab[j]) {
                // cout << tab[i] << " - " << tab[j] << endl;

                // vector<int>::iterator it_a = find(ref.begin(), ref.end(), tab[i]);
                // vector<int>::iterator it_b = find(ref.begin(), ref.end(), tab[j]);
                // cout << boolalpha << (it_a == ref.end()) << " & " << (it_b == ref.end()) << endl;
                // cout << *it_a << " ~ " << *it_b << endl;

                size_t index_a = distance(ref.begin(), find(ref.begin(), ref.end(), tab[i]));
                size_t index_b = distance(ref.begin(), find(ref.begin(), ref.end(), tab[j]));
                // cout << "index a = " << index_a << endl;
                // cout << "index b = " << index_b << endl;
                if (index_a > index_b)
                    nb++;
            }
        }
    }
    return nb;
}

static int emptyPosFromBottom(vector<int> tab) {
    int size = sqrt(tab.size());
    int emptyIndex = distance(tab.begin(), find(tab.begin(), tab.end(), 0));
    return size - emptyIndex / size;
}

bool isSolvable(vector<int> game, vector<int> goal) {
    int inversionNb = countInversion(game, goal);
    int emptyPos = emptyPosFromBottom(game);
    int size = sqrt(game.size());
    // cout << "inv count = " << inversionNb << endl;
    return (size % 2 == 0 && emptyPos % 2 != inversionNb % 2)
        || (size % 2 == 1 && inversionNb % 2 == 0);
}