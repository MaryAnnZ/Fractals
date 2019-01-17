#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D renderedTexture;

void main(){
	vec4 pixel = vec4(texture(renderedTexture, UV).xyz, 1);
	vec4 alphaPixel = vec4(pixel.rgb, 0);
	if (length(pixel) > 1.4)
	{
		color = pixel;
	}
	else
	{
		color = alphaPixel;
	}
}