#version 330 core
precision highp float;

in vec2 ex_uv;
in vec4 ex_normal;

out vec4 gl_FragColor;

uniform sampler2D textureSampler;

void main(void) {
	gl_FragColor = texture(textureSampler, ex_uv);
}
