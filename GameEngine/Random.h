#pragma once
#include <chrono>
#include <random>

namespace GameEngine {
	class Random {
	public:
		Random();
		~Random();

		int screenWidth, screenHeight;

		void reseed() { _mt.seed(unsigned long(std::chrono::system_clock::now().time_since_epoch().count())); }

		void setScreenDimensions(int width, int height) { screenWidth = width; screenHeight = height; }
		
		float random(float lowerBound, float upperBound);
		int randomInt(int lowerBound, int upperBound);
		int randomInt(std::uniform_int_distribution<int> dist);
		static int randomIntDist(std::discrete_distribution<int> dist);
	private:
		std::mt19937 _mt;
	};
}

