#ifndef __INCLUDED_GRAPHICS_H__
#define __INCLUDED_GRAPHICS_H__

#include <string> 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector> 

class Graphics {
private:
   GLint mWidth;
   GLint mHeight;
   std::string mWindowName;
   GLFWwindow * mWindow;
   GLuint mVao, mVbo;
   GLuint mShaderProgram;

   GLuint loadInShader ( char const *fname, GLenum const &shaderType ) const;
public:
   Graphics ( GLint const &width, GLint const &height, std::string name );
   void initializeWindow ();
   void initializeShaders ( std::string const &vertFile, std::string const &fragFile, std::string const &geoFile );
   void updateVbo ( std::vector<GLfloat> const &newVerts );
   void draw ( GLint const &arrayIndex ) const;
};

#endif
