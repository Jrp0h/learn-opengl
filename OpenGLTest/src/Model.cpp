#include "Model.h"
#include "Texture.h"
#include "Utils.h"

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/mesh.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/types.h>
#include <string>
#include <exception>
#include <stdexcept>
#include <iostream>


Model::Model(const char* path)
{
  loadModel(path);
}

void Model::Draw(Shader *shader)
{
  for(unsigned int i = 0; i < m_Meshes.size(); i++)
    m_Meshes[i].Draw(shader);
}

void Model::loadModel(std::string path)
{
  Assimp::Importer importer;
  const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    throw std::runtime_error(Utils::ConcatStrings({"Error::Assimp::", importer.GetErrorString()}));
  }
  m_Directory = path.substr(0, path.find_last_of('/'));

  proccessNode(scene->mRootNode, scene);
}

void Model::proccessNode(aiNode* node, const aiScene* scene)
{
  for(unsigned int i = 0; i < node->mNumMeshes; i++)
  {
    aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
    m_Meshes.push_back(proccessMesh(mesh, scene));
  }

  for(unsigned int i = 0; i < node->mNumChildren; i++)
    proccessNode(node->mChildren[i], scene);
}

Mesh Model::proccessMesh(aiMesh* mesh, const aiScene* scene)
{
  
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  for(unsigned int i = 0; i < mesh->mNumVertices; i++)
  {
    Vertex vertex;

    glm::vec3 vector;
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;

    vertex.m_Position = vector;

    if(mesh->HasNormals())
    {
      vector.x = mesh->mNormals[i].x;
      vector.y = mesh->mNormals[i].y;
      vector.z = mesh->mNormals[i].z;
      vertex.m_Normal = vector;
    }

    if(mesh->mTextureCoords[0])
    {
      glm::vec2 vec;

      vec.x = mesh->mTextureCoords[0][i].x;
      vec.y = mesh->mTextureCoords[0][i].y;

      vertex.m_TexCoords = vec;

      // vector.x = mesh->mTangents[i].x;
      // vector.y = mesh->mTangents[i].y;
      // vector.z = mesh->mTangents[i].z;

    }

    vertices.push_back(vertex);
  }

  // Load indices
  for(unsigned int i = 0; i < mesh->mNumFaces; i++)
  {
    aiFace face = mesh->mFaces[i];
    for(unsigned int j = 0; j < face.mNumIndices; j++)
    {
      indices.push_back(face.mIndices[j]);
    }
  }

  if(mesh->mMaterialIndex >= 0)
  {
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    // Load diffuse maps
    std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "Texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

    // Load specular maps
    std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "Texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
  }

  return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
  std::vector<Texture> textures;

  for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
  {
    aiString str;
    mat->GetTexture(type, i, &str);
    Texture texture(Utils::ConcatStrings({m_Directory, "/", str.C_Str()}).c_str());
    textures.push_back(texture);
  }

  return textures;
}
