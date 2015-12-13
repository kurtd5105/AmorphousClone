#pragma once
#include <list>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SDL/SDL.h>

#include "Font.h"
#include "Vertex.h"

namespace GameEngine {
	class RenderBatch {
	public:
		RenderBatch(GLuint Offset, GLuint NumVertices, GLuint Texture) : offset(Offset), numVertices(NumVertices), texture(Texture) {}
		GLuint offset;
		GLuint numVertices;
		GLuint texture;
	};

	class FontBatcher {
	public:
		FontBatcher();
		~FontBatcher();

		void init(std::string path, int point);
		void cleanUp();
		unsigned int add(const glm::vec4& destRect, const glm::vec4& UVmM, float Depth, const Color color);
		void renderBatch();

		Font* getFont() { return &_font; }
	private:
		GLuint _vboID;
		GLuint _vaoID;

		std::vector<Vertex> _vertices;

		Font _font;
		RenderBatch _renderBatch = RenderBatch(0, 0, 0);

		void createRenderBatches();
		void createVertexArray();
	};
}
