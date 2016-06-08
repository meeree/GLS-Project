#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifndef iostream
#include <iostream>
#endif

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include "/home/jhazelden/Cpp-stuff/openGL/openShader.cpp"

static struct {
   GLuint shaderProgram;
   GLfloat zoomScalar;
   GLfloat xpos, ypos;
   GLint height, width;
   glm::mat4 projection, view, model;
} attrs;

void key_callback ( GLFWwindow* window, int key, int scancode, int action, int mods ) {
}

int main ( ) {
   if ( !glfwInit ( ) ) {
      std::cout<<"failed to initialize glfw"<<std::endl;
      exit ( 0 );
   }

   glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
   glfwWindowHint ( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
   glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 3 );
   glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 2 );

   attrs.width = 975;
   attrs.height = 525;
   auto window = glfwCreateWindow ( attrs.width, attrs.height, "my window", NULL, NULL );
   if ( !window ) {
      std::cout<<"failed to initialize window"<<std::endl;
   }

   glfwMakeContextCurrent ( window );
   glfwSetKeyCallback ( window, key_callback );

   glewExperimental = GL_TRUE;
   if ( glewInit ( ) != 0 ) {
      std::cout<<"failed to initialize glew"<<std::endl;
      exit ( 0 );
   }

   GLfloat verts[2*6] = {
     2.0f, 2.0f,
     -2.0f, 2.0f,
     2.0f, -2.0f,
     -2.0f, -2.0f,
     2.0f, -2.0f,
     -2.0f, 2.0f
   };


   GLfloat pallette[4*16] = {
//      0.258, 0.117, 0.059, 0,
      0.0, 0.0, 0.0, 0,
      0.098, 0.027, 0.102, 0,
      0.035, 0.004, 0.184, 0,
      0.016, 0.016, 0.285, 0,
      0,    0.027, 0.391, 0,
      0.047, 0.172, 0.539, 0,
      0.094, 0.320, 0.691, 0,
      0.223, 0.488, 0.816, 0,
      0.523, 0.707, 0.895, 0,
      0.824, 0.922, 0.969, 0,
      0.941, 0.910, 0.746, 0,
      0.969, 0.785, 0.371, 0,
      0.996, 0.664, 0,    0,
      0.797, 0.5,   0,    0,
      0.598, 0.340, 0,    0,
      0.414, 0.203, 0.012, 0
   };

   GLuint vbo, vao, texture;

   double xpos, ypos;

   glGenTextures ( 1, &texture );  
   glBindTexture ( GL_TEXTURE_1D, texture );  
   glTexImage1D ( GL_TEXTURE_1D, 0, GL_RGB, 4*16, 0, GL_RGBA, GL_FLOAT, pallette );
   glTexParameteri ( GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
   glTexParameteri ( GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );

   glGenVertexArrays ( 1, &vao );
   glBindVertexArray ( vao );

   glGenBuffers ( 1, &vbo );
   glBindBuffer ( GL_ARRAY_BUFFER, vbo );
   glBufferData ( GL_ARRAY_BUFFER, sizeof ( verts ), verts, GL_DYNAMIC_DRAW );
   glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );

   glVertexAttribPointer ( 0, 2, GL_FLOAT, GL_FALSE, 0, 0 );
   glEnableVertexAttribArray ( 0 );

   auto vertShader = loadInShader ( "/home/jhazelden/Cpp-stuff/openGL/shaderPractice/shaders/vert.shader", GL_VERTEX_SHADER );
   auto fragShader = loadInShader ( "/home/jhazelden/Cpp-stuff/openGL/shaderPractice/shaders/frag.shader", GL_FRAGMENT_SHADER );
   attrs.shaderProgram = glCreateProgram ( );

   glAttachShader ( attrs.shaderProgram, vertShader );
   glAttachShader ( attrs.shaderProgram, fragShader );
   glBindAttribLocation ( attrs.shaderProgram, 0, "inPosition" );
   glLinkProgram ( attrs.shaderProgram );
   glUseProgram ( attrs.shaderProgram );

   auto iter = glGetUniformLocation ( attrs.shaderProgram, "iter" );
   auto zoom = glGetUniformLocation ( attrs.shaderProgram, "zoom" );
//   auto power = glGetUniformLocation ( attrs.shaderProgram, "power" );
   auto xPos = glGetUniformLocation ( attrs.shaderProgram, "xPos" );
   auto yPos = glGetUniformLocation ( attrs.shaderProgram, "yPos" );
   auto projection = glGetUniformLocation ( attrs.shaderProgram, "projection" );
   auto view = glGetUniformLocation ( attrs.shaderProgram, "view" );
   auto model = glGetUniformLocation ( attrs.shaderProgram, "model" );

   glBindVertexArray ( vao );
   glBindBuffer ( GL_ARRAY_BUFFER, vbo );
   glBindTexture ( GL_TEXTURE_1D, texture );

   attrs.zoomScalar = 2;   
   attrs.xpos = 0.75;   
   attrs.ypos = 0;   
   attrs.projection = glm::perspective ( glm::radians ( 45.0f ), ( GLfloat )attrs.width/attrs.height, 0.1f, 3.0f );
   attrs.view = glm::lookAt ( glm::vec3 ( 0, 0, -2 ), glm::vec3 ( 0, 0, 0 ), glm::vec3 ( 0, 1, 0 ) );
   attrs.model = glm::mat4 ( 1.0f );

   glEnable ( GL_MULTISAMPLE );

   glUniform1f ( zoom, attrs.zoomScalar );

   glUniformMatrix4fv ( projection, 1, GL_FALSE, glm::value_ptr ( attrs.projection ) );
   glUniformMatrix4fv ( view, 1, GL_FALSE, glm::value_ptr ( attrs.view ) );
   glUniformMatrix4fv ( model, 1, GL_FALSE, glm::value_ptr ( attrs.model ) );

   GLint itMax = 0;
   glUniform1i ( iter, 500 );

   while ( true ) {
//      attrs.model *= glm::rotate ( glm::radians ( 1.0f ), glm::vec3 ( 0.0f, 1.0f, 0.0f ) );
      glUniformMatrix4fv ( model, 1, GL_FALSE, glm::value_ptr ( attrs.model ) );
      glUniform1i ( iter, itMax );
      glUniform1f ( zoom, attrs.zoomScalar );
      glUniform1f ( xPos, attrs.xpos );
      glUniform1f ( yPos, attrs.ypos );

      glBindBuffer ( GL_ARRAY_BUFFER, vbo );
      glClear ( GL_COLOR_BUFFER_BIT );
      glDrawArrays ( GL_TRIANGLES, 0, 6 );
      glfwPollEvents ( );

      glfwSwapBuffers ( window );
      itMax++;
   }
   glfwTerminate ( );
}

