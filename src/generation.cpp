#include "include.hpp"

// Game * randomGame(size_t size) {
//     vector<int> tab(size * size);
//     for (size_t i = 0; i < tab.size(); i++)
//         tab[i] = i;
//     srand(time(NULL));
//     random_shuffle(tab.begin(), tab.end());
//     return Game *(tab);
// }

Game *randomGame(size_t size) {
    vector<int> tab(size * size);
    for (size_t i = 0; i < tab.size(); i++)
        tab[i] = i;

    vector<int> ret;
    for (size_t i = 0; i < size * size; i++) {
        srand(time(NULL));
        int index = rand() % tab.size();
        ret.push_back(tab[index]);
        swap(tab[index], tab.back());
        tab.pop_back();
    }
    return new Game(ret);
}

Game *shuffleGame(Game *game, size_t shuffleNb) {
	cout << "Shuffling game " << shuffleNb << " times..." << endl;
    for (size_t i = 0; i < shuffleNb; i++) {
        vector<Game *> childs = game->getNextTurns();
        game = childs[rand() % childs.size()];
    }
    return game;
}

Game *goalGeneration(size_t size, string type) {
    if (type == "snail") {
        switch (size) {
            case 2: return new Game({1,2,0,3});
            case 3: return new Game({1,2,3,8,0,4,7,6,5});
            case 4: return new Game({1,2,3,4,12,13,14,5,11,0,15,6,10,9,8,7});
            case 5: return new Game({1,2,3,4,5,16,17,18,19,6,15,24,0,20,7,14,23,22,21,8,13,12,11,10,9});
        }
    }
    if (type == "random")
        return randomGame(size);
    vector<int> tab(size * size, 0);
    for (size_t i = 0; i + 1 < tab.size(); i++)
        tab[i] = i + 1;
    return new Game(tab);
}
