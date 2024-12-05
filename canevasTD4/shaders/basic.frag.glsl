#version 150 core

// couleur émise pour le pixel
out vec4 frag_color;

// Coordonnées interpolées depuis le vertex shader
in vec3 frag_pos;

void main(void)
{
  // Taille d'une cellule du quadrillage
  float cell_size = 0.1;

  // Calculer la position en cellules (en divisant par la taille)
  int x_cell = int(floor(frag_pos.x / cell_size));
  int y_cell = int(floor(frag_pos.y / cell_size));

  // Calculer si la cellule est paire ou impaire
  bool is_even = (x_cell + y_cell) % 2 == 0;

  // Couleur rouge si pair, noir si impair
  vec3 color = is_even ? vec3(1.0, 0.0, 0.0) : vec3(0.0, 0.0, 0.0);

  frag_color = vec4( color, 1.0 );
}
