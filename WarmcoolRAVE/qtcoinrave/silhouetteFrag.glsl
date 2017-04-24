#version 130

varying vec3 normal;

uniform	mat4 worldToClip;
uniform	vec4 cameraPos;
uniform	vec4 cameraDir;

uniform vec4 modelColor;
varying vec3 diffuseColor;
varying vec3 ambientColor;
varying vec2 vST;

uniform int numLevels;

void main()
{
	gl_FragColor.xyz = vec3(0.,0.,0.);
	gl_FragColor.w = 0.;
}
