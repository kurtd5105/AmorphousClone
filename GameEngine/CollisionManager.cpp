#include "CollisionManager.h"
#include <vector>
#include <iostream>
namespace GameEngine {
	bool Collision::checkCollide(Hitbox a, Hitbox b) {
		if(a.getType() == b.getType()) {
			switch(a.getType()) {
			default:
				return false;
			}
		}
		//switch(a type){ for each case: switch(b type) }
		return false;
	}

	bool Collision::checkClick(Hitbox a, float x, float y) {
		std::vector<float> aInfo = *(a.getInfo());
		switch(a.getType()) {
		case HitboxType::CIRC:
			return false;
		case HitboxType::RECT:
			if(aInfo[0] <= x && aInfo[2] >= x) {
				if(aInfo[1] <= abs(y - 600) && aInfo[3] >= (abs(y - 600))) {
					//std::cout << "Button click info: " << aInfo[0] << ", " << aInfo[1] << ", " << aInfo[2] << ", " << aInfo[3] << "; " << x << ", " << abs(y - 600) << std::endl;
					return true;
				}
			}
			return false;
		default:
			return false;
		}
	}
}