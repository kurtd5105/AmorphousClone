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
				while(i < _spriteRefs.size()) {
					cmpDepth(sprite, _spriteRefs[i++]);
				}
				break;
			case sortType::TEXTURE:
				while(i < _spriteRefs.size()) {
					cmpTexture(sprite, _spriteRefs[i++]);
				}
				break;
			}
			//Advance the iterator to the insert location
			if(i != _spriteRefs.size()) {
				std::advance(insertLocation, i);
				_spriteRefs.insert(insertLocation, sprite);
			} else {
				_spriteRefs.push_back(sprite);
			}
		}
	}

	void SpriteManager::sortSprites(sortType cmp) {
		_lastSort = cmp;
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