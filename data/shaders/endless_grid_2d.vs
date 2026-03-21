#version 450 core
#ifdef GL_ES
precision mediump float;
#endif

const vec2 Pos[4] = vec2[4](
    vec2(-1.0, -1.0),
    vec2( 1.0, -1.0),
    vec2( 1.0,  1.0),
    vec2(-1.0,  1.0)
);

const int Indices[6] = int[6](0,2,1,2,0,3);

uniform mat4 ViewMat;
uniform vec3 CameraPosition;
uniform float GridSize = 2.0;

out vec2 WorldPos;

void main()
{
    int Index = Indices[gl_VertexID];
    vec4 vPos = vec4(Pos[Index], 0.0, 1.0) * GridSize;

    vPos.x += CameraPosition.x;
    vPos.y += CameraPosition.y;

    gl_Position = ViewMat * vPos;

    WorldPos = vPos.xy;
}
