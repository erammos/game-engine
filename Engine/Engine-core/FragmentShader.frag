#version 330 core
layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in DATA
{
  vec4 color;
  vec4 pos;
  vec4 tex; 
} fs_in;

uniform sampler2D tex[31];


void main(){

    float intesity= 50.0 / length(fs_in.pos.xy- light_pos);
   
	
	highp int tid = int( fs_in.tex.z);
	
	color = texture(tex[tid],fs_in.tex.xy);

}