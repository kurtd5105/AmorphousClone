#include "Animation.h"
#include "Errors.h"
//#include <iostream>

namespace GameEngine {
	unsigned int Animation::getUVLocation(std::string name) { 
		for(unsigned int i = 0; i < _animNames.size(); i++) {
			if(name == _animNames[i]) {
				return i;
			}
		} 
		fatalGenericError("Animation name '" + name + "' not found.");
		return 0;
	}

	void Animation::parseData() {
		std::regex animationSet(ANIMATION_FORMAT);
		std::string dataString(_data.begin(), _data.end());
		if(!regex_match(dataString, animationSet)) {
			fatalGenericError("Animation file cannot be parsed.");
		}

		int mode = 0;
		std::vector<float> UVmM;
		std::vector<std::vector<float>> UVmMAnimSet;
		auto prev = _data.begin();
		auto curr = _data.begin();
		for(auto& token : _data) {
			switch(mode) {
			//First part is the name
			case 0:{
				//If there is a colon then that is the end of the name
				if(token == ':') {
					mode++;
					_animNames.emplace_back(prev, curr);
					++curr;
					prev = curr;
				} else {
					++curr;
				}
				break;
			}
			//Second part is the UVmM sets
			case 1:{
				//A semicolon is the end of an animation set
				if(token == ';') {
					mode = 0;
					_UVmMSets.push_back(UVmMAnimSet);
					UVmMAnimSet.clear();
					++curr;
					prev = curr;
				//A comma means the end of a float for the UVmM
				} else if(token == ',') {
					UVmM.emplace_back(std::stof(std::string(prev, curr)));
					++curr;
					prev = curr;
				//A right brace means the end of a UVmM
				} else if(token == '}') {
					UVmM.emplace_back(std::stof(std::string(prev, curr)));
					UVmMAnimSet.push_back(UVmM);
					UVmM.clear();
					++curr;
					prev = curr;
				} else if(token == '{') {
					++curr;
					prev = curr;
				} else {
					++curr;
				}
				break;
			}
			//This is the end of an animation set
			case 2:{
				mode = 0;
				++curr;
				prev = curr;
				break;
			}
			}
		}
	}
}