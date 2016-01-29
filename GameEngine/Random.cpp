#include "Random.h"

namespace GameEngine {
	Random::Random() : screenHeight(0), screenWidth(0) {
		_mt.seed((unsigned long)std::chrono::system_clock::now().time_since_epoch().count());
	}


	Random::~Random() {
	}

	float Random::random(float lowerBound, float upperBound) {
		std::uniform_real_distribution<float> dist(lowerBound, upperBound);
		return dist(_mt);
	}

	int Random::randomInt(const int lowerBound, const int upperBound) {
		std::uniform_int_distribution<int> dist(lowerBound, upperBound);
		return dist(_mt);
	}

	int Random::randomInt(std::uniform_int_distribution<int> dist) {
		return dist(_mt);
	}

	int Random::randomIntDist(std::discrete_distribution<int> dist) {
		//std::discrete_distribution<int> distb{0,1,1,1};
		std::mt19937 gen((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
		return dist(gen);
	}
}