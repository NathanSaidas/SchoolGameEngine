#implement vertex
#version 440

// -- Position Uniforms
uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
// -- Time Uniforms
uniform float u_Time;
uniform float u_DeltaTime;

// -- Texture
uniform sampler2D u_Texture;


// -- Basic Attributes.
in vec3 a_Position;
in vec2 a_TexCoords;
in vec3 a_Normal;
in vec4 a_Color;

// -- Attributes to Fragment Shader
out vec2 v_TexCoords;
out vec3 v_Normal;
out vec4 v_Color;
out vec3 v_ObjectSpacePosition;

void main()
{

	gl_Position = u_MVP * vec4(a_Position,1.0);
	v_TexCoords = a_TexCoords;
	v_Normal = a_Normal;
	v_Color = a_Color;
	v_ObjectSpacePosition = ((u_View * u_Projection) * vec4(a_Position,1.0)).xyz; 	
}
#end
#implement fragment
#version 440

// -- Position Uniforms
uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

// -- Time Uniforms
uniform float u_Time;
uniform float u_DeltaTime;

// -- Texture
uniform sampler2D u_Texture;


// -- Attributes from Vertex Shader
in vec2 v_TexCoords;
in vec3 v_Normal;
in vec4 v_Color;
in vec3 v_ObjectSpacePosition;

// -- Frag Color. This must be bound to position 0. Using glBindFragDataLocation();
out vec4 v_FragColor;


void main()
{
	vec4 color = texture(u_Texture, v_TexCoords);
	v_FragColor = v_Color * color;
}

#end