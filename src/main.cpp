#include "include.hpp"
#include "config.hpp"

void exec(Config config) {
	

	cout << endl;
	config.print();
	cout << endl;
	config.algo(config);

	cout << "#########################################" << endl;
}

int main()
{
    srand(time(NULL));

	Config config;
	if (config.load() == EXIT_FAILURE) {
		cout << "Error loading config." << endl;
		return 1;
	}

	cout << "#########################################\n";
	config.printGames();

	if (isSolvable(config.start.toTab(), config.goal.toTab()))
		exec(config);
	else
		cout << "Game not solvable." << endl;
	
	return 0;
}
