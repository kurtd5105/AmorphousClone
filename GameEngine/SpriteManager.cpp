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
		return (a->getTextureID() > b->getTextureID());
	}

	void SpriteManager::addSprite(Sprite* sprite) {
		if(_spriteRefs.size() == 0) {
			_spriteRefs.push_back(sprite);
		} else {
			int i = 0;
			auto insertLocation = _spriteRefs.begin();
			switch(_lastSort) {
			case sortType::DEPTH:
				while(cmpDepth(sprite, _spriteRefs[i++])) {}
				break;
			case sortType::TEXTURE:
				while(cmpTexture(sprite, _spriteRefs[i++])) {}
				break;
			}
			//Advance the iterator to the insert location
			std::advance(insertLocation, i);
			_spriteRefs.insert(insertLocation, sprite);
		}
	}

	void SpriteManager::sortSprites(sortType cmp) {
		_lastSort = cmp;
		switch(cmp) {
		case sortType::TEXTURE:
			//std::stable_sort(_spriteRefs.begin(), _spriteRefs.end(), cmpTexture);
			break;
		case sortType::DEPTH:
			//std::stable_sort(_spriteRefs.begin(), _spriteRefs.end(), cmpDepth);
			break;
		}
	}
}