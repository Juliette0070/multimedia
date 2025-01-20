
#version 150 core

in vec2 texcoord;
in vec3 colors;

out vec4 frag_color;

uniform sampler2D tex;
uniform sampler2D tex2;


void main(void)
{
  frag_color = texture(tex2, texcoord);
  frag_color = mix(frag_color, vec4(1.0, 1.0, 1.0, 1.0), 0.3);
  frag_color *= texture(tex, texcoord);
}
