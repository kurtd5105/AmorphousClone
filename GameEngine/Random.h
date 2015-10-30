#pragma once
#include <chrono>
#include <random>


namespace GameEngine {
	class Random {
	public:
		Random();
		~Random();

		int screenWidth, screenHeight;

		void reseed();
		void setScreenDimensions(int width, int height) { screenWidth = width; screenHeight = height; }
		
		float random(float lowerBound, float upperBound);
		int randomInt(int lowerBound, int upperBound);
		int randomIntDist(std::discrete_distribution<int> dist);
	private:
		std::mt19937 _mt;
	};
}

