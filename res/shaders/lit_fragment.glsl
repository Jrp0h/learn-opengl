#version 330 core

out vec4 FragColor;

// uniform vec3 u_ObjectColor;
// uniform vec3 u_LightColor;
// uniform vec3 u_LightPosition;
uniform vec3 u_ViewPosition;

struct Material {
  sampler2D texture_diffuse1;
  sampler2D texture_diffuse2;
  sampler2D texture_diffuse3;
  sampler2D texture_diffuse1;
  sampler2D texture_diffuse2;
  float shininess;
};

struct PointLight {
  vec3 position;
  vec3 diffuse;
  vec3 specular;
  vec3 ambient;

  float constant;
  float linear;
  float quadratic;
};

struct DirectionalLight {
  vec3 direction;

  vec3 diffuse;
  vec3 specular;
  vec3 ambient;
};

struct Spotlight {
  vec3 position;
  vec3 direction;

  vec3 diffuse;
  vec3 specular;
  vec3 ambient;

  float cutOff;
  float outerCutOff;
  float constant;
  float linear;
  float quadratic;
};

uniform Material u_Material;

#define NUM_POINT_LIGHTS 4
uniform PointLight u_PointLights[NUM_POINT_LIGHTS];

uniform Spotlight u_Spotlight;
uniform DirectionalLight u_DirectionLight;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
  vec3 lightDir = normalize(light.position - fragPos);

  float diff = max(dot(normal, lightDir), 0.0);

  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);

  float dist = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

  vec3 ambient =  light.ambient * vec3(texture(u_Material.diffuse, TexCoords));
  vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, TexCoords));
  vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, TexCoords));

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return ambient + diffuse + specular;
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
  vec3 lightDir = normalize(-light.direction);

  float diff = max(dot(normal, lightDir), 0.0);

  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);

  vec3 ambient =  light.ambient * vec3(texture(u_Material.diffuse, TexCoords));
  vec3 diffuse = light.diffuse * diff * vec3(texture(u_Material.diffuse, TexCoords));
  vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, TexCoords));

  return ambient + diffuse + specular;
}

vec3 calculateSpotlight(Spotlight light, vec3 normal, vec3 fragPos, vec3 viewDir) {

  vec3 lightDir = normalize(light.position - FragPos);

  float diff = max(dot(normal, lightDir), 0.0);

  vec3 reflectDir = reflect(-lightDir, normal);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);

  float theta = dot(lightDir, normalize(-light.direction));
  float epsilon = (light.cutOff - light.outerCutOff);
  float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

  float dist = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * dist + light.quadratic * (dist * dist));

  vec3 diffuse = light.diffuse * (diff * vec3(texture(u_Material.diffuse, TexCoords)));
  vec3 ambient =  light.ambient * vec3(texture(u_Material.diffuse, TexCoords));
  vec3 specular = light.specular * (spec * vec3(texture(u_Material.specular, TexCoords)));

  ambient *= intensity;
  diffuse *= intensity;
  specular *= intensity;

  ambient *= attenuation;
  diffuse *= attenuation;
  specular *= attenuation;

  return ambient + diffuse + specular;
}


void main()
{
  vec3 norm = normalize(Normal);
  vec3 viewDir = normalize(u_ViewPosition - FragPos);

  vec3 result = calculateDirectionalLight(u_DirectionLight, norm, viewDir);

  for(int i = 0; i < NUM_POINT_LIGHTS; i++)
    result += calculatePointLight(u_PointLights[i], norm, FragPos, viewDir);

  result += calculateSpotlight(u_Spotlight, norm, FragPos, viewDir);

  FragColor = vec4(result, 1.0);
}

