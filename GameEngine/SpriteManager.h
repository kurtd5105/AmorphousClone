#pragma once
#include <vector>
#include <list>

namespace GameEngine {
	class ResourceManager;
	class Sprite;

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
		//std::vector<Sprite>* getSprites() { return &_sprites; }
		std::list<Sprite*>* getSprites() { return &_spriteList; }
		ResourceManager* getResourceManager() const { return _ResourceManager; }
		
		void clearSprites();
		
	private:
		ResourceManager* _ResourceManager;

		sortType _sortType;
		
		std::list<Sprite*> _spriteList;

		static bool cmpTexture(Sprite* a, Sprite* b);
		static bool cmpDepth(Sprite* a, Sprite* b);
	};
}
