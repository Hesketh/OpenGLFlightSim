#include "OGLResourceLoader.h"
#include "SkyBox.h"

OGLResourceLoader* OGLResourceLoader::m_instance = 0;

void OGLResourceLoader::LoadTexture(std::string filepath)
{
	if (!m_textures.GetResource(filepath))
	{
		OGLTexture* newTexture = new OGLTexture();
		newTexture->CreateTextureFromFile(filepath.c_str());

		m_textures.AddResource(filepath, newTexture);
	}
}

void OGLResourceLoader::LoadMesh(std::string filepath)
{
	if (!m_meshes.GetResource(filepath))
	{
		//Convert the filepath into a wide string
		std::wstring wide(filepath.begin(), filepath.end());

		OGLMesh* newMesh = new OGLMesh();
		newMesh->LoadAndBuildMeshFromOBJFile(wide.c_str());

		m_meshes.AddResource(filepath, newMesh);
	}
}

void OGLResourceLoader::LoadSkyBox()
{
	if (!m_skyboxes.GetResource("default"))
	{
		SkyBox* skybox = new SkyBox();

		m_skyboxes.AddResource("default", skybox);
	}
}

void OGLResourceLoader::LoadResource(EResourceType type, std::string filepath)
{
	switch (type)
	{
		case EResourceType::Mesh:
			LoadMesh(filepath);
			break;
		case EResourceType::Texture:
			LoadTexture(filepath);
			break;
		case EResourceType::Skybox:
			LoadSkyBox();
			break;
	}
}

void* OGLResourceLoader::GetResource(EResourceType type, std::string filepath)
{
	LoadResource(type, filepath);

	switch (type)
	{
	case EResourceType::Mesh:
		return m_meshes.GetResource(filepath);
	case EResourceType::Texture:
		return m_textures.GetResource(filepath);
	case EResourceType::Skybox:
		return m_skyboxes.GetResource("default");
	}
}