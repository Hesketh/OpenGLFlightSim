#version 430

layout (binding = 0) uniform sampler2D texColour;
layout (binding = 1) uniform sampler2D texNormal;
layout (binding = 2) uniform sampler2D texSpec;
layout (binding = 3) uniform sampler2D texEnv;
layout (binding = 4) uniform sampler2D shadowmap;

in vec4 outNormal;	//input: normal
in vec4 lightvec;	//input: light vector
in vec4 viewvec;	//input: view vector
in vec2 outUV;		//input: texcoords
in vec4 outPosInLight;	//input: position in light space

layout (location = 0) out vec4 outFrag;

void main()
{
	//Ambient
	vec4 ambient = texture(texColour, outUV) * vec4(0.25,0.25,0.25,1.0);

	//Lambertian Diffuse
	float angleDiffuse = clamp(dot(outNormal, normalize(lightvec)),0,1);
	vec4 diffuse = texture(texColour, outUV) * (angleDiffuse);

	//Phong Specular - TODO
	//vec4 reflected = normalize(reflect(-lightvec, outNormal));
	//float angleSpecular = clamp(dot(viewvec, reflected),0,1);
	//vec4 specular = /*texture(texColour, outUV)*/ vec4(1,1,1,1) * pow(angleSpecular,10);

	outFrag = ambient + diffuse;// + specular;
}