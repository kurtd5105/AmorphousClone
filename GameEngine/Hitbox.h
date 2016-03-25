#pragma once
#include <vector>

namespace GameEngine {
	enum HitboxType {
		CIRC, RECT
	};

	class Hitbox {
	public:
		Hitbox();
		~Hitbox();

		void init(float x, float y, float width, float height, float radius);//, HitboxType type); //if more shapes introduced otherwise r = 0 means rect

		void translate(float x, float y);

		HitboxType getType() const { return _type; }
		std::vector<float>* getInfo() { return &_info; }

	private:
		HitboxType _type;
		//x		y		width		height		radius
		std::vector<float> _info;
	};
}
