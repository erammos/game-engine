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
	if(tid < 0)
	{
	     color = fs_in.color;
	}
	else if(tid  > 0)
	{
	float a = texture(tex[1],fs_in.tex.xy).r;
	color =  vec4(fs_in.color.rgb, fs_in.color.a*a) ;
	}
	else
	{
	  color = texture(tex[0],fs_in.tex.xy) ;
	}
	

}