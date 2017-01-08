#implement vertex
#version 440
uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_ObjectSpace;
uniform float u_Time;
uniform float u_DeltaTime;
uniform sampler2D u_Texture;

attribute vec3 a_Position;
attribute vec2 a_TexCoords;
attribute vec3 a_Normal;
attribute vec4 a_Color;

varying vec2 v_TexCoords;
varying vec3 v_Normal;
varying vec4 v_Color;
varying vec3 v_WorldSpacePosition;

void main()
{
	gl_Position = u_MVP * vec4(a_Position,1.0);
	v_TexCoords = a_TexCoords;
	v_Normal = a_Normal;
	v_Color = a_Color;
	v_WorldSpacePosition = (u_ObjectSpace * vec4(a_Position,1.0)).xyz; 	
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

varying vec2 v_TexCoords;
varying vec3 v_Normal;
varying vec4 v_Color;
varying vec3 v_WorldSpacePosition;


void main()
{
	vec4 color = texture2D(u_Texture, v_TexCoords);

	gl_FragColor = color;
}

#end