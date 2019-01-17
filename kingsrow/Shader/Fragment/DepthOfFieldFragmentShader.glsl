#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D renderedTexture;
uniform sampler2D blurredTexture;
uniform sampler2D depthBuffer;
uniform float focusDistance;

uniform mat4 projectionMatrixInverse;

float focalLength = focusDistance / 2;

void main(){
	vec3 basePixel = texture(renderedTexture, UV).rgb;
	vec3 blurPixel = texture(blurredTexture, UV).rgb;
	
	vec2 mappedUV = UV * 2 - 1;

	float depth = texture(depthBuffer, UV).r;
	float focusDepth = texture(depthBuffer, vec2(0.5, 0.5)).r;
	
	vec4 screenCoordinate = vec4(mappedUV, depth, 1);
	vec4 screenFocus = vec4(vec2(0,0), focusDepth, 1);
	vec4 unprojectedCoordinate = inverse(projectionMatrixInverse) * screenCoordinate;
	vec4 unprojectedFocus = inverse(projectionMatrixInverse) * screenFocus;
	
	float scaleTest = length((unprojectedCoordinate.xyz/unprojectedCoordinate.w));
	scaleTest = (scaleTest - 0.1) / (50.0 - 0.1);

	float focusTest = length((unprojectedFocus.xyz/unprojectedFocus.w).xyz);
	focusTest = (focusTest - 0.1) / (50.0 - 0.1);

	float focus = abs(scaleTest - focusTest);
	//if(focus <= 0.005)
	//{
	//	color = vec3(1);
	//}
	//else 
	//{
	//	color = vec3(scaleTest);
	//}
	//color = vec3(1-scaleTest);
	color = mix(basePixel, blurPixel, focus*5);	
}
