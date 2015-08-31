#include "SpriteBatcher.h"

namespace GameEngine {
	SpriteBatcher::SpriteBatcher() {
	}


	SpriteBatcher::~SpriteBatcher() {
	}

	void SpriteBatcher::createRenderBatches() {
		//Create a vector of vertices and resize it to be the total size of all the vertices it will need to contain
		std::vector<Vertex> vertices;

		vertices.resize(_spritePointers.size() * 6);

		//If there aren't any glyphs there is nothing else that needs to be done
		if(_spritePointers.empty()) {
			return;
		}

		//Take all the vertices from the glyphs and copy them over to vertices
		int n = 0, offset = 0;
		GLuint currentTexture = 0, textureID = 0;

		for(auto& sprite : _spritePointers) {
			//If the texture is unique then add a new grouping of vertices
			textureID = sprite->getTextureID();
			if(textureID != currentTexture) {
				_renderBatches.emplace_back(offset, 6, textureID);
				currentTexture = textureID;
				//Otherwise just increase the amount of vertices for that one batch
			} else {
				_renderBatches.back().numVertices += 6;
			}
			//Add in all the vertices
			for(int i = 0; i < 6; i++) {
				vertices[n++] = sprite->getVertexAt(i);
			}
			offset += 6;
		}
		//Bind the vbo
		glBindBuffer(GL_ARRAY_BUFFER, _vboID);
		//Orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//Write to the buffer
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		//Unbind the vbo
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatcher::createVertexArray() {
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

	void SpriteBatcher::setNewBatch(std::vector<Sprite>* spritesLocation) {
		//Clear the current vector of sprite pointers and create it again with the new sprites
		_spritePointers.clear();

		_spritePointers.resize(spritesLocation->size());
		for(unsigned int i = 0; i < spritesLocation->size(); i++) {
			_spritePointers[i] = &spritesLocation->at(i);
		}
	}

	void SpriteBatcher::init() {
		//Set up the VAO and VBO
		createVertexArray();
	}

	void SpriteBatcher::cleanUp() {
		//Clean up all the batches before beginning a new batch
		_renderBatches.clear();
	}

	void SpriteBatcher::setupBatches() {
		createRenderBatches();
	}

	void SpriteBatcher::renderBatch() {
		glBindVertexArray(_vaoID);
		for(auto& batch : _renderBatches) {
			glBindTexture(GL_TEXTURE_2D, batch.texture);
			glDrawArrays(GL_TRIANGLES, batch.offset, batch.numVertices);
		}
		glBindVertexArray(0);
	}
}