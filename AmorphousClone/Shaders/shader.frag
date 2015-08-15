#version 130

in vec2 fragmentPosition;
in vec2 fragmentUV;
in vec4 fragmentColor;
out vec4 color;

uniform sampler2D playerTexture;

void main() {
	vec4 textureColor = texture(playerTexture, fragmentUV);
	color = textureColor;
}