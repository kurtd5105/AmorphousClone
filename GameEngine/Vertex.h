#pragma once
#include <GL/glew.h>

namespace GameEngine {
	struct Position {
		float x, y;
	};

	struct Color {
		GLubyte r, g, b, a;
	};

	struct UV {
		float u, v;
	};

	class Vertex {
		Position position;
		Color color;
		UV uv;

		Vertex(float x, float y, GLubyte r, GLubyte g, GLubyte b, GLubyte a, float u, float v) {
			setPosition(x, y);
			setColor(r, g, b, a);
			setUV(u, v);
		}

		void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		void setColor(GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
			color.r = r;
			color.g = g;
			color.b = b;
			color.a = a;
		}

		void setUV(float u, float v) {
			uv.u = u;
			uv.v = v;
		}
	};
}
