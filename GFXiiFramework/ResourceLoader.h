#pragma once
#include "Singleton.h"
#include "ResourceContainer.h"

#include "Renderable.h"
#include "BaseTexture.h"

#include <string>

class ResourceLoader
{
	public:
		enum EResourceType
		{
			Mesh,
			Texture,
			Skybox
		};

	protected:
		ResourceContainer<Renderable>	m_meshes;
		ResourceContainer<BaseTexture>	m_textures;
		ResourceContainer<Renderable>	m_skyboxes;

	public:
		ResourceLoader() { ; };
		~ResourceLoader() { ; };

		virtual void	LoadResource(EResourceType type, std::string filepath)	= 0;
		virtual void*	GetResource(EResourceType type, std::string filepath)	= 0;
};