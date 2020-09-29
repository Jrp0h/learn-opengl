#include "Texture.h"
#include "Vertex.h"
#include "Shader.h"

#include <vector>

struct Mesh {
  public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader* shader);

  private:
    unsigned int m_VBO, m_VAO, m_EBO;

    std::vector<Vertex> m_Vertices;
    std::vector<unsigned int> m_Indices;
    std::vector<Texture> m_Textures;

    void setupMesh();
};
