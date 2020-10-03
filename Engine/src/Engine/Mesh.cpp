#include "Mesh.h"
#include "Texture.h"
#include <string>
#include <vector>

#include <GL/glew.h>
#include <GL/gl.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
  m_Vertices = vertices;
  m_Indices = indices;
  m_Textures = textures;
}

void Mesh::setupMesh()
{
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);
  
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

    glBufferData(GL_ARRAY_BUFFER, m_Vertices.size() * sizeof(Vertex), &m_Vertices[0], GL_STATIC_DRAW);  

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * sizeof(unsigned int), 
                 &m_Indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);	
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);	
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);	
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, m_TexCoords));

    glBindVertexArray(0);
}

void Mesh::Draw(Shader *shader)
{
  unsigned int diffuseNr = 1;
  unsigned int specularNr = 1;

  for(unsigned int i = 0; i < m_Textures.size(); i++)
  {
    glActiveTexture(GL_TEXTURE0 + i);
    std::string number;
    std::string name = m_Textures[i].GetType();

    if(name == "Texture_diffuse")
      number = std::to_string(diffuseNr++);
    else if(name == "Texture_specular")
      number = std::to_string(specularNr++);

    // shader->SetFloat(("u_Material." + name + number).c_str(), i);
    shader->SetInt(("u_" + name + number).c_str(), i);

    m_Textures[i].Bind(i);
  }

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

}
