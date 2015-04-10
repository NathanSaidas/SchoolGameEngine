#implement vertex
#version 440

// -- Position Uniforms
uniform mat4 u_MVP;


// -- Basic Attributes.
in vec3 a_Position;

void main()
{
	gl_Position = u_MVP * vec4(a_Position,1.0);	
}
#end
#implement fragment
#version 440

// -- Position Uniforms
uniform mat4 u_MVP;

// -- Frag Color. This must be bound to position 0. Using glBindFragDataLocation();
out vec4 v_FragColor;


void main()
{
	v_FragColor = vec4(1.0,1.0,1.0,1.0);
}

#end