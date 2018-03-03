#version 330

layout(location = 0) in vec3 posAttr;
layout(location = 1) in vec3 colAttr;
layout(location = 2) in vec2 vertexUV;

out vec2 UV;
uniform mat4 matrix;

void main()
{
   gl_Position = matrix * vec4(posAttr, 1.0);
   UV = vertexUV;
}
