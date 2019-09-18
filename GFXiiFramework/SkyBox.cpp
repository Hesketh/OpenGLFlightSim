#include "SkyBox.h"
#include "OGLResourceLoader.h"
#include "GLEW/include/glew.h"

SkyBox::SkyBox()
{
	Init();
}

//Im sure this could be made more generic very easily. 
void SkyBox::Init()
{
	m_textures[0] = static_cast<OGLTexture*>(OGLResourceLoader::Instance()->GetResource(ResourceLoader::EResourceType::Texture, "../asset/texture/sky_bk.tga"));
	m_textures[1] = static_cast<OGLTexture*>(OGLResourceLoader::Instance()->GetResource(ResourceLoader::EResourceType::Texture, "../asset/texture/sky_rt.tga"));
	m_textures[2] = static_cast<OGLTexture*>(OGLResourceLoader::Instance()->GetResource(ResourceLoader::EResourceType::Texture, "../asset/texture/sky_ft.tga"));
	m_textures[3] = static_cast<OGLTexture*>(OGLResourceLoader::Instance()->GetResource(ResourceLoader::EResourceType::Texture, "../asset/texture/sky_lt.tga"));
	m_textures[4] = static_cast<OGLTexture*>(OGLResourceLoader::Instance()->GetResource(ResourceLoader::EResourceType::Texture, "../asset/texture/sky_tp.tga"));
	m_textures[5] = static_cast<OGLTexture*>(OGLResourceLoader::Instance()->GetResource(ResourceLoader::EResourceType::Texture, "../asset/texture/sky_bt.tga"));
}

void SkyBox::Render()
{
	glFrontFace(GL_CW);
	//glDisable(GL_DEPTH_TEST);

	for (int i = 0; i < 6; i++)
	{
		unsigned int texHandle = dynamic_cast<OGLTexture*>(m_textures[i])->m_syshandle;
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texHandle);

		glBindVertexArray(m_vao);
		glDrawElements(GL_TRIANGLES, 6 + (i*6), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	//glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
}

//This is a cube
//unsigned int texHandle = dynamic_cast<OGLTexture*>(m_tex)->m_syshandle;
//glActiveTexture(GL_TEXTURE0);
//glBindTexture(GL_TEXTURE_2D, texHandle);

//glBindVertexArray(m_vao);
//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//glBindVertexArray(0);

//This is a mesh
//unsigned int texHandle = dynamic_cast<OGLTexture*>(m_tex)->m_syshandle;
//
//glActiveTexture(GL_TEXTURE0);
//glBindTexture(GL_TEXTURE_2D, texHandle);
//
//glBindVertexArray(m_vao);
//glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
//glDrawArrays(GL_TRIANGLES, 0, m_numtriangles * 3);
//
//glBindVertexArray(0);