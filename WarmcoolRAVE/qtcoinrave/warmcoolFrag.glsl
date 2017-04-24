#version 120
// Gooch Shading based off of Julio Medina's initial code
// Author: Matt Huang

// When no GLSL version specified, defaults to 110 

// These are the names used by coin to define uniform variables.
// Don't change them!
varying vec2 vST;
varying vec4 eposition;
varying vec3 normal;
varying vec3 diffuseColor;
varying vec3 specularColor;
//varying vec3 emissiveColor;  
varying vec3 ambientColor;
varying float shininess;

void main(){
	// Define lighting constants
	const vec3 lightColor = vec3(1.0);
	const vec3 specColor  = vec3(1.0);
	const vec3 globalAmbient = vec3(0.2);
  
	// Convert to eyespace
	vec3 position_eyespace = vec3(eposition);
	vec3 normal_eyespace = normalize(normal);

	// Compute the emissive and ambient terms
	// vec3 emissive = emissiveColor;
        vec3 ambient = ambientColor * globalAmbient;


	// Compute the diffuse term
	vec3 light_direction = normalize(vec3(gl_LightSource[0].position) - position_eyespace);
	float NL = max(dot(normal_eyespace, light_direction), 0);
	//vec3 diffuse = diffuseColor * lightColor * NL;	
	vec3 diffuse = vec3(1.,1.,1.) * lightColor * NL;	 

	// Warm Cool Shading
	vec3 Kcool;
	vec3 Kwarm;
	vec3 coolcolor = vec3(0.,0.,0.);
	vec3 warmcolor = vec3(0.,0.,0.);
	float coolScalar = 0.25;
	float warmScalar = 0.25;
	if(diffuseColor.x >= diffuseColor.y + 0.15 && diffuseColor.x >= diffuseColor.z+0.15){
		//Warmcool for Red
		coolcolor = vec3(1.,0.,0.);
		warmcolor = vec3(1.,1.,0.);
	}
	else if(diffuseColor.y >= diffuseColor.x + 0.15 && diffuseColor.y >= diffuseColor.x + 0.15){
		//Warmcool for Green
		coolcolor = vec3(0.,0.,1.);
		warmcolor = vec3(0.,1.,0.);
	}
	else if(diffuseColor.z >= diffuseColor.x + 0.15 && diffuseColor.z >= diffuseColor.y + 0.15){
		//Warmcool for Blue
		coolcolor = vec3(1.,0.,1.);
		warmcolor = vec3(0.,0.,1.);
	}
	else if(diffuseColor.x > diffuseColor.z+0.15 && diffuseColor.y > diffuseColor.z+0.15 && abs(diffuseColor.x - diffuseColor.y) < 0.15){
		//Warmcool for yellow
		coolcolor = vec3(1.,1.,1.);
		warmcolor = vec3(0.,1.,1.);
	}
	else if(diffuseColor.x > diffuseColor.y+0.15 && diffuseColor.z > diffuseColor.y+0.15 && abs(diffuseColor.x - diffuseColor.z) < 0.15){
		//Warmcool for purple
		coolcolor = vec3(0.,1.,1.);
		warmcolor = vec3(0.,0.,1.);
	}
	else if(diffuseColor.z > diffuseColor.x+0.15 && diffuseColor.y > diffuseColor.x+0.15 && abs(diffuseColor.z - diffuseColor.y) < 0.15){
		//Warmcool for cyan
		coolcolor = vec3(0.,0.,1.);
		warmcolor = vec3(0.,1.,1.);
	}
	else if(diffuseColor.x > 0.5 && diffuseColor.y > 0.5 && diffuseColor.z > 0.5){
		//Warmcool for white
		coolcolor = vec3(0.,0.,1.);
		warmcolor = vec3(1.,1.,1.);
	}
	else if(diffuseColor.x <= 0.5 && diffuseColor.y <=0.5 && diffuseColor.z <= 0.5){
		//Warmcool for black
		coolcolor = vec3(0., 0., 1.);
		warmcolor = vec3(0.8,0.8,0.8);	
	}
	Kcool = coolcolor + coolScalar * diffuseColor.xyz;
	Kwarm = warmcolor + warmScalar * diffuseColor.xyz;
	
	// Compute the specular term
	vec3 V = normalize(-position_eyespace);     // vector toward the viewpoint
	vec3 H = normalize(light_direction + V);    // vector that is halfway between viewpoint and light
	float newshininess = 10* shininess;
	float specularLight = pow(max(dot(normal_eyespace, H),0), newshininess);
	vec3 specular = specColor * lightColor * specularLight; 


	// Define the final vertex color: 
	gl_FragColor.xyz = mix(Kcool,Kwarm,diffuse) + specular + ambient; // - emissive;
	gl_FragColor.w = 1.0;
	//discard;
}


