#include "Animation.h"
#include "Errors.h"

namespace GameEngine {
	int Animation::getUVLocation(std::string name) { 
		for(int i = 0; i < _animNames.size(); i++) {
			if(name == _animNames[i]) {
				return i;
			}
		} 
		fatalGenericError("Animation name '" + name + "' not found.");
	}
}