#version 120
#extension GL_ARB_texture_rectangle : enable

varying vec2 v_texCoord;

void main(void)
{
  v_texCoord = gl_MultiTexCoord0.st;
  
  gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
