#pragma once
#define ANIMATION_FORMAT "([[:alnum:]]+:(\\{([[:digit:]](.[[:digit:]]+)?,){3}[[:digit:]](.[[:digit:]]+)?\\})+;)+"
#include <regex>
#include <vector>

namespace GameEngine {
	class Animation {
	public:
		Animation() {}
		~Animation() {}

		void init(std::vector<unsigned char> data) { _data = data; }
		void parseData();

		//Getters
		std::vector<float>* getUVSet(int set, int step) { return &_UVmMSets[set][step]; }
		unsigned int getUVLocation(std::string name);
		int getAnimSize(int set) { return _UVmMSets[set].size(); }

	private:
		std::vector<std::vector<std::vector<float>>> _UVmMSets;
		std::vector<std::string> _animNames;
		std::vector<unsigned char> _data;
	};
}