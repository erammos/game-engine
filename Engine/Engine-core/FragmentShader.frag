#version 330 core
layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in DATA
{
  vec4 color;
  vec4 pos;
  vec2 texCoord; 
  int tid;
} fs_in;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;

void main(){

    float intesity= 10.0 / length(fs_in.pos.xy- light_pos);
   
	 //color = fs_in.color*intesity;
	int tid= fs_in.tid;

	//if(tid == 0)color = mix(texture(tex0,fs_in.texCoord),vec4((fs_in.tid*4)/255.0f,0.0,0,1),0);
	if(tid == 1)color = vec4(1,0,0,1);
	//if(tid == 2)color = mix(texture(tex2,fs_in.texCoord),vec4((fs_in.tid*4)/255.0f,0.0,0,1),0);

	

	
	// color = vec4(1,1,0,1);
	color =vec4((fs_in.tid*4);
}