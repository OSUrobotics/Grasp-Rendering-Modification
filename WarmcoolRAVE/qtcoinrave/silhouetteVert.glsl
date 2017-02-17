#version 120
varying vec3 vpos;

varying vec4 eposition;
varying vec3 normal;
varying vec3 diffuseColor;
varying vec3 specularColor;
varying vec3 emissiveColor;
varying vec3 ambientColor;
varying float shininess;

uniform	mat4 worldToClip;
uniform	vec4 cameraPos;
uniform	vec4 cameraDir;

uniform float scale;

void main()
{
	normal = mat3(gl_ModelViewMatrix) * gl_Normal;
	gl_Position = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xyz*1.1, 1.0);
}
