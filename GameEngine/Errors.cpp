#include "Errors.h"
#include <iostream>
#include <SDL/SDL.h>

namespace GameEngine {
	void fatalSDLError(std::string errorSDL, std::string errorNote) {
		std::cout << errorNote << std::endl << errorSDL << std::endl << "Press any key and hit enter to continue..." << std::endl;
		int a;
		std::cin >> a;
		exit(1);
	}

	void fatalGLError(GLenum errorGL, std::string errorNote) {
		std::cout << errorNote << std::endl << " GL Error: " << errorGL << std::endl << "Press any key and hit enter to continue..." << std::endl;
		int a;
		std::cin >> a;
		exit(1);
	}

	void fatalIOError(std::string path) {
		std::cout << "Failed to load " << path + " to buffer." << std::endl << "Press any key and hit enter to continue..." << std::endl;
		int a;
		std::cin >> a;
		exit(1);
	}

	void fatalPicoError(std::string errorPico) {
		std::cout << "Decode PNG failed with error code " << errorPico << "." << std::endl << "Press any key and hit enter to continue..." << std::endl;
		int a;
		std::cin >> a;
		exit(1);
	}

	void fatalGenericError(std::string error) {
		std::cout << error << std::endl << "Press any key and hit enter to continue..." << std::endl;
		int a;
		std::cin >> a;
		exit(1);
	}
}