#implement vertex
#version 440
uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_ObjectSpace;
uniform float u_Time;
uniform float u_DeltaTime;

attribute vec3 a_Position;
attribute vec2 a_TexCoords;
attribute vec3 a_Normal;
attribute vec4 a_Color;

varying vec2 v_TexCoords;
varying vec3 v_Normal;
varying vec4 v_Color;
varying vec3 v_ObjectSpacePosition;

void main()
{
	gl_Position = u_MVP * vec4(a_Position,1.0);
	//gl_Position = vec4(a_Position,1.0);
	v_TexCoords = a_TexCoords;
	v_Normal = a_Normal;
	v_Color = a_Color;
	v_ObjectSpacePosition = (u_ObjectSpace * vec4(a_Position,1.0)).xyz; 	
}
#end
#implement fragment
#version 440
uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_ObjectSpace;
uniform float u_Time;
uniform float u_DeltaTime;

varying vec2 v_TexCoords;
varying vec3 v_Normal;
varying vec4 v_Color;
varying vec3 v_ObjectSpacePosition;


void main()
{
	gl_FragColor = v_Color;
}

#end