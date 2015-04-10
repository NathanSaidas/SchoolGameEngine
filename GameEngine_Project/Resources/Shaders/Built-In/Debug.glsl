#implement vertex
#version 440

// -- Position Uniforms
uniform mat4 u_MVP;
// -- Texture
uniform sampler2D u_Texture;


// -- Basic Attributes.
in vec3 a_Position;
in vec2 a_TexCoords;

// -- Attributes to Fragment Shader
out vec2 v_TexCoords;

void main()
{
	gl_Position = u_MVP * vec4(a_Position,1.0);
	v_TexCoords = a_TexCoords;
}
#end
#implement fragment
#version 440

// -- Position Uniforms
uniform mat4 u_MVP;
// -- Texture
uniform sampler2D u_Texture;


// -- Attributes from Vertex Shader
in vec2 v_TexCoords;
// -- Frag Color. This must be bound to position 0. Using glBindFragDataLocation();
out vec4 v_FragColor;

//#define INVERT

void main()
{
	vec4 color = texture(u_Texture, v_TexCoords);
	#ifdef INVERT
	v_FragColor = vec4(1.0,1.0,1.0,1.0) - color;
	v_FragColor.w = 1.0;
	#else
	v_FragColor = color;
	#endif
}

#end