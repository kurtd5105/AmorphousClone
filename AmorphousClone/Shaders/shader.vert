#version 130
//change to layout(location = 2)
in vec2 vertexPosition;
in vec2 vertexUV;
in vec4 vertexColor;

out vec4 fragmentColor;
out vec2 fragmentPosition;
out vec2 fragmentUV;

uniform mat4 P;

void main() {
	gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
	gl_Position.z = 0.0;
	gl_Position.w = 1.0;
	fragmentColor = vertexColor;
	fragmentPosition = (P * vec4(vertexPosition, 0.0, 1.0)).xy;//vertexPosition;
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);
}