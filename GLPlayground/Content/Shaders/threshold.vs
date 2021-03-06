#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 uv;

layout (binding = 0) uniform Matrices
{
	mat4 Projection;
	mat4 View;
	mat4 Model;
};

uniform float threshold;


out vec4 fragmentColor;
out vec2 uvCoords;
out float thresholdOut;

void main()
{
  gl_Position = Projection * Model * vec4(position.xyz, 1.0);
  thresholdOut = threshold;
  uvCoords = uv; 
  fragmentColor = color;
}