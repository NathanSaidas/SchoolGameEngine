#implement vertex
#version 440

// -- Position Uniforms
uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_ShadowBias;
// -- Time Uniforms
uniform float u_Time;
uniform float u_DeltaTime;
// -- Textures
uniform sampler2D u_ShadowMap;



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
//Coordinate of the shadow on the shadow map.
out vec4 v_ShadowCoord;

void main()
{
	gl_Position = u_MVP * vec4(a_Position,1.0);
	v_TexCoords = a_TexCoords;
	v_Normal = a_Normal;
	v_Color = a_Color;
	v_ObjectSpacePosition = ((u_View * u_Projection) * vec4(a_Position,1.0)).xyz; 	 //This is my world space.
	v_ShadowCoord = u_ShadowBias * vec4(a_Position, 1.0);
}
#end
#implement fragment
#version 440

// -- Position Uniforms
uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
uniform mat4 u_ShadowBias;
// -- Time Uniforms
uniform float u_Time;
uniform float u_DeltaTime;
// -- Textures
uniform sampler2D u_ShadowMap;





// -- Attributes to Fragment Shader
in vec2 v_TexCoords;
in vec3 v_Normal;
in vec4 v_Color;
in vec3 v_ObjectSpacePosition;
//Coordinate of the shadow on the shadow map.
in vec4 v_ShadowCoord;

// -- Frag Color. This must be bound to position 0. Using glBindFragDataLocation();
out vec4 v_FragColor;


float Deg2Rad(float theta)
{
	return theta * 3.14 / 180.0;
}

float CalcShadowVisibilty()
{
	vec2 texCoords = (v_ShadowCoord.xy / v_ShadowCoord.w) * 0.5 + 0.5;
	vec4 shadow = texture(u_ShadowMap, texCoords);

	float bias = 0.0002;
	float projectionDepth = ((v_ShadowCoord.z)/v_ShadowCoord.w) * 0.5 + 0.5;

    float visibility = 1.0;
	if(shadow.z < projectionDepth - bias)
	{
		visibility = 0.5;
	}


	return visibility;
}

void main()
{
	float visibility = CalcShadowVisibilty();
	v_FragColor = v_Color * visibility;
}

#end