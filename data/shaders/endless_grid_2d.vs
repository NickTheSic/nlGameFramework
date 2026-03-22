#version 450 core


const vec2 Pos[4] = vec2[4](
    vec2(-1.0, -1.0),
    vec2( 1.0, -1.0),
    vec2( 1.0,  1.0),
    vec2(-1.0,  1.0)
);

const int Indices[6] = int[6](0,2,1,2,0,3);

uniform mat4 uViewMat;
uniform vec3 uCameraPosition;
uniform vec2 uScreenSize;

out vec2 WorldPos;

void main()
{
    int Index = Indices[gl_VertexID];
    vec2 vPos = vec2(Pos[Index]) * uScreenSize;

    vPos.x += uCameraPosition.x;
    vPos.y += uCameraPosition.y;

    gl_Position = uViewMat * vec4(vPos, 0.0, 1.0);

    WorldPos = vPos.xy;
}
