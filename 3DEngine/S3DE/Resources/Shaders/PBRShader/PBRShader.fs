#version 330

in vec3 fragPos;
in vec3 fragNormal;
in vec3 fragTangent;
in vec2 fragUvs;
in vec3 dist;

#define USE_ALBEDO_MAP 			1
#define USE_NORMAL_MAP 			2
#define NOT_AFFECTED_BY_LIGHTS 	4
#define USE_METALLIC_MAP 		8
#define USE_ROUGHNESS_MAP 		16
#define USE_AO_MAP 			    32

layout(std140) uniform Material
{
    vec4 metallic_roughness_ao;
	vec4 color_flags;
} material;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;
uniform sampler2D metallicMap;
uniform sampler2D roughnessMap;
uniform sampler2D aoMap;

struct LightData
{
	vec4 positionIntensity;
	vec4 colorRadius;
	vec4 directionType;
};

#define MAX_LIGHTS 10
layout(std140) uniform Lights
{
  LightData data[MAX_LIGHTS];
  int numLights;
  int[3] padding;
} lights;

out vec4 finalColor;

uniform vec3 camPos;
uniform bool useWireframe;

const float screenGamma = 2.2; // Assume the monitor is calibrated to the sRGB color space.

float getLightAttenuation(float d, float radius)
{
	if(d >= radius) return 0.0;
	return (radius-d)/radius;
}

const float PI = 3.14159265359;

/*  Normal Distribution Function (NDF) "Like specular"
    n: Normal vector
    h: halfway vector
    roughness: [0,1]
*/
float distributionGGX(vec3 n, vec3 h, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float nDotH = max(dot(n, h), 0.0);
    float denom = nDotH * nDotH * (a2 - 1.0) + 1.0;
    denom = PI * denom * denom;
    return a2/denom;
}

float geometrySchlickGGX(float nDotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;
    return nDotV / (nDotV * (1.0 - k) + k);
}

/*  Geometry function "like diffuse, self shadowing microfacets"
    n: Normal vector
    v: View direction vector
    l: Light direction vector
    roughness: [0,1]
*/
float geometrySmith(vec3 n, vec3 v, vec3 l, float roughness)
{
    float nDotV = max(dot(n, v), 0.0);
    float nDotL = max(dot(n, l), 0.0);
    float ggx1 = geometrySchlickGGX(nDotV, roughness);
    float ggx2 = geometrySchlickGGX(nDotL, roughness);
    return ggx1*ggx2;
}

/*  Fresnel equation "Reflects more if angle is greater"
    f0:         Base reflectivity of a surface
    cosTheta:   dot(n, v)
*/
vec3 fresnelSchlick(float cosTheta, vec3 f0)
{
    return f0 + (1.0 - f0) * pow(1.0 - cosTheta, 5.0);
}

