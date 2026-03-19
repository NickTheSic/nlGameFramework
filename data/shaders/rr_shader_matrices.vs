#version 300 es 
precision mediump float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColour;
layout (location = 2) in vec2 aTexCoord;

out vec3 outColour;
out vec2 outTexCoord;

uniform mat4 uModelTransform;
uniform mat4 uProjection;
uniform mat4 uViewMatrix;

void main() 
{
    gl_Position = uProjection * uViewMatrix * uModelTransform * vec4(aPos.x, aPos.y, aPos.z, 1.0);

    outColour = aColour;
    outTexCoord = aTexCoord;
}