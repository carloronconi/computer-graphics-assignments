#version 450#extension GL_ARB_separate_shader_objects : enablelayout(location = 0) in vec3 fragPos;layout(location = 1) in vec3 fragNorm;layout(location = 2) in vec4 fragTan;layout(location = 3) in vec2 fragUV;layout(location = 0) out vec4 outColor;layout(binding = 1) uniform sampler2D tex;layout(binding = 3) uniform sampler2D normMap;layout(binding = 4) uniform sampler2D matMap;layout(binding = 2) uniform GlobalUniformBufferObject {	vec3 lightDir;	vec4 lightColor;	vec3 eyePos;} gubo;float ggx( vec3 n, vec3 a, float roughness) {	float dotNA2 = pow(dot(n, a), 2.0);	float roughness2 = pow(roughness, 2);	return 2.0 / (1.0 + sqrt(1.0 + roughness2 * ((1.0 - dotNA2) / dotNA2)));}vec3 BRDF(vec3 V, vec3 N, vec3 L, vec3 Md, float F0, float metallic, float roughness) {	//vec3 V  - direction of the viewer	//vec3 N  - normal vector to the surface	//vec3 L  - light vector (from the light model)	//vec3 Md - main color of the surface	//float F0 - Base color for the Fresnel term	//float metallic - parameter that mixes the diffuse with the specular term.	//                 in particular, parmeter K seen in the slides is: float K = 1.0f - metallic;	//float roughness - Material roughness (parmeter rho in the slides).	//specular color Ms is not passed, and implicitely considered white: vec3 Ms = vec3(1.0f);	vec3 diffuseReflection = Md * clamp(dot(L, N), 0.0f, 1.0f); // Lambert diffuse reflection	float K = 1.0f - metallic;	vec3 Ms = vec3(1.0f);	vec3 halfVector = normalize(L + V); // Blinn - direction of the reflected ray	float pi = radians(180);	float roughness2 = pow(roughness, 2.0);	float clamp2 = pow(clamp(dot(N, halfVector), 0.0, 1.0), 2.0);	float D = roughness2 / (pi * pow(clamp2 * (roughness2 - 1.0) + 1.0, 2.0));	float F = F0 + (1 - F0) * pow(1 - clamp(dot(V, halfVector), 0.0, 1.0), 5.0);	float dotHN = dot(halfVector, N);	float dotVN = dot(V, N);	float dotLN = dot(L, N);	float dotVH = dot(V, halfVector);	// float G = min(1, min(2 * dotHN * dotVN / dotVH, 2 * dotHN * dotLN / dotVH)); // microfacet version	float G = ggx(N, V, roughness) * ggx(N, L, roughness);	vec3 specularReflection = Ms * (D * F * G) / (4 * clamp(dotVN, 0.0, 1.0));	return K * diffuseReflection + (1.0 - K) * specularReflection;}void main() {	vec3 Norm = normalize(fragNorm);	vec3 Tan = normalize(fragTan.xyz - Norm * dot(fragTan.xyz, Norm));	vec3 Bitan = cross(Norm, Tan) * fragTan.w;	mat3 tbn = mat3(Tan, Bitan, Norm);	vec4 nMap = texture(normMap, fragUV);	vec3 N = normalize(tbn * (nMap.rgb * 2.0 - 1.0));	vec3 albedo = texture(tex, fragUV).rgb;	vec4 MRAO = texture(matMap, fragUV);	float roughness = MRAO.g;	float ao = MRAO.b;	float metallic = MRAO.r;		vec3 L = gubo.lightDir;	vec3 lightColor = gubo.lightColor.rgb;	vec3 V = normalize(gubo.eyePos - fragPos);	vec3 DiffSpec = BRDF(V, N, L, albedo, 0.3f, metallic, roughness);	vec3 Ambient = albedo * 0.05f * ao;		outColor = vec4(clamp(0.95 * DiffSpec * lightColor.rgb + Ambient,0.0,1.0), 1.0f);}