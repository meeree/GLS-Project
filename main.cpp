#include "./ConfigReader/Tree/tree.h"
#include "./ConfigReader/Node/node.h"
#include "./ConfigReader/Token/token.h"
#include "./ConfigReader/Tokenizer/tokenizer.h"
#include "./ConfigReader/Value/value.h"
#include "./ConfigReader/Parser/parser.h"
#include "./L-System/lSystem.h"
#include "./Graphics/Turtle/turtle.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include "/home/jhazelden/Cpp-stuff/openGL/openShader.cpp"

static struct {
   GLuint shaderProgram;
   GLint height, width;
   glm::mat4 projection, view, model;
} attrs;

int main () {
   std::ifstream fl;
   fl.open ( "/home/jhazelden/GLS-Project/fl.txt" );
   Tokenizer t;
   t.tokenizeFile ( fl );

   Parser p { t.getTokenString () };
   p.mainParse ();

   std::vector<Symbol> axiom { p.getAxiom () };
   std::map<SymbolWithoutParams, Tree*, TreeTableCompare> treeTable { p.getTreeTable () };
   std::vector<SymbolWithoutParams> constants { p.getConstants () }; 
   LSystem l { axiom, treeTable, constants };

   for ( int i = 0; i < 3; ++i ) {
      l.update (); 
   }

   Turtle turt ( {0,0,0}, {0,1,0} );
   std::vector<GLfloat> verts { 0, 0, 0};

   for ( auto const &sym: l.getString () ) {
      std::string name { sym.getName () };
      sym.print ();
      std::cout<<std::endl;
      if ( name == "Branch" ) {
         turt.move ( sym.getParam ( "length" ) );
      } else if ( name == "RotX" ) {
         turt.rotateX ( sym.getParam ( "theta" ) ); 
      } else if ( name == "RotY" ) {
         turt.rotateY ( sym.getParam ( "theta" ) );
      } else if ( name == "RotZ" ) {
         turt.rotateZ ( sym.getParam ( "theta" ) );
      } else if ( name == "StartBrack" ) {
         turt.push ();
      } else if ( name == "EndBrack" ) {
         turt.pop ();
      } else {
         continue;
      }

      std::vector<double> curPos { turt.getPos () };
      verts.push_back ( (GLfloat)curPos.at ( 0 ) );
      verts.push_back ( (GLfloat)curPos.at ( 1 ) );
      verts.push_back ( (GLfloat)curPos.at ( 2 ) );
      verts.push_back ( (GLfloat)curPos.at ( 0 ) );
      verts.push_back ( (GLfloat)curPos.at ( 1 ) );
      verts.push_back ( (GLfloat)curPos.at ( 2 ) );
   }


   if ( !glfwInit ( ) ) {
      std::cerr<<"failed to initialize glfw"<<std::endl;
      exit ( EXIT_FAILURE );
   }

   glfwWindowHint ( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
   glfwWindowHint ( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
   glfwWindowHint ( GLFW_CONTEXT_VERSION_MAJOR, 3 );
   glfwWindowHint ( GLFW_CONTEXT_VERSION_MINOR, 2 );

   attrs.width = 1300;
   attrs.height = 1300;
   auto window = glfwCreateWindow ( attrs.width, attrs.height, "my window", NULL, NULL );
   if ( !window ) {
      std::cerr<<"failed to initialize window"<<std::endl;
      exit ( EXIT_FAILURE );
   }

   glfwMakeContextCurrent ( window );

   glewExperimental = GL_TRUE;
   if ( glewInit ( ) != 0 ) {
      std::cerr<<"failed to initialize glew"<<std::endl;
      exit ( EXIT_FAILURE );
   }

   GLuint vbo, vao, texture;

   glGenVertexArrays ( 1, &vao );
   glBindVertexArray ( vao );

   glGenBuffers ( 1, &vbo );
   glBindBuffer ( GL_ARRAY_BUFFER, vbo );
   glBufferData ( GL_ARRAY_BUFFER, verts.size() * sizeof ( GLfloat ) , verts.data (), GL_DYNAMIC_DRAW );
   glClearColor ( 0.0f, 0.0f, 0.0f, 1.0f );

   int posIndex { 0 };
   glVertexAttribPointer ( posIndex, 3, GL_FLOAT, GL_FALSE, 0, 0 );
   glEnableVertexAttribArray ( posIndex );

   auto vertShader = loadInShader ( "/home/jhazelden/GLS-Project/Graphics/Shaders/vertex.glsl", GL_VERTEX_SHADER );
   auto fragShader = loadInShader ( "/home/jhazelden/GLS-Project/Graphics/Shaders/fragment.glsl", GL_FRAGMENT_SHADER );
   attrs.shaderProgram = glCreateProgram ( );

   glAttachShader ( attrs.shaderProgram, vertShader );
   glAttachShader ( attrs.shaderProgram, fragShader );
   glBindAttribLocation ( attrs.shaderProgram, 0, "inPosition" );
   glLinkProgram ( attrs.shaderProgram );
   glUseProgram ( attrs.shaderProgram );

   auto projection = glGetUniformLocation ( attrs.shaderProgram, "projection" );
   auto view = glGetUniformLocation ( attrs.shaderProgram, "view" );
   auto model = glGetUniformLocation ( attrs.shaderProgram, "model" );

   glBindVertexArray ( vao );
   glBindBuffer ( GL_ARRAY_BUFFER, vbo );
   glBindTexture ( GL_TEXTURE_1D, texture );

   attrs.projection = glm::perspective ( glm::radians ( 45.0f ), ( GLfloat )attrs.width/attrs.height, 0.1f, 20.0f );
   attrs.view = glm::lookAt ( glm::vec3 ( 0, 5, -5 ), glm::vec3 ( 0, 0, 0 ), glm::vec3 ( 0, 1, 0 ) );
   attrs.model = glm::mat4 ( 1.0f );

   glUniformMatrix4fv ( projection, 1, GL_FALSE, glm::value_ptr ( attrs.projection ) );
   glUniformMatrix4fv ( view, 1, GL_FALSE, glm::value_ptr ( attrs.view ) );
   glUniformMatrix4fv ( model, 1, GL_FALSE, glm::value_ptr ( attrs.model ) );

   while ( true ) {
      attrs.model *= glm::rotate ( glm::radians ( 1.0f ), glm::vec3 ( 0.0f, 1.0f, 0.0f ) );
      glUniformMatrix4fv ( model, 1, GL_FALSE, glm::value_ptr( attrs.model ) ); 
      glBindBuffer ( GL_ARRAY_BUFFER, vbo );
      glClear ( GL_COLOR_BUFFER_BIT );
      glDrawArrays ( GL_LINES, 0, (GLint)( verts.size () / 3 )  );
      glfwPollEvents ( );

      glfwSwapBuffers ( window );
   }
   glfwTerminate ( );
}
