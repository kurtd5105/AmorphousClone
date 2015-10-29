#include "Random.h"

namespace GameEngine {
	Random::Random() : screenHeight(0), screenWidth(0) {
		_mt.seed(std::chrono::system_clock::now().time_since_epoch().count());
	}


	Random::~Random() {
	}

	float Random::random(float lowerBound, float upperBound) {
		std::uniform_real_distribution<double> dist(lowerBound, upperBound);
		return dist(_mt);
	}

	int Random::randomInt(int lowerBound, int upperBound) {
		std::uniform_real_distribution<int> dist(lowerBound, upperBound);
		return dist(_mt);
	}
}