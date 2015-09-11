#pragma once
#include <vector>

namespace GameEngine {
	class Animation {
	public:
		Animation() {}
		~Animation() {}

		void init(std::vector<std::string> animNames, std::vector<std::vector<std::vector<float>>> UVmMSets) { _UVmMSets = UVmMSets; _animNames = animNames; }

		std::vector<float>* getUVSet(int set, int step) { return &_UVmMSets[set][step]; }
		int getUVLocation(std::string name);
		int getAnimSize(int set) { return _UVmMSets[set].size(); }

	private:
		std::vector<std::vector<std::vector<float>>> _UVmMSets;
		std::vector<std::string> _animNames;
	};
}