
#version 150 core

in vec2 texcoord;
in vec3 colors;

out vec4 frag_color;

uniform sampler2D tex;


void main(void)
{
  frag_color = texture( tex, texcoord );
  frag_color =  vec4(colors, 0.5 );
 
}
