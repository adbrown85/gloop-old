#version 130

/* Uniforms */
uniform sampler2D Texture;

/* Inputs */
in vec2 Coord0;

/* Outputs */
out vec4 FragColor;


/** Compute fragment color. */
void main() {
	
	FragColor = texture(Texture, Coord0);
}
