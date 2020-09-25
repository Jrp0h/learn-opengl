#version 330 core

out vec4 FragColor;

// uniform vec3 u_ObjectColor;
// uniform vec3 u_LightColor;
// uniform vec3 u_LightPosition;
uniform vec3 u_ViewPosition;

struct Material {
  sampler2D diffuse;
  sampler2D specular;
  float shininess;
};

struct Pointlight {
  vec3 position;
  vec3 diffuse;
  vec3 specular;
  vec3 ambient;
};

struct DirectionalLight {
  vec3 direction;

  vec3 diffuse;
  vec3 specular;
  vec3 ambient;
}

uniform Material u_Material;
uniform Pointlight u_PointLight;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

void main()
{
  vec3 ambient =  u_PointLight.ambient * vec3(texture(u_Material.diffuse, TexCoords));

  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(u_PointLight.position - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = u_PointLight.diffuse * (diff * vec3(texture(u_Material.diffuse, TexCoords)));

  vec3 viewDir = normalize(u_ViewPosition - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
  vec3 specular = u_PointLight.specular * (spec * vec3(texture(u_Material.specular, TexCoords)));

  vec3 result = (ambient + diffuse + specular);

  FragColor = vec4(result, 1.0f);
}
