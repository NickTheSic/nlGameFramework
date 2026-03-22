#version 450 core

#ifdef GL_ES
precision mediump float;
#endif

out vec4 FragColor;

in vec2 WorldPos;

float log10(float x)
{
    float f = log(x) / log(10);
    return f;
}

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
    float GridMinCellSize = 5.0;
    float gGridCellSize = 0.5;

    float delta_x = clamp(tan(WorldPos.x*0.001), 0.0f, 0.5);
    float delta_y = clamp(tan(WorldPos.y*0.001), 0.0f, 0.5);

    vec4 gGridColourThick = vec4(delta_x,0.0,delta_y,1.0);

    vec2 dvx = vec2(dFdx(WorldPos.x),dFdy(WorldPos.x));
    vec2 dvy = vec2(dFdx(WorldPos.y),dFdy(WorldPos.y));
    float lx = length(dvx);
    float ly = length(dvy);

    vec2 dudv = vec2(lx,ly);

    float l = length(dudv);

    float LOD = max(0.0, log10(l*GridMinCellSize/gGridCellSize) + 1.0);
    float GridLod0 = gGridCellSize * pow(10, floor(LOD));

    dudv *= 4;

    vec2 mod_div_dudv = mod(WorldPos.xy, GridLod0) / dudv;
    float Lod0a = max2( vec2(1.0) - abs(satv(mod_div_dudv) * 2.0 - vec2(1.0)) );
 
    vec4 Colour = gGridColourThick;
    Colour.a *= Lod0a;

    FragColor = Colour;
}