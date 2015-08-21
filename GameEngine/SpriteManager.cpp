#include "SpriteManager.h"
#include <algorithm>

namespace GameEngine {
	SpriteManager::SpriteManager() : _sortType(sortType::TEXTURE){
	}


	SpriteManager::~SpriteManager() {
	}

	void SpriteManager::init(sortType sort, ResourceManager* manager) {
		_ResourceManager = manager;
		_sortType = sort;
	}

	bool SpriteManager::cmpDepth(Sprite a, Sprite b) {
		return (a.getDepth() < b.getDepth());
	}

	bool SpriteManager::cmpTexture(Sprite a, Sprite b) {
		return (a.getTextureID() > b.getTextureID());
	}

	void SpriteManager::addSprite(float x, float y, float width, float height, float depth, std::string path) {
		Sprite sprite;
		sprite.init(x, y, width, height, depth, path, _ResourceManager);

		//If there aren't any sprites then simply push the new sprite
		if(_sprites.size() == 0) {
			_sprites.push_back(sprite);
		//Otherwise find a new insert location
		} else {
			int i = 0;
			auto insertLocation = _sprites.begin();
			switch(_sortType) {
			case sortType::DEPTH:
				while(i < _sprites.size()) {
					cmpDepth(sprite, _sprites[i++]);
				}
				break;
			case sortType::TEXTURE:
				while(i < _sprites.size()) {
					cmpTexture(sprite, _sprites[i++]);
				}
				break;
			}
			//Advance the iterator to the insert location or push to the back if it is at the end 
			if(i != _sprites.size()) {
				std::advance(insertLocation, i);
				_sprites.insert(insertLocation, sprite);
			} else {
				_sprites.push_back(sprite);
			}
		}
	}

	void SpriteManager::sortSprites(sortType cmp) {
		switch(cmp) {
		case sortType::TEXTURE:
			std::stable_sort(_sprites.begin(), _sprites.end(), cmpTexture);
			break;
		case sortType::DEPTH:
			std::stable_sort(_sprites.begin(), _sprites.end(), cmpDepth);
			break;
		}
	}
}