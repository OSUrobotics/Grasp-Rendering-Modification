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

void main(){

	// Position in clip space
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


/*
// Experimental method of rendering silhouettes: Expand the backfaces slightly so they extend past
// the edges of the actual object and create black outlines. I decided this would not be a good
// algorithm because the manipulation of the object's vertices might worsen shape perception 
// instead of improving it.
// Also, coin flips out when you try to do this and I don't know why.
if( dot(gl_Normal.xyz, normalize(eposition.xyz)) <= 0 ){  

	gl_Position = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xyz + (gl_Normal*0.05f), 1.0f);
	//gl_Position = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xyz*1.5f, 1.0f);
}
else{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
*/


}

