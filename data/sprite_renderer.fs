#version 300 es
precision mediump float;

out vec4 FragColor;                                        

in vec2 uv_coords;                                         
in vec4 oCol;                                              

uniform sampler2D sprite_texture;                          

void main() 
{                                              
    FragColor = texture(sprite_texture,uv_coords) * oCol;  
}