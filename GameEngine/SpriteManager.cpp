#include "SpriteManager.h"
#include <algorithm>
#include <iostream>

namespace GameEngine {
	SpriteManager::SpriteManager() : _ResourceManager(nullptr), _sortType(sortType::TEXTURE){}

	SpriteManager::~SpriteManager() {}

	void SpriteManager::init(sortType sort, ResourceManager* manager) {
		_ResourceManager = manager;
		_sortType = sort;
	}

	bool SpriteManager::cmpDepth(Sprite* a, Sprite* b) {
		//Sort so sprites with higher depth are behind other sprites
		return (a->getDepth() > b->getDepth());
	}

	bool SpriteManager::cmpTexture(Sprite* a, Sprite* b) {
		return (a->getTextureID() > b->getTextureID());
	}

	Sprite* SpriteManager::addSprite(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path) {
		Sprite* sprite = new Sprite();
		sprite->init(x, y, width, height, depth, UVmM, path, _ResourceManager);

		auto insertLocation = _spriteList.begin();

		if(_spriteList.size() == 0) {
			_spriteList.push_back(sprite);
		} else {
			//Iterate to the insertion point for the new sprite
			switch(_sortType) {
			case sortType::DEPTH:
				while(insertLocation != _spriteList.end() && cmpDepth(sprite, *insertLocation)) {
					insertLocation = std::next(insertLocation);
				}
				break;
			case sortType::TEXTURE:
				while(insertLocation != _spriteList.end() && cmpTexture(sprite, *insertLocation)) {
					insertLocation = std::next(insertLocation);
				}
				break;
			}
			if(insertLocation == _spriteList.end()) {
				_spriteList.push_back(sprite);
			} else {
				_spriteList.insert(insertLocation, sprite);
			}
		}
		//Sort the sprites again based on their depth
		sortSprites(sortType::DEPTH);
		return sprite;
	}

	void SpriteManager::deleteSprite(Sprite* sprite) {
		//Remove the reference from the linked list and then delete the sprite
		auto spriteLocation = std::find(_spriteList.begin(), _spriteList.end(), sprite);
		_spriteList.erase(spriteLocation);
		delete sprite;
	}

	void SpriteManager::clearSprites() {
		for(auto it = _spriteList.begin(); it != _spriteList.end(); ++it) {
			delete *it;
		}
		_spriteList.clear();
	}

	void SpriteManager::sortSprites(sortType cmp) {
		switch(cmp) {
		case sortType::TEXTURE:
			std::stable_sort(_spriteList.begin(), _spriteList.end(), cmpTexture);
			break;
		case sortType::DEPTH:
			std::stable_sort(_spriteList.begin(), _spriteList.end(), cmpDepth);
			break;
		}
	}
}