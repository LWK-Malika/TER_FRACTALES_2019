#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <cmath>

// Inclure les entêtes standard
#include <stdio.h> 
#include <stdlib.h>
// Inclure GLEW. Toujours l'inclure avant gl.h et glfw.h, car c'est un peu magique. 
//include <GL/glew.h>
// Inclure GLFW 
//include <GL/glfw3.h>
// Inclure GLM 
//#include <glm/glm.hpp> 
using namespace glm;
//using namespace std;




int main()
{
  // Initialise GLFW 
  if( !glfwInit() ) 
    { 
      fprintf( stderr, "Failed to initialize GLFW\n" ); 
      return -1; 
    }

  glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // antialiasing 4x 
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3); // Nous voulons OpenGL 3.3 
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3); 
  glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Nous ne voulons pas de support de l'ancien OpenGL
 
  // Ouvre une fenêtre et crée son contexte OpenGL
  GLFWwindow* window; // (Dans le code joint, cette variable est globale) 
  window = glfwCreateWindow( 1024, 768, "Tutorial 01", NULL, NULL); 
  if( window == NULL ){ 
    fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" ); 
    glfwTerminate(); 
    return -1; 
  } 
  glfwMakeContextCurrent(window); 
 
  // Initialise GLEW 
  glewExperimental=true; // Nécessaire pour le profil core
  if (glewInit() != GLEW_OK) { 
    fprintf(stderr, "Failed to initialize GLEW\n"); 
    return -1; 
  }
  
  return 0;
}
