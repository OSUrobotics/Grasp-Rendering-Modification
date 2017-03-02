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
uniform	sampler2D ImageUnit;

void main()
{
	ivec2 ires = textureSize( ImageUnit, 0 );
	float ResS = float( ires.s );
	float ResT = float( ires.t );
	float ResS = 5.;
	float ResT = 5.;
	vec3 rgb = texture2D( ImageUnit,  vST ).rgb;

	vec4 color = vec4( 1., 0., 0., 1. );

	vec2 stp0 = vec2(1./ResS,  0. );
	vec2 st0p = vec2(0.     ,  1./ResT);
	vec2 stpp = vec2(1./ResS,  1./ResT);
	vec2 stpm = vec2(1./ResS, -1./ResT);
	float i00 =   dot( texture2D( ImageUnit, vST ).rgb, vec3(0.2125,0.7154,0.0721) );
	float im1m1 = dot( texture2D( ImageUnit, vST - stpp ).rgb, vec3(0.2125,0.7154,0.0721) );
	float ip1p1 = dot( texture2D( ImageUnit, vST + stpp ).rgb, vec3(0.2125,0.7154,0.0721) );
	float im1p1 = dot( texture2D( ImageUnit, vST - stpm ).rgb, vec3(0.2125,0.7154,0.0721) );
	float ip1m1 = dot( texture2D( ImageUnit, vST + stpm ).rgb, vec3(0.2125,0.7154,0.0721) );
	float im10 =  dot( texture2D( ImageUnit, vST - stp0 ).rgb, vec3(0.2125,0.7154,0.0721) );
	float ip10 =  dot( texture2D( ImageUnit, vST + stp0 ).rgb, vec3(0.2125,0.7154,0.0721) );
	float i0m1 =  dot( texture2D( ImageUnit, vST - st0p ).rgb, vec3(0.2125,0.7154,0.0721) );
	float i0p1 =  dot( texture2D( ImageUnit, vST + st0p ).rgb, vec3(0.2125,0.7154,0.0721) );
	float h = -1.*im1p1 - 2.*i0p1 - 1.*ip1p1  +  1.*im1m1 + 2.*i0m1 + 1.*ip1m1;
	float v = -1.*im1m1 - 2.*im10 - 1.*im1p1  +  1.*ip1m1 + 2.*ip10 + 1.*ip1p1;
	float mag = sqrt( h*h + v*v );
	if( mag > 1. )
	{
		color = vec4( 1., 1., 0., 1. );
	}
	else
	{
		rgb.rgb *= 5.;
		rgb.rgb += vec3( 5., 5., 5. );
		ivec3 irgb = ivec3( rgb.rgb );
		rgb.rgb = vec3( irgb ) / 5.;
		color = vec4( rgb, 1. );
	}
	gl_FragColor = color;
}
