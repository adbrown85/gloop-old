#version 130

/* Uniforms */
uniform mat4 MVPMatrix = mat4(1.0);

/* Inputs */
in vec4 MCVertex;
in vec2 TexCoord0;

/* Outputs */
out vec2 Coord0;


/** Compute vertex attributes. */
void main() {
	
	gl_Position = MVPMatrix * MCVertex;
	Coord0 = TexCoord0;
	Coord0.y = 1.0 - Coord0.y;
}
