// ssao vertex shader
#version 120
#extension GL_ARB_texture_rectangle : enable

uniform mat4 u_inverseProjMatrix;

varying vec3 v_vertex;
varying vec2 v_texCoord;

void main()
{
  v_vertex = vec3(gl_ModelViewMatrix * gl_Vertex);
  v_texCoord = gl_MultiTexCoord0.st;

    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}