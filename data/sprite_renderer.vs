#version 300 es 

precision mediump float;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aUV_coord;                            
layout (location = 2) in vec4 aCol;
uniform mat4 uModelMat;
uniform mat4 uViewMat;
uniform mat4 uProjMat;

out vec2 uv_coords;
out vec4 oCol;

void main()
{
   gl_Position = uProjMat * uViewMat * uModelMat * vec4(aPos,1.0);
   uv_coords = aUV_coord;
   oCol = aCol;
}