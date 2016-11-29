#define _USE_MATH_DEFINES
#include "Hitbox.h"
#include "Sprite.h"

namespace GameEngine {
	Hitbox::Hitbox() : _type(HitboxType::RECT){}

	Hitbox::~Hitbox() {}

	void Hitbox::init(float x, float y, float width, float height, float radius, HitboxType t) {
		_info.resize(5);
		_info[0] = x;
		_info[1] = y;
		_info[2] = x + width;
		_info[3] = y + height;
		_info[4] = radius;

		if(t == RECT_POINT) {
			_vertices.push_back(std::pair<float, float>{0.0f, 0.0f});
			_vertices.push_back(std::pair<float, float>{0.0f, 0.0f});
			_vertices.push_back(std::pair<float, float>{0.0f, 0.0f});
			_vertices.push_back(std::pair<float, float>{0.0f, 0.0f});
			_l = _r = _t = _b = 0;
		}
	}

	void Hitbox::translate(float x, float y) {
		_info[0] += x;
		_info[1] += y;
		_info[2] += x;
		_info[3] += y;
	}

	void Hitbox::lockOn(Sprite* target) {
		if(_type == RECT_POINT) {
			Vertex v = target->getVertexAt(0);
			_vertices[0].first = v.position.x;
			_vertices[0].second = v.position.y;

			v = target->getVertexAt(1);
			_vertices[1].first = v.position.x;
			_vertices[1].second = v.position.y;

			v = target->getVertexAt(2);
			_vertices[2].first = v.position.x;
			_vertices[2].second = v.position.y;

			v = target->getVertexAt(3);
			_vertices[3].first = v.position.x;
			_vertices[3].second = v.position.y;

			float minx, maxx, miny, maxy;
			minx = maxx = _vertices[0].first;
			miny = maxy = _vertices[0].second;

			unsigned int i = 0;
			for(auto& p : _vertices) {
				if(p.first > maxx) {
					_r = i;
				}
				if(p.first < minx) {
					_l = i;
				}
				if(p.second > maxy) {
					_t = i;
				}
				if(p.second < miny) {
					_b = i;
				}

				i++;
			}
		}
	}
}
