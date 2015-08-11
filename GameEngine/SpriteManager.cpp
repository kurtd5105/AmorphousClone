#include "SpriteManager.h"
#include <algorithm>

namespace GameEngine {
	SpriteManager::SpriteManager() {
	}


	SpriteManager::~SpriteManager() {
	}

	bool SpriteManager::cmpDepth(Sprite* a, Sprite* b) {
		return (a->getDepth() < b->getDepth());
	}

	bool SpriteManager::cmpTexture(Sprite* a, Sprite* b) {
		return (a->getTextureID() < b->getTextureID());
	}

	void SpriteManager::sortSprites(sortType cmp) {
		switch(cmp) {
		case sortType::TEXTURE:
			std::stable_sort(_spriteRefs.begin(), _spriteRefs.end(), cmpTexture);
			break;
		case sortType::DEPTH:
			std::stable_sort(_spriteRefs.begin(), _spriteRefs.end(), cmpDepth);
			break;
		}
	}
}