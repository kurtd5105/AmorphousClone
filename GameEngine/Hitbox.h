#pragma once
#include <vector>
#include "GameEngine/Sprite.h"

namespace GameEngine {

	enum HitboxType {
		CIRC, RECT, RECT_POINT
	};

	class Hitbox {
	public:
		Hitbox();
		~Hitbox();

		void init(float x, float y, float width, float height, float radius, HitboxType t); //if more shapes introduced otherwise r = 0 means rect

		void translate(float x, float y);
		void lockOn(Sprite* target);
		void setPos(float x, float y);

		HitboxType getType() const { return _type; }
		std::vector<float>* getInfo() { return &_info; }

	private:
		HitboxType _type;
		//x		y		width		height		radius
		std::vector<float> _info;
		std::vector<std::pair<float, float>> _vertices;
		int _l, _r, _t, _b;
	};
}
