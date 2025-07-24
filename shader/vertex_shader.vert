#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec4 aColor;
out vec4 vertex_color;
void main() {
    gl_Position = vec4(vertexPosition_modelspace, 1.0f);
    vertex_color = aColor;
}

