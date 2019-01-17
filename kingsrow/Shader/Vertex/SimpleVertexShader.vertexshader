#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal_modelspace;
layout(location = 2) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 Normal_cameraspace;
out vec3 vertexPosition_cameraspace;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 M;

void main()
{
    gl_Position = MVP * vec4(vertexPosition_modelspace, 1.0f);
    vertexPosition_cameraspace = vec3(M * vec4(vertexPosition_modelspace, 1.0f));
    Normal_cameraspace = mat3(transpose(inverse(M))) * vertexNormal_modelspace;  
    UV = vertexUV;
} 

