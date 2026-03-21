#version 450 core

layout (location = 0) in vec3 aPos;           
layout (location = 1) in vec4 aCol;   

uniform mat4 uViewMat;                        
uniform mat4 uProjMat;  

out vec4 oColour;  

void main() 
{                                 
   vec4 viewPos = vec4(aPos, 1.0);            
   gl_Position = uProjMat * uViewMat * viewPos;
   oColour = aCol;                            
}                                             