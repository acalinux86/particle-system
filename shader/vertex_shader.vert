#version 460 core
layout(location = 0) in vec3 vertexPosition_pixels;
layout(location = 1) in vec4 aColor;

uniform vec2 screenSize;

out vec4 vertex_color;

void main()
{
    float x = vertexPosition_pixels.x / screenSize.x * 2.0 - 1.0;

    float y = vertexPosition_pixels.y / screenSize.y * 2.0 - 1.0;  // no Y flip

    gl_Position = vec4(x, y, vertexPosition_pixels.z, 1.0);
    vertex_color = aColor;
}
