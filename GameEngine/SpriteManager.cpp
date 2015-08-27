#include "SpriteManager.h"
#include <algorithm>
#include <iostream>

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

	Sprite* SpriteManager::addSprite(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path) {
		Sprite sprite;
		sprite.init(x, y, width, height, depth, UVmM, path, _ResourceManager);

		//Iterate to the insertion point for the new sprite
		unsigned int i = 0;
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
		if(i != _sprites.size() && _sprites.size() != 0) {
			std::advance(insertLocation, i);
			_sprites.insert(insertLocation, sprite);
			_spriteRefs.push_back(&_sprites[i]);
		} else {
			_sprites.push_back(sprite);
			_spriteRefs.push_back(&_sprites.back());
		}
		return _spriteRefs.back();
	}

	void SpriteManager::deleteSprite(Sprite* sprite) {
		//auto spriteRefLocation = std::find(_spriteRefs.begin(), _spriteRefs.end(), sprite);
		//auto spriteLocation = std::find(_sprites.begin(), _sprites.end(), *sprite);
		//_spriteRefs.erase(spriteRefLocation);
		//_sprites.erase(spriteLocation);
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