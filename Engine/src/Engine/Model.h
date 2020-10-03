#pragma once

#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
public:
  Model(const char* path);
  void Draw(Shader* shader);
private:
  std::vector<Mesh> m_Meshes;
  std::string m_Directory;

  void loadModel(std::string path);
  void proccessNode(aiNode* node, const aiScene* scene);
  Mesh proccessMesh(aiMesh* mesh, const aiScene* scene);

  std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
