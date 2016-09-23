#version 430

layout(location = 0) out vec4  outColor;
layout(location = 1) out vec4 outSpecular;

in vec3 vPosition;
in vec3 vNormal;
in vec2 vUV;

layout(location = 1) uniform mat4 view;
layout(location = 3) uniform sampler2D diffuseMap;
layout(location = 4) uniform sampler2D normalMap;
layout(location = 5) uniform sampler2D specularMap;

mat3 cotangent_frame(in vec3 N, in vec3 p, in vec2 uv);

uniform vec3 L = normalize(vec3(1,0,1));

void main ()
{
	mat3 TBN = cotangent_frame(vNormal, vPosition, vUV);
	vec3 N = TBN * (texture(normalMap, vUV).xyz * 2 - 1);

	vec3 R = reflect(L, N);
	vec3 E = normalize(view[3].xyz + vPosition);
	float sP = 2;

	float lamb = max(0, -dot(L, N));
	float spec = max(0, -dot(E, R));
	
	if(spec > 0)
		spec = pow(spec, sP);

	outColor = texture(diffuseMap, vUV) * lamb;
	outSpecular = texture(specularMap, vUV) * spec;
}

mat3 cotangent_frame( in vec3 N, in vec3 p, in vec2 uv)
{
	vec3 dp1 = dFdx( p );
	vec3 dp2 = dFdy( p );
	vec2 duv1 = dFdx(uv);
	vec2 duv2 = dFdy(uv);

	vec3 dp2perp = cross( dp2, N );
	vec3 dp1perp = cross( N, dp1 );

	vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;
	vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;

	float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );
	return mat3( T * invmax, B * invmax, N);
}