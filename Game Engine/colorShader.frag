#version 430	

in vec4 ex_Color;	
in vec2 ex_TexCoords;

layout(location=3) uniform sampler2D uTexture;

uniform vec2 uTextureOffset;


out vec4 out_Color;		
 
void main() {			
		out_Color = ex_Color;
}