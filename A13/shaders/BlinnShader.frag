#version 450#extension GL_ARB_separate_shader_objects : enablelayout(location = 0) in vec3 fragPos;layout(location = 1) in vec3 fragNorm;layout(location = 2) in vec2 fragUV;layout(location = 0) out vec4 outColor;layout(binding = 1) uniform sampler2D tex;layout(binding = 2) uniform GlobalUniformBufferObject {	vec3 lightPos;	// position of the spotlight AKA p	vec3 lightDir;	// direction of the spotlight AKA d	vec4 lightColor;// color of the spotlight		vec3 eyePos;	// position of the viewer} gubo;layout(binding = 3) uniform sampler2D texEmit;const float beta = 2.0f;	// decay exponent of the spotlightconst float g = 3;			// target distance of the spotlightconst float cosout = 0.5;	// cosine of the outer angle of the spotlightconst float cosin  = 0.95;	// cosine of the inner angle of the spotlightconst float gamma = 160.0f;	// cosine power for the Blinn specular reflection// coefficients for the spehrical harmonics ambient light termconst vec3 C00  = vec3( .38f, .43f, .45f)/8.0f;const vec3 C1m1 = vec3( .29f, .36f, .41f)/8.0f;const vec3 C10  = vec3( .04f, .03f, .01f)/8.0f;const vec3 C11  = vec3(-.10f,-.10f,-.09f)/8.0f;const vec3 C2m2 = vec3(-.06f,-.06f,-.04f)/8.0f;const vec3 C2m1 = vec3( .01f,-.01f,-.05f)/8.0f;const vec3 C20  = vec3(-.09f,-.13f,-.15f)/8.0f;const vec3 C21  = vec3(-.06f,-.05f,-.04f)/8.0f;const vec3 C22  = vec3( .02f, .00f,-.05f)/8.0f;vec3 BRDF(vec3 V, vec3 N, vec3 L, vec3 Md, vec3 Ms, float gamma) {	//vec3 V  - direction of the viewer	//vec3 N  - normal vector to the surface	//vec3 L  - light vector (from the light model)	//vec3 Md - main color of the surface	//vec3 Ms - specular color of the surface	//float gamma - Exponent for power specular term	vec3 halfVector = normalize(L + V); // direction of the reflected ray	vec3 diffuseReflection = Md * clamp(dot(L, N), 0.0f, 1.0f); // Lambert	vec3 specularReflection = Ms * pow(clamp(dot(N, halfVector), 0.0f, 1.0f), gamma) ; // Blinn	return diffuseReflection + specularReflection;}void main() {	vec3 N = normalize(fragNorm);				// surface normal - Norm	vec3 V = normalize(gubo.eyePos - fragPos);	// viewer direction - V	vec3 MD = texture(tex, fragUV).rgb;			// diffuse color - albedo	vec3 MA = MD;								// ambient color - Ambient	vec3 MS = vec3(1);							// specular color - Ms argument of BRDF	vec3 ME = texture(texEmit, fragUV).rgb;		// emission color	// Write the shader here	// SPOT LIGHT - not sure which was requested among direct, point or spot, decided for spot because shader constants seem to indicate that	vec3 lightDir = normalize(gubo.lightDir); // d	float arg = (dot(normalize(gubo.lightPos - fragPos), lightDir) - cosout) / (cosin - cosout);	vec3 lightColor = gubo.lightColor.rgb * pow((g / length(gubo.lightPos - fragPos)), beta) * clamp(arg, 0.0, 1.0);	vec3 DiffSpec = BRDF(V, N, lightDir, MD, MS, gamma);	// 𝒍𝐴 𝑥 =𝒄0,0 + 𝑛𝑥 .𝑥∙𝒄1,1 + 𝑛𝑥 .𝑦∙𝒄1,−1 + 𝑛𝑥 .𝑧∙𝒄1,0 +	//+ 𝑛𝑥 .𝑥∙ 𝑛𝑥 .𝑦 ∙𝒄2,−2+ 𝑛𝑥 .𝑦∙ 𝑛𝑥 .𝑧 ∙𝒄1,−1+ 𝑛𝑥 .𝑧∙ 𝑛𝑥 .𝑥 ∙𝒄1,1+	//+ 𝑛𝑥 .𝑥2− 𝑛𝑥 .𝑦2 ∙𝒄2,2+ 3∙ 𝑛𝑥 .𝑧2−1 ∙𝒄2,0	// c00 c1m1 c10 c11...	vec3 LA = C00 + N.x * C11 + N.y * C1m1 + N.z * C10 +	N.x * N.y * C2m2 + N.y * N.z * C1m1 + N.z * N.x * C11 +	(pow(N.x, 2.0) - pow(N.y, 2.0)) * C22 + (3 * pow(N.z, 2.0)- 1) * C20;	outColor = vec4(clamp(DiffSpec * lightColor + LA * MA + ME, 0.0, 1.0), 1.0f); // output color}