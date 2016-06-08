#include "graphics.h"
#include <fstream> 
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

Graphics::Graphics ( GLint const &width, GLint const &height, std::string name ) : mWidth { width }, mHeight { height } {
   mWindowName = name;
}
GLuint Graphics::loadInShader ( char const *fname, GLenum const &shaderType ) const {
   std::vector<char> buffer;
   std::ifstream in;
   in.open ( fname, std::ios::binary );

   if ( in.is_open ( ) ) {
      in.seekg ( 0, std::ios::end );
      size_t const &length = in.tellg ( );

      in.seekg ( 0, std::ios::beg );

      buffer.resize ( length + 1 );
      in.read ( &buffer[0], length );
      in.close ( );
      buffer[length] = '\0';
   } else {
      std::cerr << "Unable to open " << fname << std::endl;
      exit ( -1 );
   }

   GLchar const *src = &buffer[0];

   GLuint shader = glCreateShader ( shaderType );
   glShaderSource ( shader, 1, &src, NULL );
   glCompileShader ( shader );
   GLint test;
   glGetShaderiv ( shader, GL_COMPILE_STATUS, &test );

   if ( !test ) {
      std::cerr << "Shader compilation failed with this message:" << std::endl;
      std::vector<char> compilationLog ( 512 );
      glGetShaderInfoLog ( shader, compilationLog.size ( ), NULL, &compilationLog[0] );
      std::cerr << &compilationLog[0] << std::endl;
      glfwTerminate ( );
      exit ( -1 );
   }
}

void Graphics::initializeWindow () {
   if ( !glfwInit ( ) ) {
      std::cerr<<"failed to initialize glfw"<<std::endl;
      exit ( EXIT_FAILURE );
   }

   glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
   glfwWindowHint ( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
   glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 3 );
   glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 2 );

   mWindow = glfwCreateWindow ( mWidth, mHeight, mWindowName.c_str (), NULL, NULL );
   if ( !mWindow ) {
      std::cerr<<"failed to initialize mWindow"<<std::endl;
      exit ( EXIT_FAILURE );
   }

   glfwMakeContextCurrent ( mWindow );

   glewExperimental = GL_TRUE;
   if ( glewInit ( ) != 0 ) {
      std::cerr<<"failed to initialize glew"<<std::endl;
      exit ( EXIT_FAILURE );
   }

   glGenVertexArrays ( 1, &mVao );
   glGenBuffers ( 1, &mVbo );
}

void Graphics::initializeShaders ( std::string const &vertFile, std::string const &fragFile, std::string const &geoFile ) {
   int positionIndex { 0 };
   glVertexAttribPointer ( positionIndex, 3, GL_FLOAT, GL_FALSE, 0, 0 );
   glEnableVertexAttribArray ( positionIndex );

   GLuint vertShader { loadInShader ( vertFile.c_str (), GL_VERTEX_SHADER ) };
   GLuint fragShader { loadInShader ( fragFile.c_str (), GL_FRAGMENT_SHADER ) };
//   GLuint geoShader { loadInShader ( geoFIle.c_str (), GL_GEOMETRY_SHADER ) };
   mShaderProgram = glCreateProgram ();
   glAttachShader ( mShaderProgram, vertShader );
   glAttachShader ( mShaderProgram, fragShader );
   glBindAttribLocation ( mShaderProgram, positionIndex, "position" );
   glLinkProgram ( mShaderProgram );
   glUseProgram ( mShaderProgram );
}

void Graphics::updateVbo ( std::vector<GLfloat> const &newVerts ) {
   glBufferData ( GL_ARRAY_BUFFER, sizeof ( newVerts ), newVerts.data (), GL_DYNAMIC_DRAW );
}

void Graphics::draw ( GLint const &arrayIndex ) const {
   glBindVertexArray ( mVao );
   glBindBuffer ( GL_ARRAY_BUFFER, mVbo );

   while ( true ) {
      glClear ( GL_COLOR_BUFFER_BIT );
      glDrawArrays ( GL_TRIANGLES, 0, arrayIndex );
      glfwSwapBuffers ( mWindow );
      glfwPollEvents ( );
   }
}
   

int main () {
   std::vector<GLfloat> verts {
     1.0f, 1.0f, 1.0f,
     0.0f, 1.0f, 1.0f, 
     1.0f, 0.0f, 1.0f, 
     0.0f, 0.0f, 0.0f,
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f
   };

   std::string windowName { "my window" };
   std::string vertFile { "./Shaders/vertex.glsl" };
   std::string fragFile { "./Shaders/fragment.glsl" };
   std::string geoFile { "./Shaders/geometry.glsl" };

   Graphics g ( 700, 700, windowName );
   g.initializeWindow ();
   g.initializeShaders ( vertFile, fragFile, geoFile );
   g.updateVbo ( verts );
   g.draw ( 6 );
}

