#include "Scene.h"
#include "AABB.h"
#include "SceneBuilder.h"
#include <iostream>

void Scene::FindNodesOfTypeInChildren(SceneNode::ENodeType type, SceneNode* root, std::vector<SceneNode*>* collection)
{
	if (root)
	{
		for (int childIndex = 0; childIndex < root->GetNumChildren(); childIndex++)
		{
			SceneNode* child = root->GetChild(childIndex);

			//If of correct type
			if (child->GetNodeType() == type)
			{
				collection->push_back(child);
			}

			if (child->GetNumChildren() > 0)
			{
				FindNodesOfTypeInChildren(type, child, collection);
			}
		}
	}
}

SceneNode* Scene::FindNodeOfTypeInChildren(SceneNode::ENodeType type, SceneNode* root)
{
	if (root)
	{
		for (int childIndex = 0; childIndex < root->GetNumChildren(); childIndex++)
		{
			SceneNode* child = root->GetChild(childIndex);

			//If of correct type
			if (child->GetNodeType() == type)
			{
				return child;
			}

			if (child->GetNumChildren() > 0)
			{
				SceneNode* node = FindNodeOfTypeInChildren(type, child);
				if (node)
				{
					if (node->GetNodeType() == type)
					{
						return node;
					}
				}
			}
		}
	}
	return nullptr;
}

void Scene::UpdateNode(SceneNode* node)
{
	if (node)
	{
		for (int childIndex = 0; childIndex < node->GetNumChildren(); childIndex++)
		{
			SceneNode* child = node->GetChild(childIndex);

			child->Update();

			if (child->GetNumChildren() > 0)
			{
				UpdateNode(child);
			}
		}
	}
}

Scene::Scene()
{
}

Scene::~Scene() 
{
	//delete m_skybox;
	//delete m_origin; //TODO: This needs to get rid of all the children too
}

std::vector<SceneNode*> Scene::GetRenderables()
{
	std::vector<SceneNode*>* renderables = new std::vector<SceneNode*>();

	FindNodesOfTypeInChildren(SceneNode::ENodeType::RenderNode, m_origin, renderables);

	return *renderables;
}

CameraNode* Scene::GetActiveCamera()
{
	return static_cast<CameraNode*>(FindNodeOfTypeInChildren(SceneNode::ENodeType::CameraNode, m_origin));
}

void Scene::Update()
{
	m_origin->Update();
	UpdateNode(m_origin);
}

void Scene::CheckCollisions()
{
	std::vector<SceneNode*> nodes = GetRenderables();

	for (int i = 0; i < nodes.size(); i++)
	{
		RenderableNode* n1 = static_cast<RenderableNode*>(nodes[i]);
		AABB colliderA = n1->GetCollisionBox() + n1->GetWorldPosition(); //This doesnt properly transform the bounding box to where it should be. Scale and rotation caused issues so we just us position to give us something that sort of works for now

		//std::cout << "A:     ";
		//colliderA.DebugPrint();
		
		for (int j = i + 1; j < nodes.size(); j++)
		{
			RenderableNode* n = static_cast<RenderableNode*>(nodes[j]);
			AABB colliderB = n->GetCollisionBox() + n->GetWorldPosition();

			//std::cout << "B:      ";
			//colliderB.DebugPrint();

			if (colliderA.Intersects(colliderB) || colliderB.Intersects(colliderA))
			{
				static_cast<RenderableNode*>(nodes[i])->OnCollision(static_cast<RenderableNode*>(nodes[j]));
				static_cast<RenderableNode*>(nodes[j])->OnCollision(static_cast<RenderableNode*>(nodes[i]));
			}
		}
	}
}

RenderableNode* Scene::GetSkyBox()
{
	return m_skybox;
}
