#pragma once
#include "EnemySuper.h"

class Goople : public EnemySuper {
public:
	Goople();
	~Goople();

	void think();
	void onCollide();

private:
	int _hp;
	glm::vec2 _target;

	void logicInit(int side);
};

