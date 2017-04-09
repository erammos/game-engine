#version 330 core
layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in DATA
{
  vec4 color;
  vec4 pos;
  vec4 tex; 
} fs_in;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;

void main(){

   // float intesity= 10.0 / length(fs_in.pos.xy- light_pos);
   
	
	highp int tid = int( fs_in.tex.z);
	
	if(tid == 0)color = vec4(1,0,0,1);
	if(tid == 1)color = vec4(1,1,0,1);
	if(tid == 2)color = vec4(1,0,1,1);
	
  

}