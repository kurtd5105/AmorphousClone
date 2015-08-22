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

		void init(sortType sort, ResourceManager* _ResourceManager);

		Sprite* addSprite(float x, float y, float width, float height, float depth, std::vector<float> UVmM, std::string path);

		//For resorting sprites later
		void sortSprites(sortType cmp);
		

		//Getters
		std::vector<Sprite>* getSprites() { return &_sprites; }
		
		void clearSprites() { _sprites.clear(); }
		
	private:
		ResourceManager* _ResourceManager;

		sortType _sortType;
		std::vector<Sprite> _sprites;
		std::vector<Sprite*> _spriteRefs;

		static bool cmpTexture(Sprite a, Sprite b);
		static bool cmpDepth(Sprite a, Sprite b);
	};
}
