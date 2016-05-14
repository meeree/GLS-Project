#version 150

in vec3 position;
out vec4 outColor;
uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main () {
   gl_Position = vec4 ( position.xyz, 1.0 );
   outColor = gl_Position;
}
