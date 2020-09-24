#version 330 core

layout(location = 0) out vec4 FragColor;
  
// in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D u_Texture;

void main()
{
      FragColor = texture(u_Texture, TexCoord);
}
