#pragma once
#include "SceneNode.h"
#include "RenderableNode.h"
#include "SkyBox.h"
#include "CameraNode.h"

#include <vector>

class Scene
{
private:
	SceneNode*				m_origin;
	RenderableNode*			m_skybox;

	void					FindNodesOfTypeInChildren(SceneNode::ENodeType type, SceneNode* root, std::vector<SceneNode*>* collection);
	SceneNode*				FindNodeOfTypeInChildren(SceneNode::ENodeType type, SceneNode* root);
	void					UpdateNode(SceneNode* node);
public:
	Scene();
	~Scene();
	std::vector<SceneNode*>		GetRenderables();
	CameraNode*					GetActiveCamera();
	void						Update();
	void						CheckCollisions();
	RenderableNode*				GetSkyBox();
	
	inline void	SetRoot(SceneNode* node)
	{
		m_origin = node;
	}

	inline void SetSkyBox(RenderableNode* node)
	{
		m_skybox = node;
	}
};