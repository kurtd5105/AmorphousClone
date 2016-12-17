#pragma once
#include "Animation.h"

#include <vector>

namespace GameEngine {
	class ResourceManager;
	class Sprite;

	class SpriteSheet {
	public:
		SpriteSheet();
		~SpriteSheet();

		//Sprite manager loads the UVmM data and stores like sprites
		void init(std::string& path, Sprite* sprite, ResourceManager* manager);
		void nextStep();
		void setAnim(std::string& animName);

	private:
		int _set, _step;
		Sprite* _sprite;
		ResourceManager* _ResourceManager;
		Animation _animation;

		std::string _currAnim;
	};
}
