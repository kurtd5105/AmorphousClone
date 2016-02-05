#include "FontBatcher.h"
#include <iostream>

namespace GameEngine {
	FontBatcher::FontBatcher() {
	}


	FontBatcher::~FontBatcher() {
	}

	/*void FontBatcher::extendCharLimit(unsigned int length) {
		_vertices.resize(_vertices.size() + (6 * length));
	}*/

	unsigned int FontBatcher::addString() {
		_vertexGroups.emplace_back();
		return _vertexGroups.size() - 1;
	}

	void FontBatcher::remove(unsigned int index) {
		/*_renderBatch.numVertices -= amount * 6;
		unsigned int end = start + (amount * 6);
		std::vector<Vertex> vertices;
		vertices.resize(_vertices.size() - (6 * amount));
		unsigned int k = 0;
		std::cout << "Start: " << start << " End: " << end << std::endl;
		for(unsigned int i = 0; i < vertices.size(); i++) {
			if(i < start || i >= end) {
				vertices[k] = _vertices[i];
				k++;
			}
		}
		_vertices.clear();
		_vertices = vertices;
		std::cout << "Everything removed: " << _vertices.size() << std::endl;*/
		_vertexGroups[index] = std::vector<Vertex>();
	}

	void FontBatcher::updateBatch() {
		_vertices.clear();

		unsigned int size = 0, i = 0;
		for(auto& g : _vertexGroups) {
			size += g.size();
		}

		_vertices.resize(size);
		_renderBatch.numVertices = size;

		for(auto& g : _vertexGroups) {
			for(auto& v : g) {
				_vertices[i] = v;
				i++;
			}
		}
	}

	void FontBatcher::add(const glm::vec4& destRect, const glm::vec4& uvRect, float Depth, const Color color, unsigned int i) {
		//_renderBatch.numVertices += 6;
		//std::cout << _vertices.size() << ", ";
		Vertex vertex;
		//Triangle 1
		//Top right [0]
		vertex.setVertex(destRect.x + destRect.z, destRect.y + destRect.w, 255, 255, 255, 255, uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		vertex.color = color;
		_vertexGroups[i].push_back(vertex);

		//Top left [1]
		vertex.setVertex(destRect.x, destRect.y + destRect.w, 255, 255, 255, 255, uvRect.x, uvRect.y + uvRect.w);
		vertex.color = color;
		_vertexGroups[i].push_back(vertex);

		//Bottom left [2]
		vertex.setVertex(destRect.x, destRect.y, 255, 255, 255, 255, uvRect.x, uvRect.y);
		vertex.color = color;
		_vertexGroups[i].push_back(vertex);

		//Triangle 2
		//Bottom left [3] = [2]
		_vertexGroups[i].push_back(vertex);

		//Bottom right [4]
		vertex.setVertex(destRect.x + destRect.z, destRect.y, 255, 255, 255, 255, uvRect.x + uvRect.z, uvRect.y);
		vertex.color = color;
		_vertexGroups[i].push_back(vertex);

		//Top right [5] = [0]
		vertex.setVertex(destRect.x + destRect.z, destRect.y + destRect.w, 255, 255, 255, 255, uvRect.x + uvRect.z, uvRect.y + uvRect.w);
		vertex.color = color;
		_vertexGroups[i].push_back(vertex);
		//std::cout << _vertices.size() << std::endl;
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

	void FontBatcher::init(std::string path, int point, ResourceManager* manager) {
		_ResourceManager = manager;
		_font = _ResourceManager->getFont(path, point);

		_renderBatch.texture = _font.getFontID();

		//Set up the VAO and VBO
		createVertexArray();
	}

	void FontBatcher::cleanUp() {
		//Clean up all the batches before beginning a new batch
		_renderBatch.numVertices = 0;
		_renderBatch.offset = 0;
		_vertices.clear();
		_vertexGroups.clear();
	}

	void FontBatcher::renderBatch() {
		createRenderBatches();
		glBindVertexArray(_vaoID);
		glBindTexture(GL_TEXTURE_2D, _renderBatch.texture);
		glDrawArrays(GL_TRIANGLES, _renderBatch.offset, _renderBatch.numVertices);
		glBindVertexArray(0);
	}
}