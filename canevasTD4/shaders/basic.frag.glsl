#version 150 core

// couleur émise pour le pixel
out vec4 frag_color;

in vec4 gl_FragCoord;

void main(void)
{
  frag_color = vec4( sin(gl_FragCoord.x/5+5), sin(gl_FragCoord.x/5), 0.0, 1.0 );
}
