#pragma once
#include "Sprite.h"
#include <vector>
namespace GameEngine {
	enum sortType {
		TEXTURE, DEPTH
	};
	class SpriteManager {
	public:
		SpriteManager();
		~SpriteManager();

		void sortSprites(sortType cmp = sortType::TEXTURE);
		void addSprite(Sprite* sprite);

		//Getters
		std::vector<Sprite*>* getSprites() { return &_spriteRefs; }
		
	private:
		sortType _lastSort = sortType::TEXTURE;
		std::vector<Sprite*> _spriteRefs;

		static bool cmpTexture(Sprite* a, Sprite* b);
		static bool cmpDepth(Sprite* a, Sprite* b);
	};
}