void main()
{
    vec3 normal = normalize(fragNormal);
    vec3 v = normalize(camPos - fragPos);

    // Get material color
	vec3 albedo = vec3(0.0);
	if((int(material.color_flags.w) & USE_ALBEDO_MAP) == USE_ALBEDO_MAP)
		albedo = texture(albedoMap, fragUvs).rgb; // Should be raised to the power of screenGamma
	else
		albedo = material.color_flags.rgb;

    // Get metallic factor
    float metallic = 0.0;
    if((int(material.color_flags.w) & USE_METALLIC_MAP) == USE_METALLIC_MAP)
		metallic = texture(metallicMap, fragUvs).r;
	else
		metallic = material.metallic_roughness_ao.x;

    // Get roughness factor
    float roughness = 0.0;
    if((int(material.color_flags.w) & USE_ROUGHNESS_MAP) == USE_ROUGHNESS_MAP)
		roughness = texture(roughnessMap, fragUvs).r;
	else
		roughness = material.metallic_roughness_ao.y;
    roughness = max(roughness, 0.1);

    // Get ao factor
    float ao = 0.0;
    if((int(material.color_flags.w) & USE_AO_MAP) == USE_AO_MAP)
		ao = texture(aoMap, fragUvs).r;
	else
		ao = material.metallic_roughness_ao.z;

    // Get normal
    if((int(material.color_flags.w) & USE_NORMAL_MAP) == USE_NORMAL_MAP)
    {
	    vec3 tangent = normalize(fragTangent);
	    vec3 bitangent = cross(tangent, normal);
	    mat3 tbn = mat3(tangent, bitangent, normal); // Tangent space to world space.
	    normal = normalize((tbn*(texture(normalMap, fragUvs).xyz*2.0 - 1.0)));
    }

    vec3 lo = vec3(0.0);
	if((int(material.color_flags.w) & NOT_AFFECTED_BY_LIGHTS) == 0)
	{
        // Light code here.
        for(int i = 0; i < lights.numLights; i++)
		{
			LightData light = lights.data[i];
            if(light.directionType.w == 0) // Point light
            {
                vec3 lightPos = light.positionIntensity.xyz;
                vec3 lightColor = light.colorRadius.rbg;
                vec3 fragToLight = lightPos - fragPos;

                vec3 l = normalize(fragToLight);
                vec3 h = normalize(v + l);

                float d = length(l);
	            float attenuation = 1.0/(d*d);  //getLightAttenuation(length(fragToLight), lightRadius);
                vec3 radiance = lightColor * attenuation;

                vec3 f0 = vec3(0.04);
                f0 = mix(f0, albedo, metallic); // The surface reflection at zero incidence.
                vec3 f = fresnelSchlick(max(dot(v, h), 0.0), f0); // Ratio of light that gets reflected on the surface.
                float ndf = distributionGGX(normal, h, roughness);
                float g = geometrySmith(normal, v, l, roughness);

                vec3 nominator = ndf * g * f;
                float denominator = 4.0 * max(dot(normal, v), 0.0) * max(dot(normal, l), 0.0);
                vec3 specular = nominator / max(denominator, 0.001);

                vec3 ks = f;
                vec3 kd = vec3(1.0) - ks;
                kd *= 1.0 - metallic;

                float nDotL = max(dot(normal, l), 0.0);
                lo += (kd * albedo / PI + specular) * radiance * nDotL;
            } 
            else if(light.directionType.w == 1) // Directional light
            {
                vec3 lightPos = light.positionIntensity.xyz;
                vec3 lightColor = light.colorRadius.rbg;
                vec3 invLightDirection = -light.directionType.xyz;
                vec3 radiance = lightColor;

                vec3 l = invLightDirection;
                vec3 h = normalize(v + l);

                vec3 f0 = vec3(0.04);
                f0 = mix(f0, albedo, metallic); // The surface reflection at zero incidence.
                vec3 f = fresnelSchlick(max(dot(v, h), 0.0), f0); // Ratio of light that gets reflected on the surface.
                float ndf = distributionGGX(normal, h, roughness);
                float g = geometrySmith(normal, v, l, roughness);

                vec3 nominator = ndf * g * f;
                float denominator = 4.0 * max(dot(normal, v), 0.0) * max(dot(normal, l), 0.0);
                vec3 specular = nominator / max(denominator, 0.001);

                vec3 ks = f;
                vec3 kd = vec3(1.0) - ks;
                kd *= 1.0 - metallic;

                float nDotL = max(dot(normal, l), 0.0);
                lo += (kd * albedo / PI + specular) * radiance * nDotL;
            }
        }
       
	}
	else
	{
        lo = albedo;
	}

    vec3 ambient = vec3(0.03) * albedo * ao;
    vec3 color = ambient + lo;

    if(useWireframe)
	{
		vec3 d = fwidth(dist);
		vec3 a3 = smoothstep(vec3(0.0), d * 0.8, dist);
		float edgeFactor = min(min(a3.x, a3.y), a3.z);
		color = mix(vec3(1.0, 1.0, 1.0), color, edgeFactor);
	}

    color = color / (color + vec3(1.0));
    vec3 colorGammaCorrected = pow(color, vec3(1.0/screenGamma));
    finalColor = min(vec4(colorGammaCorrected, 1.0), 1.0);
}