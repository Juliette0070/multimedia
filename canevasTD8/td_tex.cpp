#include <iostream>
#include <vector>
#include <array>
#include <fstream>

#if defined(__APPLE__)
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include <GLUT/glut.h>

#else
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#endif


#include "config.h"

#define ENABLE_SHADERS

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <opencv4/opencv2/opencv.hpp>

#include "cube.h"

unsigned int progid;
unsigned int mvpid;

glm::mat4 view;
glm::mat4 proj;
glm::mat4 mvp;

float angle = 0.0f;
float inc = 0.1f;

unsigned int vaoids[ 1 ];

unsigned int size;
cube uncube(1.01);


void display()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  // L'origine du repère est déplacée à -5 suivant l'axe z.
  view = glm::translate( glm::mat4( 1.0f ) , glm::vec3( 0.0f, 0.0f, -5.0f ) );
  // Le repère subit une rotation suivant l'axe z.
  view = glm::rotate( view, glm::degrees( angle ), glm::vec3( 0.0f, 1.0f, 1.0f ) );
    view = glm::rotate( view, glm::degrees( angle/3 ), glm::vec3( 1.0f, 0.0f, 0.0f ) );
  //

  // Calcul de la matrice mvp.
  mvp = proj * view;
    glBindVertexArray( vaoids[ 0 ] );
      glUseProgram( progid );
  // Passage de la matrice mvp au shader.
  glUniformMatrix4fv( mvpid , 1, GL_FALSE, &mvp[0][0]);

  // Dessin des triangles...

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawElements( GL_TRIANGLES,size, GL_UNSIGNED_SHORT, 0 );
    
    
    uncube.trace_cube(proj*  view);
  
  glutSwapBuffers();
}


void idle()
{
  angle += 0.001f;
  if( angle >= 360.0f )
  {
    angle = 0.0f;
  }
  
  glutPostRedisplay();
}


void reshape( int w, int h )
{
  glViewport(0, 0, w, h);
  // Modification de la matrice de projection à chaque redimensionnement de la fenêtre.
  proj = glm::perspective( 45.0f, w/static_cast< float >( h ), 0.1f, 100.0f );
}


void initVAOs()
{
  unsigned int vboids[ 4 ];
  
  std::vector< float > verticesCarreSimple = {
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

    

  std::vector< float > verticesCarreDoublons = {
      -0.5,-0.5,0.5,  // pointinital: 0   nouveau point: 0
      0.5,-0.5,0.5,  // pointinital: 2   nouveau point: 1
      -0.5,0.5,0.5,  // pointinital: 1   nouveau point: 2
      0.5,0.5,0.5,  // pointinital: 3   nouveau point: 3
      0.5,-0.5,-0.5,  // pointinital: 6   nouveau point: 4
      -0.5,-0.5,-0.5,  // pointinital: 4   nouveau point: 5
      0.5,0.5,-0.5,  // pointinital: 7   nouveau point: 6
      -0.5,0.5,-0.5,  // pointinital: 5   nouveau point: 7
      0.5,-0.5,0.5,  // pointinital: 2   nouveau point: 8
      0.5,-0.5,-0.5,  // pointinital: 6   nouveau point: 9
      0.5,0.5,0.5,  // pointinital: 3   nouveau point: 10
      
  };
    
    
     std::vector< float > colors = {
         1.0f,0.0f,0.0,
         1.0f,0.0f,0.0,  //Point initial 2 en rouge
         1.0f,0.0f,0.0,
         1.0f,0.0f,0.0,
 
         0.0f,1.0f,0.0,
         0.0f,1.0f,0.0,
         0.0f,1.0f,0.0,
         0.0f,1.0f,0.0,

         
         0.0f,0.0f,1.0, //Point initial 2 en bleu
         0.0f,0.0f,1.0,
         0.0f,0.0f,1.0,
         0.0f,0.0f,1.0,


         0.0f,1.0f,1.0,
         0.0f,1.0f,1.0,
         0.0f,1.0f,1.0,
         0.0f,1.0f,1.0,

         
         1.0f,0.0f,1.0,
         1.0f,0.0f,1.0,
         1.0f,0.0f,1.0,
         1.0f,0.0f,1.0,


         1.0f,1.0f,0.0,
         1.0f,1.0f,0.0,
         1.0f,1.0f,0.0,
         1.0f,1.0f,0.0


     };
    
  
    
    std::vector< float > texcoords = {
        0.0f, 0.f,
        0.0f, 1.f,
        1.0f, 0.0f,
        1.f, 1.f,
        
        0.0f, 0.f,
        0.0f, 1.f,
        1.0f, 0.0f,
        1.f, 1.f,
        
        0.0f, 0.f,
        0.0f, 1.f,
        1.0f, 0.0f,
        1.f, 1.f,
        
   // ajouter les coordonnées de texture pour les 3 faces manquantes
     };

  
    std::vector< unsigned short > indices = {0,1,2,1,2,3,4,5,6,5,6,7,8,9,10,};
    size=indices.size();

     
  // Génération d'un Vertex Array Object contenant 3 Vertex Buffer Objects.
  glGenVertexArrays( 1, &vaoids[ 0 ] );
  glBindVertexArray( vaoids[ 0 ] );

  // Génération de 3 VBO.
  glGenBuffers( 4, vboids );

  // VBO contenant les sommets.
  
  glBindBuffer( GL_ARRAY_BUFFER, vboids[ 0 ] );
 glBufferData( GL_ARRAY_BUFFER, verticesCarreDoublons.size() * sizeof( float ), verticesCarreDoublons.data(), GL_STATIC_DRAW );
    
 //   glBufferData( GL_ARRAY_BUFFER, vertices.size() * sizeof( float ), vertices.data(), GL_STATIC_DRAW );

  // L'attribut in_pos du vertex shader est associé aux données de ce VBO.
  auto pos = glGetAttribLocation( progid, "in_pos" );
  glVertexAttribPointer( pos, 3, GL_FLOAT, GL_FALSE, 0, 0 );
  glEnableVertexAttribArray( pos );
  
  // VBO contenant les coordonnées de texture.
  
  glBindBuffer( GL_ARRAY_BUFFER, vboids[ 1 ] );
  glBufferData( GL_ARRAY_BUFFER, texcoords.size() * sizeof( float ),
               texcoords.data(), GL_STATIC_DRAW );

  auto coord = glGetAttribLocation( progid, "in_coord" );
  glVertexAttribPointer( coord, 2, GL_FLOAT, GL_FALSE, 0, 0 );
  glEnableVertexAttribArray( coord );

  
  glBindBuffer( GL_ARRAY_BUFFER, vboids[ 3 ] );
  glBufferData( GL_ARRAY_BUFFER, colors.size() * sizeof( float ), colors.data(), GL_STATIC_DRAW );

       // L'attribut in_pos du vertex shader est associé aux données de ce VBO.
       auto col = glGetAttribLocation( progid, "in_col" );
       glVertexAttribPointer( col, 3, GL_FLOAT, GL_FALSE, 0, 0 );
       glEnableVertexAttribArray( col );
    
    // VBO contenant les indices.
  
  glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, vboids[ 2 ] );
  glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( unsigned short ), indices.data(), GL_STATIC_DRAW );

