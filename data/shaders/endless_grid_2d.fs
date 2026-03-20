#version 450 core

out vec4 FragColor;

in vec2 WorldPos;

uniform float gGridCellSize = 0.1;
uniform vec4 gGridColourThick = vec4(0.0,0.0,0.0,1.0);
uniform vec4 gGridColourThin  = vec4(0.5,0.5,0.5,1.0);

float max2(vec2 vec)
{
    return max(vec.x, vec.y);
}

vec2 satv(vec2 x)
{
    vec2 v = clamp(x, vec2(0.0), vec2(1.0));
    return v;
}

void main()
{
    vec2 dvx = vec2(dFdx(WorldPos.x),dFdy(WorldPos.x));
    vec2 dvy = vec2(dFdx(WorldPos.y),dFdy(WorldPos.y));
    float lx = length(dvx);
    float ly = length(dvy);

    vec2 dudv = vec2(lx,ly);
    dudv *= 4;

    vec2 mod_div_dudv = mod(WorldPos.xy, gGridCellSize) / dudv;
    float Lod0a = max2( vec2(1.0) - abs(satv(mod_div_dudv) * 2.0 - vec2(1.0)) );
 
    vec4 Colour = gGridColourThick;
    Colour.a *= Lod0a;

    FragColor = Colour;
}