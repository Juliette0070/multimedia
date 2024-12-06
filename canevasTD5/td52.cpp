// #include <GL/glew.h>
// #include <GL/freeglut.h>
// #include <glm/glm.hpp>
// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>
// #include <iostream>
// #include <fstream>
// #include <sstream>
// #include <string>

// #define NBMESHES 4

// // Structure pour stocker les informations des shaders
// struct shaderProg {
//     unsigned int progid; // ID du shader
//     unsigned int mid;    // ID de la matrice de modelisation passée en uniform
//     unsigned int vid;
//     unsigned int pid;
//     unsigned int LightID;
// }shaders[NBMESHES];

// // Structure pour stocker les informations des maillages
// struct maillage {
//     shaderProg shader;
//     unsigned int vaoids; // VaoID contenant les VBO des données du maillage
//     unsigned int nbtriangles;
//     float angle = 0.0f;
//     float scale = 0.0f; // pour la normalisation de la taille
//     float inc = 0.1f;
//     float x, y, z; // position du centre du maillage
// }maillages[NBMESHES];

// // Variables globales pour la vue et la position de la caméra
// glm::mat4 view, model;
// float eye[3] = {0.0f, 0.0f, 5.0f};






// // Fonction pour lire le code d'un fichier shader
// std::string readShaderFile(const char* filename) {
//     std::ifstream file(filename);
//     std::stringstream buffer;
//     buffer << file.rdbuf();
//     return buffer.str();
// }

// // Fonction pour initialiser les shaders
// unsigned int initShaders(const char* vertShaderFile, const char* fragShaderFile) {
//     std::string vertexShaderCode = readShaderFile(vertShaderFile);
//     std::string fragmentShaderCode = readShaderFile(fragShaderFile);

//     const char* vertexShaderSource = vertexShaderCode.c_str();
//     const char* fragmentShaderSource = fragmentShaderCode.c_str();

//     // Compilation du shader de vertex
//     unsigned int vertShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertShader, 1, &vertexShaderSource, NULL);
//     glCompileShader(vertShader);

//     // Vérification de la compilation du shader de vertex
//     int success;
//     glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         char infoLog[512];
//         glGetShaderInfoLog(vertShader, 512, NULL, infoLog);
//         std::cout << "Erreur de compilation du shader de vertex: " << infoLog << std::endl;
//     }

//     // Compilation du shader de fragment
//     unsigned int fragShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragShader, 1, &fragmentShaderSource, NULL);
//     glCompileShader(fragShader);

//     // Vérification de la compilation du shader de fragment
//     glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         char infoLog[512];
//         glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
//         std::cout << "Erreur de compilation du shader de fragment: " << infoLog << std::endl;
//     }

//     // Création du programme shader
//     unsigned int shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertShader);
//     glAttachShader(shaderProgram, fragShader);
//     glLinkProgram(shaderProgram);

//     // Vérification de la liaison du programme shader
//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     if (!success) {
//         char infoLog[512];
//         glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//         std::cout << "Erreur de liaison du programme shader: " << infoLog << std::endl;
//     }

//     // Nettoyage des shaders après leur utilisation
//     glDeleteShader(vertShader);
//     glDeleteShader(fragShader);

//     return shaderProgram;
// }






// // Fonction pour initialiser un VAO pour un maillage donné
// unsigned int initVAOs(shaderProg shader, const char* meshFile) {
//     unsigned int vao;
//     glGenVertexArrays(1, &vao);
//     glBindVertexArray(vao);

//     // Charger les données du maillage depuis le fichier .off (positions, normales, etc.)
//     // Ici, il faut parser le fichier .off et charger les données dans des VBOs
//     // Cette partie dépend du format du fichier .off et de la façon dont vous gérez les données

//     // Exemple de données : positions, normales, indices
//     // Vous devez remplir les VBO pour ces données, puis les lier au VAO

//     glBindVertexArray(0);
//     return vao;
// }






// void displayMesh(maillage currentMesh, glm::mat4 model) {
//     glUseProgram(currentMesh.shader.progid);

//     // Envoi de la matrice modèle au shader
//     glUniformMatrix4fv(currentMesh.shader.mid, 1, GL_FALSE, glm::value_ptr(model));

//     // Envoi de la lumière au shader
//     glUniform3fv(currentMesh.shader.LightID, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));

//     // Lier le VAO du maillage
//     glBindVertexArray(currentMesh.vaoids);

//     // Dessiner le maillage
//     glDrawElements(GL_TRIANGLES, currentMesh.nbtriangles * 3, GL_UNSIGNED_INT, (void*)0);

//     glBindVertexArray(0);
// }






// void display() {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//     // Calcul de la vue de la caméra
//     view = glm::lookAt(glm::vec3(eye[0], eye[1], eye[2]),
//                        glm::vec3(eye[0], eye[1], eye[2] - 1.0f),
//                        glm::vec3(0.0f, 1.0f, 0.0f));

//     float decal = 1.25f;

//     // Affichage du premier maillage
//     model = glm::mat4(1.0f);
//     model = glm::translate(model, glm::vec3(-decal, -decal, 0.0f));
//     displayMesh(maillages[0], model);

//     // Affichage du deuxième maillage
//     model = glm::mat4(1.0f);
//     model = glm::translate(model, glm::vec3(decal, decal, 0.0f));
//     displayMesh(maillages[1], model);

//     // Affichage du troisième maillage
//     model = glm::mat4(1.0f);
//     model = glm::translate(model, glm::vec3(-decal, decal, 0.0f));
//     displayMesh(maillages[2], model);

//     // Affichage du quatrième maillage avec mise à l'échelle
//     model = glm::mat4(1.0f);
//     model = glm::translate(model, glm::vec3(decal, -decal, 0.0f));
//     model = glm::scale(model, glm::vec3(0.70f));
//     displayMesh(maillages[3], model);

//     glutSwapBuffers();
// }






// void init() {
//     glEnable(GL_DEPTH_TEST);

//     // Initialisation des shaders
//     shaders[0] = initShaders("/shaders/phong.vert.glsl", "/shaders/phong.frag.glsl");
//     shaders[1] = initShaders("/shaders/phong.vert.glsl", "/shaders/toon.frag.glsl");
//     shaders[2] = initShaders("/shaders/phong.vert.glsl", "/shaders/phongVert.frag.glsl");
//     shaders[3] = initShaders("/shaders/phong.vert.glsl", "/shaders/phongRouge.frag.glsl");

//     // Initialisation des VAOs pour chaque maillage
//     maillages[0].vaoids = initVAOs(shaders[0], "/meshes/space_shuttle2.off");
//     maillages[1].vaoids = initVAOs(shaders[1], "/meshes/space_station2.off");
//     maillages[2].vaoids = initVAOs(shaders[2], "/meshes/milleniumfalcon.off");
//     maillages[3].vaoids = initVAOs(shaders[3], "/meshes/rabbit.off");
// }






// int main(int argc, char** argv) {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//     glutInitWindowSize(800, 600);
//     glutCreateWindow("OpenGL - Affichage de plusieurs maillages");

//     glewInit();

//     init();

//     // Boucle de rendu
//     glutDisplayFunc(display);
//     glutMainLoop();
//     return 0;
// }
