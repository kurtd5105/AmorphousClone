#pragma once
#include "RenderBatch.h"

#include <GL/glew.h>

#include <list>
#include <vector>

namespace GameEngine {
	class Sprite;

	class SpriteBatcher {
	public:
		SpriteBatcher();
		~SpriteBatcher();

		void init();
		void cleanUp();
		void setupBatches(std::list<Sprite*>* spritesLocation);
		void renderBatch();

		

	private:
		GLuint _vboID;
		GLuint _vaoID;

		GLushort _indices;

		//Pointers are for sorting the actual glyphs
		std::vector<Sprite*> _spritePointers;
		std::vector<RenderBatch> _renderBatches;

		void setNewBatch(std::list<Sprite*>* spritesLocation);
		void createRenderBatches();
		void createVertexArray();
	};
}
