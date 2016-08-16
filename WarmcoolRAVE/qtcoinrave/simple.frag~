// Gooch Lighting w/ Specular Effects
// Author: Julio Medina
// jamedina@hmc.edu
// 6.20.2016

#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

// Ouput data
out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform vec3 LightPosition_worldspace;
uniform vec3 LightColor = vec3(1);
uniform float LightPower = 30;
uniform vec3 MaterialSpecularColor = vec3(1);


vec3 specular_light( vec3 light_color,
                     vec3 light_position,
                     vec3 light_direction,
                     vec3 vertex_normal,
                     vec3 vertex_position,
                     vec3 eye_direction,
                     vec3 material_color,
                     float light_power){

        //Distance calculation
        float distance = length( light_position - vertex_position );

        //Normalize all the things
        vec3 n = normalize( vertex_normal );
        vec3 l = normalize( light_direction );
        vec3 E = normalize( eye_direction );

        // Direction in which the triangle reflects the light
        vec3 R = reflect(-l,n);

        // Cosine of angle between Eye vector and Reflect vector, clamped.
        // Looking into the reflection = 1. Looking perpendicular = 0
        float cosAlpha = clamp( dot( E,R ), 0,1 );

        return material_color * light_color * light_power * pow(cosAlpha,5) / (distance*distance);
}


vec3 gooch_shading(vec4 m_color,	//material color
                   float m_shine,	//surface shininess
                   vec3 l_direction,	//light direction
                   vec3 v_normal ){	//vertex normal

    //Initialize constants
    float coolScalar = 0.7;
    float warmScalar = 0.2;
    vec3 Kcool = vec3(0, 0, 0.8) + coolScalar * m_color.xyz;
    vec3 Kwarm = (vec3(0.9, 0.5, 0) + warmScalar * m_color.xyz);

    //Compute the final color by scaling Kcool and Kwarm
    float NL = dot(normalize(v_normal), normalize(l_direction));
    float it = ((1 + 1.5* NL) / 2);
    vec3 color = (1-(0.8*it)) * Kcool + it * Kwarm;

    return color;
}


void main(){

        if( dot(Normal_cameraspace, EyeDirection_cameraspace) < .05f){
            color = vec3(0,0,0);
        }
        else{
            color = gooch_shading( vec4(.2),
                                   .1,
                                   LightDirection_cameraspace,
                                   Normal_cameraspace)

            + specular_light( LightColor,
                              LightPosition_worldspace,
                              LightDirection_cameraspace,
                              Normal_cameraspace,
                              Position_worldspace,
                              EyeDirection_cameraspace,
                              MaterialSpecularColor,
                              LightPower);
        }

       // color = texture(myTextureSampler, UV).xyz;

}
