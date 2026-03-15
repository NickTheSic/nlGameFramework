#version 300 es 
precision mediump float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;
layout (location = 2) in vec2 aTexCoord;

out vec3 outColour;
out vec2 outTexCoord;

void main() 
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);

    outColour = aColour;
    outTexCoord = aTexCoord;
}