#include "Circle.h"

Circle::Circle()
{
}


Circle::~Circle()
{
}

void Circle::init(b2World* world, const glm::vec2& position, const float& radius) {
	m_radius = radius;
	
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(position.x, position.y);
	m_body = world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_p.Set(position.x, position.y);
	circle.m_radius = radius;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1;
	m_fixture = m_body->CreateFixture(&fixtureDef);
}
