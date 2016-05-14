#version 150 

in vec4 outColor;
out vec4 color;

void main () {
//   color = vec4 ( 0.5, 0.5, 0.5, 1.0 );
   color = outColor;
} 
