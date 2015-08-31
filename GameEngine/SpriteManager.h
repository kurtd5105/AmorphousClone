#pragma once
#include "Sprite.h"
#include <vector>
#include <list>
namespace GameEngine {
	enum sortType {
		TEXTURE, DEPTH
	};
	class SpriteManager {
	public:
		SpriteManager();
		~SpriteManager();

		void init(sortType sort, ResourceManager* _ResourceManager);

		Sprite* addSprite(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path);
		void deleteSprite(Sprite* sprite);

		//For resorting sprites later
		void sortSprites(sortType cmp);
		

		//Getters
		std::vector<Sprite>* getSprites() { return &_sprites; }
		
		void clearSprites() { _sprites.clear(); _spriteRefs.clear(); }
		
	private:
		ResourceManager* _ResourceManager;

		sortType _sortType;
		std::vector<Sprite> _sprites;
		std::vector<Sprite*> _spriteRefs;

		//To be replaced in the future
		std::list<Sprite> _spriteList;

		static bool cmpTexture(Sprite a, Sprite b);
		static bool cmpDepth(Sprite a, Sprite b);
	};
}
