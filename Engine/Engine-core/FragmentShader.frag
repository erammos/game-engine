#version 330 core
layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in DATA
{
  vec4 color;
  vec4 pos;
  vec2 texCoord; 
  float tid;
} fs_in;

uniform sampler2D tex[32];
void main(){

    float intesity= 10.0 / length(fs_in.pos.xy- light_pos);
   
	 //color = fs_in.color*intesity;
	 int tid= int(fs_in.tid+ 0.5);

	 color = texture(tex[tid],fs_in.texCoord)* intesity;
	 
}