#include "ewatce.h"
#include "game.h"

int main(int argc, char **argv)
{
    // Initialize Engine
    if (ewatceInitialize()) {
        // Start the Game
        LOGINF("Starting Game....");
        StartGame();
        LOGINF("Game Finished....");
    }

    // Shutdown Engine
    ewatceShutdown();

	return 0;
}


