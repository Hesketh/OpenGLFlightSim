#pragma once
#include "SceneNode.h"
#include <string>

#include "OGLResourceLoader.h"
#include "RenderableNode.h"
#include "Camera.h"

static class SceneBuilder
{
private:
	//ResourceLoader*		m_resourceLoader;
public:
	SceneBuilder();
	~SceneBuilder();


	SceneNode*		LoadDefaultScene();
	RenderableNode* LoadDefaultSkyBox();
};