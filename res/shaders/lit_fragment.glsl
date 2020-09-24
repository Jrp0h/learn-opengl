#version 330 core

out vec4 FragColor;

uniform vec3 u_ObjectColor;
uniform vec3 u_LightColor;
uniform vec3 u_LightPosition;
uniform vec3 u_ViewPosition;

in vec3 Normal;
in vec3 FragPos;

void main()
{
  float ambientStrength = 0.1;
  float specularStrength = 2;

  vec3 ambient = ambientStrength * u_LightColor;

  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(u_LightPosition - FragPos);

  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * u_LightColor;

  vec3 viewDir = normalize(u_ViewPosition - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
  vec3 specular = specularStrength * spec * u_LightColor;

  vec3 result = (ambient + diffuse + specular) * u_ObjectColor;

  FragColor = vec4(result, 1.0f);
}
