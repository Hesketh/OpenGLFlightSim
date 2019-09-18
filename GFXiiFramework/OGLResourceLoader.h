#pragma once
#include "ResourceLoader.h"

#include "OpenGL\OGLMesh.h"
#include "OpenGL\OGLTexture.h"
#include "OpenGL\OGLShader.h"

class OGLResourceLoader : public ResourceLoader
{
	private:
		static OGLResourceLoader* m_instance;

		void	LoadTexture(std::string filepath);
		void	LoadMesh(std::string filepath);
		void	LoadSkyBox();

		OGLResourceLoader() { ; };
		~OGLResourceLoader() { ; };
	public:
		inline static OGLResourceLoader* Instance()
		{
			if (!m_instance)
			{
				m_instance = new OGLResourceLoader();
			}
			return m_instance;
		}

		void	LoadResource(EResourceType type, std::string filepath)	override;
		void*	GetResource(EResourceType type, std::string filepath)	override;
};