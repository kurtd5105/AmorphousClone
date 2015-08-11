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
}