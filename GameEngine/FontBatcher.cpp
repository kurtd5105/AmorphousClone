#include "FontBatcher.h"

namespace GameEngine {
	FontBatcher::FontBatcher() {
	}


	FontBatcher::~FontBatcher() {
	}

	unsigned int FontBatcher::add(const glm::vec4& destRect, const glm::vec4& uvRect, float Depth, const Color color) {
		unsigned int size = _vertices.size();
		_vertices.resize(size + 6);
		_renderBatch.numVertices += 6;

		Vertex vertex;
		//Triangle 1
		//Top right [0]
		vertex.setVertex(destRect.x + destRect.z, destRect.y + destRect.w, 255, 255, 255, 255, uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		vertex.color = color;
		_vertices.push_back(vertex);

		//Top left [1]
		vertex.setVertex(destRect.x, destRect.y + destRect.w, 255, 255, 255, 255, uvRect.x, uvRect.y + uvRect.w);
		vertex.color = color;
		_vertices.push_back(vertex);

		//Bottom left [2]
		vertex.setVertex(destRect.x, destRect.y, 255, 255, 255, 255, uvRect.x, uvRect.y);
		vertex.color = color;
		_vertices.push_back(vertex);

		//Triangle 2
		//Bottom left [3] = [2]
		_vertices.push_back(vertex);

		//Bottom right [4]
		vertex.setVertex(destRect.x + destRect.z, destRect.y, 255, 255, 255, 255, uvRect.x + uvRect.z, uvRect.y);
		vertex.color = color;
		_vertices.push_back(vertex);

		//Top right [5] = [0]
		vertex.setVertex(destRect.x + destRect.z, destRect.y + destRect.w, 255, 255, 255, 255, uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		vertex.color = color;
		_vertices.push_back(vertex);

		return size;
	}

	void FontBatcher::createRenderBatches() {
		//Bind the vbo
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//Write to the buffer
		glBufferSubData(GL_ARRAY_BUFFER, 0, _vertices.size() * sizeof(Vertex), _vertices.data());
		//Unbind the vbo
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void FontBatcher::createVertexArray() {
		//If the vao or vbos don't exist, create them and then also bind them
		if(_vaoID == 0) {
			glGenVertexArrays(1, &_vaoID);
		}
		glBindVertexArray(_vaoID);

		if(_vboID == 0) {
			glGenBuffers(1, &_vboID);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);

		//Set up the VBO
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//Information about the data and how to read it
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void FontBatcher::init(std::string path, int point) {
		_font.init(path, point);

		_renderBatch.texture = _font.getFontID();

		//Set up the VAO and VBO
		createVertexArray();
	}

	void FontBatcher::cleanUp() {
		//Clean up all the batches before beginning a new batch
		_renderBatch.numVertices = 0;
		_renderBatch.offset = 0;
		_vertices.clear();
	}

	void FontBatcher::renderBatch() {
		glBindVertexArray(_vaoID);
		glBindTexture(GL_TEXTURE_2D, _renderBatch.texture);
		glDrawArrays(GL_TRIANGLES, _renderBatch.offset, _renderBatch.numVertices);
		glBindVertexArray(0);
	}
}