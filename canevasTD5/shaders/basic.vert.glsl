#version 150 core
// version du langage GLSL utilisée, ici 4.5

// in indique que la variable est fournie en entrée pour chaque point
// chaque point possède une position 3D
in vec3 in_pos;

in vec3 in_normal;
out vec4 color;

out vec3 lightDir;
out vec3 eyeVec;
out vec3 out_normal;

uniform mat4 v,m,p;

out vec4 frag_color;

void main(void)
{
  color = vec4(in_normal, 0.0);
  // color =in_pos;
  // calcul de la position du point une fois toutes les transformations appliquées

  gl_Position = p * v * m * vec4( in_pos, 1.0 );

  vec4 vVertex = v*m * vec4(in_pos, 1.0);
  eyeVec = -vVertex.xyz;

  vec4 LightSource_position=vec4(0.0,0.0,10.0,0.0);
  lightDir=vec3(LightSource_position.xyz - vVertex.xyz);

  out_normal = in_normal;
  
  vec3 L = normalize(lightDir);
  vec3 N = normalize(out_normal);

  float intensity = max(dot(L,N),0.0);
  frag_color = vec4(intensity,intensity,intensity, 1.0);
}
