#version 150 core
// version du langage GLSL utilisée, ici 1.5

// mvp est la variable contenant la matrice proj*view*model
// uniform indique que c'est la même matrice pour tous les points
uniform mat4 mvp;

// in indique que la variable est fournie en entrée pour chaque point
// chaque point possède une position 3D
in vec3 in_pos;

out vec3 color;

out vec3 frag_pos;

void main(void)
{
  // définir la scale à 2.0
  float scale = 2.0;

  // Ajouter un décalage pour les points avec x > 0
  vec3 offset = (in_pos.x > 0.0) ? vec3(1.0, 0.0, 0.0) : vec3(0.0, 0.0, 0.0);

  // calcul de la position du point une fois toutes les transformations appliquées
  gl_Position = mvp * vec4( in_pos * scale + offset, 1.0 );

  frag_pos = in_pos;
}
