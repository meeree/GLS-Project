#include "lSystem.h"
#include "turtle.cpp"
#include "../openGL/generalGraphicsDirectory.cpp"
#include <algorithm>
#include <iostream>

lSystem::lSystem(lSysString const &string, lSysString * endStringContainer, std::vector<char> const &variables, std::vector<char> const &constants, std::vector<rule> const &rules) {
   mString1 = string;
   mString2 = endStringContainer;
   mVariables = variables;
   mConstants = constants;
   mRules = rules;
}

void lSystem::update() {
   mString2->clear();
   for (auto const &symbol: mString1) {
      char const &name = symbol.name;
      std::vector<double> const &params = symbol.params;
      if (std::find(mConstants.begin(), mConstants.end(), name) != mConstants.end()) {
         mString2->push_back(symbol);
      } else {
         auto const &it = std::find(mVariables.begin(), mVariables.end(), name);
         if (it != mVariables.end()) {
            auto const &stringAddition = mRules[it-mVariables.begin()](params, mString2);
            mString2->insert(mString2->end(), stringAddition.begin(), stringAddition.end());
         }
      }
   }
   mString1.clear();
   mString1.resize(mString2->size());
   for (int iSymbol = 0; iSymbol < mString2->size(); iSymbol++) {
      mString1[iSymbol] = (*mString2)[iSymbol];
   }
}
//ADD ADDOBJECT UPDATEOBJECT AND ADDSHADER METHODS

int main () {
   lSysSymbol plus = {'+', {3.14/7}};
   lSysSymbol minus = {'-', {3.14/7}};
   lSysSymbol up = {'^', {3.14/7}};
   lSysSymbol down = {'V', {3.14/7}};
   lSysSymbol lbrack = {'['};
   lSysSymbol rbrack = {']'};

   std::vector<char> variables = {'A'}; /*Variables must be ordered the same as rules*/
   std::vector<char> constants = {plus.name, minus.name, up.name, down.name, lbrack.name, rbrack.name, 'F'};
   lSysString string = {{'F', {2}}, {'A', {2}}}, container = {};
   

//   rule rule1 = [&] (std::vector<double> params, lSysString* string) {return (std::vector<lSysSymbol>){{'F', {params[0]}}, {'A', {params[0]/1.9}},{'F', {params[0]/2}}}; };
   rule rule1 = [&] (std::vector<double> params, lSysString* string) {return (std::vector<lSysSymbol>){lbrack,plus,{'F', {params[0]}},{'A', {params[0]/2}},rbrack,lbrack,minus,{'F', {params[0]}},{'A', {params[0]/2}},rbrack,lbrack,up,{'F', {params[0]}},{'A', {params[0]/2}},rbrack,lbrack,down,{'F', {params[0]}},{'A', {params[0]/2}},rbrack,{'F', {params[0]/2}},{'A', {params[0]/1.1}}}; };

   std::vector<rule> rules = {rule1};
   lSystem test(string, &container, variables, constants, rules);

   std::vector<double> pos0 {0, -5, 0}, ori0 {0, 1, 0};

   std::vector<GLdouble> vertices {0,-5,0}, colors {};
   std::vector<GLint> indices {};

   turtle toitle(pos0, ori0, &vertices);

   for (int iCounter = 0; iCounter < 6; iCounter++) {
      test.update();
   }

   for (auto const &sym: container) {
//      std::cout<<sym.name<<"{";
//      for (auto const &param: sym.params) {
//         std::cout<<param;
//      }
//      std::cout<<"}";
      if (sym.name=='F') {
         toitle.mv(sym.params[0]);
         continue;
      }
      if (sym.name==']') {
         toitle.popMatrix();
         continue;
      }

      switch(sym.name) {
         case '+':
            toitle.Rz(sym.params[0]);
            continue;
         case '-':
            toitle.Rz(-sym.params[0]);
            continue;
         case '^':
            toitle.Rx(sym.params[0]);
            continue;
         case 'V':
            toitle.Rx(-sym.params[0]);
            continue;
         case '[':
            toitle.pushMatrix();
            continue;
      }
   }
   std::cout<<std::endl;

   for (int iVert=0; iVert < (vertices.size()-1)/3; iVert++) {
      indices.push_back(iVert);
      indices.push_back(iVert+1);
   }

   for (int iVert=0; iVert < vertices.size(); iVert++) {
      colors.push_back(1);
   }

   initializePrograms(700, 700, false, 0, 0, 0);
   glm::mat4 projection = setProjection(40);
   glm::mat4 view = setView(0, 0, -20);
   glm::mat4 model = glm::mat4(1.0f);

   GLuint shaderProgram = createShaderProgram();
   readShaderSource("shaders/vert.shader", GL_VERTEX_SHADER, shaderProgram);
   readShaderSource("shaders/frag.shader", GL_FRAGMENT_SHADER, shaderProgram);
   auto vao = createVao();
   auto vbo = createVbo(vao);
   createEab(vbo, indices, false);

   auto position_attribute = glGetAttribLocation(shaderProgram, "position");
   auto color_attribute = glGetAttribLocation(shaderProgram, "vert_color");
   auto PVM = glGetUniformLocation(shaderProgram, "PVM");

   glBindBuffer(GL_ARRAY_BUFFER, vbo);
   glVertexAttribPointer(position_attribute, 3, GL_FLOAT, GL_FALSE, 0, 0);
   glVertexAttribPointer(color_attribute, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid *)(sizeof(GLfloat)*vertices.size()));

   glEnableVertexAttribArray(position_attribute);
   glEnableVertexAttribArray(color_attribute);

   updateVbo(vbo, vertices, colors, PVM, projection, view, model, false);
   while(true) {
      model *= glm::rotate(glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
      draw(indices.size(), GL_STATIC_DRAW);
   }
}
