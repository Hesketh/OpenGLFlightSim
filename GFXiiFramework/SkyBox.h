#pragma once
#include "OpenGL\OGLCube.h"
class SkyBox : public OGLCube
{
private:
	BaseTexture			*m_textures[6];
public:
	SkyBox();

	void				Init();
	void				Render() override;
};