#version 430

layout(location=0) in vec3 in_Position;				
layout(location=1) in vec4 in_Color;			
layout(location=2) in vec2 in_TexCoords;	

out vec4 ex_Color;				
out vec2 ex_TexCoords;	

uniform mat4 transform;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;


void main() {	
	//gl_Position = transform * vec4(in_Position, 1.0f);	
	gl_Position = projMat * viewMat * modelMat * vec4(in_Position, 1.0f);			
	ex_Color = in_Color;	
	ex_TexCoords =  in_TexCoords;
}