#version 120

varying vec3 normal;

uniform	mat4 worldToClip;
uniform	vec4 cameraPos;
uniform	vec4 cameraDir;

uniform vec4 modelColor;
varying vec3 diffuseColor;
varying vec3 ambientColor;
varying vec2 vTex;

uniform int numLevels;

float step(float val, int levels)
{
	int level = int(val * levels);
	return float(level) / levels;
}

void main()
{
	float camDotN = clamp(dot(-vec3(cameraDir), normal), 0, 1);
	float brightness = step(camDotN, numLevels);
	gl_FragColor = (0.5 + brightness/2.0) * modelColor; 
	gl_FragColor = vec4(1.,1.,0.,1.);
}
