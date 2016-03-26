#include "turtle.h"
#include <cmath>
#include <iostream>

turtle::turtle(std::vector<double> const &position, std::vector<double> const orientation, std::vector<double> * vertices) {
   mPositionStack.push(position);
   mVertices = vertices;

   double magnitude = 0; /*normalize orientation with magnitude*/
   magnitude += pow(orientation[0], 2);
   magnitude += pow(orientation[1], 2);
   magnitude += pow(orientation[2], 2);
   magnitude = sqrt(magnitude);
   mOrientationStack.push({0, 0, 0});
   for (int iComponent = 0; iComponent < 3; iComponent++) {
      mOrientationStack.top()[iComponent] = orientation[iComponent] / magnitude;
   }
}

std::vector<double> turtle::Rx(double const &theta) {
   std::vector<double> const &curOri = mOrientationStack.top();
   mOrientationStack.push({curOri[0], 0, 0});
   mOrientationStack.top()[1] = curOri[1] * cos(theta) - curOri[2] * sin(theta);
   mOrientationStack.top()[2] = curOri[1] * sin(theta) + curOri[2] * cos(theta);
   return mOrientationStack.top();
}

std::vector<double> turtle::Ry(double const &theta) {
   std::vector<double> const &curOri = mOrientationStack.top();
   mOrientationStack.push({0, curOri[1], 0});
   mOrientationStack.top()[0] = curOri[0] * cos(theta) + curOri[2] * sin(theta);
   mOrientationStack.top()[2] = -curOri[0] * sin(theta) + curOri[2] * cos(theta);
   return mOrientationStack.top();
}

std::vector<double> turtle::Rz(double const &theta) {
   std::vector<double> const &curOri = mOrientationStack.top();
   mOrientationStack.push({0, 0, curOri[2]});
   mOrientationStack.top()[0] = curOri[0] * cos(theta) - curOri[1] * sin(theta);
   mOrientationStack.top()[1] = curOri[0] * sin(theta) + curOri[1] * cos(theta);
   return mOrientationStack.top();
}
   
void turtle::mv(double const &distance) {
   mPositionStack.push(mPositionStack.top());
   auto &top = mPositionStack.top();
   auto const &oriTop = mOrientationStack.top();
   for (int iComponent = 0; iComponent < 3; iComponent++) {
      top[iComponent] += distance * oriTop[iComponent];
      mVertices->push_back(top[iComponent]);
   }
}

void turtle::pushMatrix() {
   mPopStack.push(mPositionStack.size());
   mPopStack.push(mOrientationStack.size());
}

void turtle::popMatrix() {
   int const &oriPopCount = mOrientationStack.size() - mPopStack.top();
   mPopStack.pop();
   for (int iOriCounter = 0; iOriCounter < oriPopCount; iOriCounter++) {
      mOrientationStack.pop();
   }

   int const &posPopCount = mPositionStack.size() - mPopStack.top();
   mPopStack.pop();
   for (int iPosCounter = 0; iPosCounter < posPopCount; iPosCounter++) {
      mPositionStack.pop();
      auto const &top = mPositionStack.top();
      for (int iComponent = 0; iComponent < 3; iComponent++) {
         mVertices->push_back(top[iComponent]);
      }
   }
}
