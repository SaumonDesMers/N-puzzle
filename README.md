
# N-puzzle

This is a project from 42 whose aim is to solve an [n-puzzle](https://en.wikipedia.org/wiki/15_puzzle).

<br/>

## How does it Work

You compile it with `make` then you run `./solver`.

<br/>

## Configuration

In ***n-puzzle.conf*** you can choose between several options.

#### The algorithm :  `algorithme`

- `AStar` [A*](https://en.wikipedia.org/wiki/A*_search_algorithm)
- `IDAStar` [IDA*](https://en.wikipedia.org/wiki/Iterative_deepening_A*)

#### The heuristic : `heuristic`

- `badPlacedTiles`
- `manhattanDistance`
- `manhattanDistance+linearConflict`
- See [here](https://medium.com/swlh/looking-into-k-puzzle-heuristics-6189318eaca2) for more information.

#### The function that determines the order in which game states are visited : `sortingFunction`

- `uniformCost`: uses the heuristic added to the number of moves made so far (*depth*). 
- `greedy`: uses only the heuristic.

#### The maximum number of iterations of the algorithm : `maxIteration`

- keeping it below **1,000,000** is a good idea.

#### The weight with which the heuristic will be multiplied: `weight`.

- The greater the weight, the more important the heuristic will be with respect to depth. Only useful with `uniformCost`.

#### The starting position : `start`

- `./file.location`: with the size of the puzzle first, then each line separated by a new line and each column by a space. Example:
    ```
    3
    4 3 2
    1 8 6
    5 0 7
    ```
- `random:size`: a random position (the existence of a solution is not guaranteed).
- `suffle:size`: a position obtained by mixing the ending position (solution guaranteed)

#### The ending postion: `end`

- `snail`
- `std`
- `random`

## Performance

My program can solve up to a size 6 puzzle easily. Beyond that, you'll need to increase the maximum number of iterations, which may cause performance problems on your computer.
If you don't have enough RAM, my program will probably crash.
