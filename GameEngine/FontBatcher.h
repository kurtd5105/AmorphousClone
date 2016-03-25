#pragma once
#include <list>
#include <glm/glm.hpp>
#include <GL/glew.h>

#include "Font.h"
#include "RenderBatch.h"
#include "ResourceManager.h"
#include "Vertex.h"

namespace GameEngine {
	class FontBatcher {
	public:
		FontBatcher();
		~FontBatcher();

		void init(std::string path, int point, ResourceManager* manager);//add resource manager control of fonts
		void cleanUp();
		void remove(unsigned int index);
		void add(const glm::vec4& destRect, const glm::vec4& UVmM, float Depth, const Color color, unsigned int i);
		void updateBatch();//turn the vertex groups into vertices
		void renderBatch();
		unsigned int addString();//create a new vertex group

		Font* getFont() { return &_font; }
	private:
		GLuint _vboID;
		GLuint _vaoID;

		std::vector<Vertex> _vertices;
		std::vector<std::vector<Vertex>> _vertexGroups;

		Font _font;
		RenderBatch _renderBatch = RenderBatch(0, 0, 0);
		ResourceManager* _ResourceManager;

		void createRenderBatches();
		void createVertexArray();
	};
}
