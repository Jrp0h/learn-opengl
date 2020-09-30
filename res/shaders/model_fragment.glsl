#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D u_Texture_diffuse1;

void main()
{    
    FragColor = texture(u_Texture_diffuse1, TexCoords);
}
