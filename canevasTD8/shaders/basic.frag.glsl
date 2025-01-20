
#version 150 core

in vec2 texcoord;
in vec3 colors;

out vec4 frag_color;

uniform sampler2D tex;


void main(void)
{
  // frag_color = texture( tex, texcoord );
  // frag_color *=  vec4(colors, 0.5 );
 

  frag_color = vec4(colors, 0.5);
  frag_color.rgb = mix(frag_color.rgb, vec3(1.0), 0.7); // Mélange avec du blanc pour éclaircir les couleurs
  frag_color *= texture(tex, texcoord);
}
