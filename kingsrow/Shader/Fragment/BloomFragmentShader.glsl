#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D renderedTexture;
uniform sampler2D bloomTexture;


void main(){
	vec3 basePixel = texture(renderedTexture, UV).rgb;
	vec4 bloomPixel = texture(bloomTexture, UV);
	if (bloomPixel.a == 1)
	{
		color = mix(basePixel.rgb, bloomPixel.rgb, 0.8);	//decreases quality, but subjectively (= in my oppinion) makes bloom look better. if we don't want this remove the whole if/else part
	}
	else
	{
		color = mix(basePixel.rgb, bloomPixel.rgb, bloomPixel.a);
	}
	//color = (bloomPixel.rgb * bloomPixel.a + basePixel * (1 - bloomPixel.a)).rgb;
}
