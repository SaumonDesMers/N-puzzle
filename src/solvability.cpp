#include "include.hpp"

static int countInversion(vector<int> tab, vector<int> ref) {
    int nb = 0;
    for (size_t i = 0; i < tab.size(); i++) {
        for (size_t j = i + 1; j < tab.size(); j++) {
            size_t index_a = distance(ref.begin(), find(ref.begin(), ref.end(), tab[i]));
            size_t index_b = distance(ref.begin(), find(ref.begin(), ref.end(), tab[j]));
            if (index_a > index_b)
                nb++;
        }
    }
    return nb;
}

static int emptyPosFromBottom(vector<int> tab) {
    int size = sqrt(tab.size());
    int emptyIndex = distance(tab.begin(), find(tab.begin(), tab.end(), 0));
    return size - emptyIndex / size;
}

// bool isSolvable(Game game, Game goal) {
//     return isSolvable(game.toTab(), goal.toTab());
// }

bool isSolvable(vector<int> game, vector<int> goal) {
    int inversionNb = countInversion(game, goal);
    int emptyPos = emptyPosFromBottom(game);
    int size = sqrt(game.size());
    return (size % 2 == 0 && emptyPos % 2 != inversionNb % 2) || (size % 2 == 1 && inversionNb % 2 == 0);
}