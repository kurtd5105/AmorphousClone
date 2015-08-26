#pragma once
#include <SDL/SDL.h>
#include <GL/glew.h>
#include "Sprite.h"
#include "Vertex.h"
#include <vector>

namespace GameEngine {
	class RenderBatch {
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) {}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class SpriteBatcher {
	public:
		SpriteBatcher();
		~SpriteBatcher();

		void init();
		void cleanUp();
		void setupBatches();
		void renderBatch();

		void setNewBatch(std::vector<Sprite>* spritesLocation);

	private:
		GLuint _vboID;
		GLuint _vaoID;

		GLushort _indices;

		//Pointers are for sorting the actual glyphs
		std::vector<Sprite*> _spritePointers;
		std::vector<RenderBatch> _renderBatches;

		void createRenderBatches();
		void createVertexArray();
	};
}
