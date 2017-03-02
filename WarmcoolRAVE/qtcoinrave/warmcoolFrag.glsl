// Gooch Shading w/ Specular Effects and Silhouettes
// Author: Julio Medina
// jamedina@hmc.edu

// When no GLSL version specified, defaults to 110 

// These are the names used by coin to define uniform variables.
// Don't change them!
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
	vec3 diffuse = diffuseColor * lightColor * NL;	
 

	// Warm Cool Shading
	float coolScalar = 0.25;
	float warmScalar = 0.5;
	vec3 Kcool = vec3(0.0, 0.0, 0.9) + coolScalar * diffuseColor.xyz;
	vec3 Kwarm = vec3(0.9, 0.5, 0.0) + warmScalar * diffuseColor.xyz;

	float it = ( 1.0 + 1.5*NL ) / 2.0;
	vec3 color = ( 1.0 - 0.8*it ) * Kcool + it * Kwarm;


	// Compute the specular term
	vec3 V = normalize(-position_eyespace);     // vector toward the viewpoint
	vec3 H = normalize(light_direction + V);    // vector that is halfway between viewpoint and light
	float specularLight = pow(max(dot(normal_eyespace, H),0), shininess);
	vec3 specular = specColor * lightColor * specularLight; 


	// Define the final vertex color: 
	// If angle is very shallow -> silhouette edge (color black)
	// Otherwise, color normally.

	if( abs(dot(position_eyespace, normal_eyespace)) < 0.05 || NL < 0.12 ){
	gl_FragColor.xyz = vec3(0.0, 0.0, 0.0);
	}

	else{
	//gl_FragColor.xyz = 0.7*color + specular + ambient; // - emissive; 
	gl_FragColor.xyz = mix(Kcool,Kwarm,diffuse) + specular + ambient; // - emissive; 
	}
 
	gl_FragColor.w = 1.0;
 
}


