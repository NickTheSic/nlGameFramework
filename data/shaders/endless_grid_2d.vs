#version 450 core


const vec2 Pos[4] = vec2[4](
    vec2(-1.0, -1.0),
    vec2( 1.0, -1.0),
    vec2( 1.0,  1.0),
    vec2(-1.0,  1.0)
);

const int Indices[6] = int[6](0,2,1,2,0,3);

uniform mat4 ViewMat;
uniform vec3 CameraPosition;
uniform vec2 ScreenSize;

out vec2 WorldPos;

void main()
{
    int Index = Indices[gl_VertexID];
    vec2 vPos = vec2(Pos[Index]) * ScreenSize;

    vPos.x += CameraPosition.x;
    vPos.y += CameraPosition.y;

    gl_Position = ViewMat * vec4(vPos, 0.0, 1.0);

    WorldPos = vPos.xy;
}
