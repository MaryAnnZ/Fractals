#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D renderedTexture;
uniform bool horizontal;
uniform vec2 pixelSize;

const vec2 gaussFilter[31] = vec2[](
	vec2(-15.0, 0.009091),
	vec2(-14.0, 0.0114),
	vec2(-13.0, 0.014073),
	vec2(-12.0, 0.017104),
	vec2(-11.0, 0.020466),
	vec2(-10.0, 0.02411),
	vec2(-9.0, 0.027962),
	vec2(-8.0, 0.031928),
	vec2(-7.0, 0.035893),
	vec2(-6.0, 0.039724),
	vec2(-5.0, 0.043284),
	vec2(-4.0, 0.046433),
	vec2(-3.0, 0.04904),
	vec2(-2.0, 0.05099),
	vec2(-1.0, 0.052198),
	vec2(0.0, 0.052607),
	vec2(1.0, 0.052198),
	vec2(2.0, 0.05099),
	vec2(3.0, 0.04904),
	vec2(4.0, 0.046433),
	vec2(5.0, 0.043284),
	vec2(6.0, 0.039724),
	vec2(7.0, 0.035893),
	vec2(8.0, 0.031928),
	vec2(9.0, 0.027962),
	vec2(10.0, 0.02411),
	vec2(11.0, 0.020466),
	vec2(12.0, 0.017104),
	vec2(13.0, 0.014073),
	vec2(14.0, 0.0114),
	vec2(15.0, 0.009091));

 
void main(){
	vec4 pixel = texture(renderedTexture, UV);

	vec4 tempColor = vec4(0);
	if (horizontal)
	{
		for (int i = 0; i < 31; i++)
		{
			vec2 sampleUV;
			sampleUV = vec2(UV.x + gaussFilter[i].x * pixelSize.x, UV.y);
			tempColor += texture(renderedTexture, sampleUV) * gaussFilter[i].y;
		}
	}
	else
	{
		for (int i = 0; i < 31; i++)
		{
			vec2 sampleUV;
			sampleUV = vec2(UV.x, UV.y + gaussFilter[i].x * pixelSize.y);
			tempColor += texture(renderedTexture, sampleUV) * gaussFilter[i].y;
		}
	}
	if (pixel.a == 1)
	{
		tempColor.a = 1;
	}

	color = tempColor;
}
