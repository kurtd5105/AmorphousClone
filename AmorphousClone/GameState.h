#pragma once

// Contains all the possible game states. Game logic and stage manager need to be updated to handle these cases.
enum GameState {
	MAIN_MENU, OPTIONS, LOADING, PLAYING, LOST, WON, AWARDS, REWARDS, EXIT
};