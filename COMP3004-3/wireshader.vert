#version 330 core
in vec3 in_position;
in vec2 in_uv;
in vec3 in_normal;
out vec2 ex_uv;
out vec4 ex_normal;

uniform mat4 MVP;

void main(){
    vec4 v = vec4(in_position,1);
    gl_Position = MVP * v;
	ex_uv = in_uv;
	ex_normal = vec4(in_normal,0);
}