#version 330

in vec4 color;

out vec4 outputF;

void main()
{
	outputF = vec4(0.0, 0.5, 0.25, 1.0);
	//outputF = color;
} 
