#include "include.hpp"

Game randomGame(size_t size) {
    vector<int> tab(size * size);
    for (size_t i = 0; i < tab.size(); i++)
        tab[i] = i;
    random_shuffle(tab.begin(), tab.end());
    return Game(tab, size);
}

Game shuffleGame(Game game, size_t shuffleNb) {
    for (size_t i = 0; i < shuffleNb; i++) {
        vector<Game> childs = game.getNextTurns();
        srand(time(NULL));
        game = childs[rand() % childs.size()];
    }
    return game;
}
