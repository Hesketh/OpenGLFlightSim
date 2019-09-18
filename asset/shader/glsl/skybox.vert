#version 430

layout (location = 0) uniform mat4 modelview;	//modelview matrix
layout (location = 1) uniform mat4 projection;	//projection matrix

layout (location = 0) in vec4 position;	//vertex attribute: position
layout (location = 2) in vec2 inUV;		//vertex attribute: texcoords

out vec2 outUV;			//output: texcoords

void main()
{	
	gl_Position = projection*modelview*position;
	
	outUV = inUV;
}