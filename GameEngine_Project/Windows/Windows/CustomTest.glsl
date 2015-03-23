#implement vertex
#version 440
uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_ObjectSpace;
uniform float u_Time;
uniform float u_DeltaTime;
uniform sampler2D u_Texture;
uniform sampler2D u_ShadowMap;
uniform mat4 u_DirectionalLight;

attribute vec3 a_Position;
attribute vec2 a_TexCoords;
attribute vec3 a_Normal;
attribute vec4 a_Color;

varying vec2 v_TexCoords;
varying vec3 v_Normal;
varying vec4 v_Color;
varying vec3 v_WorldSpacePosition;
varying vec4 v_ShadowPosition;

void main()
{
	gl_Position = u_MVP * vec4(a_Position,1.0);
	v_TexCoords = a_TexCoords;
	v_Normal = a_Normal;
	v_Color = a_Color;
	v_WorldSpacePosition = (u_ObjectSpace * vec4(a_Position,1.0)).xyz; 	
	v_ShadowPosition = u_DirectionalLight * vec4(a_Position, 1.0);
}
#end
#implement fragment
#version 440

uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_ObjectSpace;
uniform float u_Time;
uniform float u_DeltaTime;
uniform sampler2D u_Texture;
uniform sampler2D u_ShadowMap;
uniform mat4 u_DirectionalLight;

varying vec2 v_TexCoords;
varying vec3 v_Normal;
varying vec4 v_Color;
varying vec3 v_WorldSpacePosition;
varying vec4 v_ShadowPosition;


void main()
{
	vec4 fragColor = texture2D(u_Texture, v_TexCoords);

	float shadowPercent = 1.0;

	vec2 shadowTexCoord = (v_ShadowPosition.xy / v_ShadowPosition.w) * 0.5 + 0.5;
	vec4 shadowColor = texture2D(u_ShadowMap, shadowTexCoord);

	float bias = 0.0002;
	float projectionDepth = ((v_ShadowPosition.z)/v_ShadowPosition.w) * 0.5 + 0.5;

	if(shadowColor.z < projectionDepth - bias)
	{
		shadowPercent = 0.5;
	}

	gl_FragColor = fragColor * shadowPercent;
}

#end