#version 120


// These are the names used by coin to define uniform variables.
// Don't change them!
varying vec4 eposition;
varying vec3 normal;
varying vec3 diffuseColor;
varying vec3 specularColor;
varying vec3 emissiveColor;
varying vec3 ambientColor;
varying float shininess;
varying vec2 vST;

void main(){

	// Position in clip space
	//gl_Position = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xyz*1.05, 1.0);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	// Position in eye space
	eposition = gl_ModelViewMatrix * gl_Vertex;

	// Normal in eye space
	normal = mat3(gl_ModelViewMatrix) * gl_Normal;


	// Retrieves diffuse, specular emissive, and ambient color from the OpenGL state.
	diffuseColor = vec3(gl_FrontMaterial.diffuse);
	specularColor = vec3(gl_FrontMaterial.specular);
	emissiveColor = vec3(gl_FrontMaterial.emission);
	ambientColor = vec3(gl_FrontMaterial.ambient);
	shininess = gl_FrontMaterial.shininess;
	vST = gl_MultiTexCoord0.st;
}

