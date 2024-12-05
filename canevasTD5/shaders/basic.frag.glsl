#version 150 core

// couleur émise pour le pixel
in vec4 color;

out vec4 frag_color;

void main( void )
{
    frag_color =  color;
   //frag_color = vec4( mod(ceil(gl_FragCoord.x/30)+ceil(gl_FragCoord.y/10), 2), 0.0, 0.0, 1.0 );
   //frag_color = vec4( pow(cos(gl_FragCoord.x*0.02),2.0), 0.0, 0.0, 1.0 );
}
