#version 330 core
layout(location = 0) in vec4 model_position;
layout(location = 1) in vec4 model_color;
layout(location = 2) in vec4 model_tex;

uniform mat4 proj_matrix;
uniform mat4 model_matrix;
out DATA
{
   vec4 color;
   vec4 pos;
   vec4 tex;
} vs_out;


void main( ) 
{
 
   gl_Position = proj_matrix * model_position;
   vs_out.color = model_color;
   vs_out.pos = model_position;
   vs_out.tex = model_tex;
}