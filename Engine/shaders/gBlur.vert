// Gaussian blur vertex shader
#version 120
#extension GL_ARB_texture_rectangle : enable

void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}

