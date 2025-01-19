/*
 *  cube.cpp
 *  glutMaster
 *
 *  Created by Emmanuel Melin on 19/01/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "cube.h"
#include <string.h>
 cube::cube(float t){
taille=t;

}

void cube::init()
{initShaders();
initVAOs();
}
 cube::~cube(){}


void cube::trace_cube(glm::mat4 m){
    glUseProgram( rep_progid );
    m = glm::scale(m , glm::vec3(taille,taille, taille ) );
     glUniformMatrix4fv( rep_mvpid , 1, GL_FALSE, &m[0][0]);
    glBindVertexArray( rep_vaoids[ 0 ] );
    glDrawElements(GL_LINES, 48, GL_UNSIGNED_SHORT, 0 );
}

/**
 * Fonction définissant le maillage et effectuant son envoi sur la carte graphique.
 */
void cube::initVAOs()
{
  // Identifiant du maillage.
  unsigned int vboids[ 3 ];
   float  coef=0.1;
  // Points du maillage.

    
  std::vector< float > vertices = {
      
      
      //face
           -0.5f, -0.5f,  0.5f,  //0
           -0.5f,  0.5f,  0.5f,  //1
            0.5f, -0.5f,  0.5f,  //2
            0.5f,  0.5f,  0.5f,  //3
        
         //Arriere
                -0.5f, -0.5f, -0.5f, //4
                -0.5f,  0.5f, -0.5f, //5
                 0.5f, -0.5f, -0.5f, //6
                0.5f,  0.5f,  -0.5f, //7
                
  };

  // Couleurs du maillage.
  std::vector< float > colors = {
    1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
   
    1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
   
      
   
  };

  // Indices du maillage.
  std::vector< unsigned short > indices = {

      0,1,3,2,
      0,2,1,3,
      
      
      6,7,5,4,
       6,4,7,5,
    
        2,3,7,6,
      2,6,3,7,
      
        4,5,1,0,
       4,0,5,1,
        
        3,1,5,7,
      3,7,1,5,
  
        
        0,2,6,4,
      0,4,2,6
  
  };

  // Génération d'un Vertex Array Object (VAO) contenant 3 Vertex Buffer Objects.
  glGenVertexArrays( 1, &rep_vaoids[ 0 ] );
  // Activation du VAO.
  glBindVertexArray( rep_vaoids[ 0 ] );

  // Génération de 3 VBO.
  glGenBuffers( 3, vboids );

  // VBO contenant les sommets : activation puis envoi.
  glBindBuffer( GL_ARRAY_BUFFER, vboids[ 0 ] );
  glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( float ), vertices.data(), GL_STATIC_DRAW );

  // L'attribut in_pos du vertex shader est associé aux données de ce VBO.
  auto pos = glGetAttribLocation( rep_progid, "in_pos" );
  glVertexAttribPointer( pos, 3, GL_FLOAT, GL_FALSE, 0, 0 );
  glEnableVertexAttribArray( pos );

  // VBO contenant les couleurs.
  glBindBuffer( GL_ARRAY_BUFFER, vboids[ 1 ] );
  glBufferData( GL_ARRAY_BUFFER, colors.size() * sizeof( float ), colors.data(), GL_STATIC_DRAW );

  // L'attribut in_color du vertex shader est associé aux données de ce VBO.
  auto color = glGetAttribLocation( rep_progid, "in_color" );
  glVertexAttribPointer( color, 3, GL_FLOAT, GL_FALSE, 0, 0 );
  glEnableVertexAttribArray( color );

  // VBO contenant les indices.
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vboids[ 2 ] );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( unsigned short ), indices.data(), GL_STATIC_DRAW );

  // Désactivation du VAO.
  glBindVertexArray( 0 );
}


/**
 * Initialisation des vertex et fragment shaders.
 */
void cube::initShaders()
{
  // Identifiants des vertex et fragment shaders.
  unsigned int vsid, fsid;

  // Programme du vertex shader : transformation du point 3D par la matrice MVP.
  std::string vs(
         "#version 150 core\n"                                    \
         "in vec3 in_pos;\n"                            \
         "in vec3 in_color;\n"                          \
         "uniform mat4 mvp;\n"                          \
         "out vec3 color;\n"                            \
         "void main(void)\n"                            \
         "{\n"                                          \
         "  gl_Position = mvp * vec4( in_pos, 1.0 );\n" \
         "  color = in_color;\n"                        \
         "}\n"
  );
  // Programme du fragment shader : chaque point prend la couleur qui lui est associée.
  std::string fs(
         "#version 150 core\n"                       \
         "in vec3 color;\n"                     \
         "out vec4 frag_color;\n"               \
         "void main(void)\n"                    \
         "{\n"                                  \
         "  frag_color = vec4( color, 1.0 );\n" \
         "}\n"
  );

  // Création et compilation du vertex shader.
  vsid = glCreateShader( GL_VERTEX_SHADER );
  char const * vs_char = vs.c_str();
  glShaderSource( vsid, 1, &vs_char, nullptr );
  glCompileShader( vsid );

  // Idem pour le fragment shader.
  fsid = glCreateShader( GL_FRAGMENT_SHADER );
  char const * fs_char = fs.c_str();
  glShaderSource( fsid, 1, &fs_char, nullptr );
  glCompileShader( fsid );

  // Création du programme (vertex + fragment shader)
  rep_progid = glCreateProgram();

  glAttachShader( rep_progid, vsid );
  glAttachShader( rep_progid, fsid );

  glLinkProgram( rep_progid );


  // Récupération de l'identifiant de la matrice MVP dans le shader.
  rep_mvpid = glGetUniformLocation( rep_progid, "mvp" );
}
