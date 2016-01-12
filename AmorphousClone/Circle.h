#pragma once

#include <Box2D/Box2D.h>
#include <glm/glm.hpp>
class Circle
{
public:
	Circle();
	~Circle();

	void init(b2World* world, const glm::vec2& position, const float& radius);

	b2Body* getBody() const { return m_body; }
	b2Fixture* getFixture() const { return m_fixture; }
	const float& getFloat() const { return m_radius; }

private:
	b2Body* m_body = nullptr;
	b2Fixture* m_fixture = nullptr;
	float m_radius;

};