//   glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof( unsigned short ), indices.data(), GL_STATIC_DRAW );

     
    
    
    
  glBindVertexArray( 0 );
}



void initShaders()
{
    unsigned int vsid, fsid;
    int status;
    int logsize;
    std::string log;

    
    
    
    std::ifstream vs_ifs( MY_SHADER_PATH+ (std::string )"/shaders/basic.vert.glsl" );
   std::ifstream fs_ifs(  MY_SHADER_PATH+ (std::string )"/shaders/basic.frag.glsl" );


    auto begin = vs_ifs.tellg();
    vs_ifs.seekg( 0, std::ios::end );
    auto end = vs_ifs.tellg();
    vs_ifs.seekg( 0, std::ios::beg );
    auto size = end - begin;

    std::string vs;
    vs.resize( size );
    vs_ifs.read( &vs[ 0 ], size );

    begin = fs_ifs.tellg();
    fs_ifs.seekg( 0, std::ios::end );
    end = fs_ifs.tellg();
    fs_ifs.seekg( 0, std::ios::beg );
    size = end - begin;

    std::string fs;
    fs.resize( size );
    fs_ifs.read( &fs[0], size );

    vsid = glCreateShader( GL_VERTEX_SHADER );
    char const * vs_char = vs.c_str();
    glShaderSource( vsid, 1, &vs_char, nullptr );
    glCompileShader( vsid );

    // Get shader compilation status.
    glGetShaderiv( vsid, GL_COMPILE_STATUS, &status );

    if( !status )
    {
        std::cerr << "Error: vertex shader compilation failed.\n";
        glGetShaderiv( vsid, GL_INFO_LOG_LENGTH, &logsize );
        log.resize( logsize );
        glGetShaderInfoLog( vsid, log.size(), &logsize, &log[0] );
        std::cerr << log << std::endl;
    }

    fsid = glCreateShader( GL_FRAGMENT_SHADER );
    char const * fs_char = fs.c_str();
    glShaderSource( fsid, 1, &fs_char, nullptr );
    glCompileShader( fsid );

    // Get shader compilation status.
    glGetShaderiv( fsid, GL_COMPILE_STATUS, &status );

    if( !status )
    {
        std::cerr << "Error: fragment shader compilation failed.\n";
        glGetShaderiv( fsid, GL_INFO_LOG_LENGTH, &logsize );
        log.resize( logsize );
        glGetShaderInfoLog( fsid, log.size(), &logsize, &log[0] );
        std::cerr << log << std::endl;
    }

    progid = glCreateProgram();

    glAttachShader( progid, vsid );
    glAttachShader( progid, fsid );

    glLinkProgram( progid );

    glUseProgram( progid );

    mvpid = glGetUniformLocation( progid, "mvp" );
    
}


void initTextures()
{
  
    
  cv::Mat img = cv::imread(  MY_RES_PATH+ (std::string )"/res/images/logoIUT.png", cv::IMREAD_UNCHANGED );
 
  unsigned int texture[1];

  glGenTextures( 1, texture );
  glActiveTexture( GL_TEXTURE0  );
  glBindTexture( GL_TEXTURE_2D, texture[0] );
  unsigned int tex = glGetUniformLocation(progid, "tex");
  glUniform1i(tex, 0);
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.rows, img.cols, 0, GL_BGRA,GL_UNSIGNED_BYTE,img.data);
        
   
}


int main( int argc, char * argv[] )
{
    glutInit( &argc, argv );
#if defined(__APPLE__) && defined(ENABLE_SHADERS)
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA|GLUT_3_2_CORE_PROFILE);
#else

glutInitContextVersion( 3, 2 );
//glutInitContextVersion( 4, 5 );
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glewInit();
#endif

    glutInitWindowSize( 640, 480 );


    glutCreateWindow( argv[ 0 ]  );

    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutIdleFunc( idle );
    

    // Initialisation de la bibliothèque GLEW.
#if not defined(__APPLE__)
    glewInit();
#endif
 glEnable(GL_DEPTH_TEST);
    

    initShaders();
    initVAOs();
initTextures();
    uncube.init();
    
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glutMainLoop();

    return 0;
}
