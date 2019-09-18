#include "RenderableNode.h"
#include "OpenGL\OGLMesh.h"

RenderableNode::RenderableNode() : SceneNode() 
{
	m_collision = new AABB(0, 0, 0, 0, 0, 0);
};

RenderableNode::RenderableNode(SceneNode* parent, Renderable* renderable) : SceneNode(parent) 
{
	SetRenderable(renderable);
	m_collision = new AABB(static_cast<OGLMesh*>(m_mesh)->GetMinX(), static_cast<OGLMesh*>(m_mesh)->GetMaxX(), static_cast<OGLMesh*>(m_mesh)->GetMinY(), static_cast<OGLMesh*>(m_mesh)->GetMaxY(), static_cast<OGLMesh*>(m_mesh)->GetMinZ(), static_cast<OGLMesh*>(m_mesh)->GetMaxZ());
};

RenderableNode::~RenderableNode() 
{
	m_mesh = nullptr;	//Lifetime dictated by resource management classes
	delete m_collision;
}

Renderable* RenderableNode::GetRenderable()
{
	return m_mesh;
}

void RenderableNode::SetRenderable(Renderable* renderable)
{
	m_mesh = renderable;
	m_type = ENodeType::RenderNode;
	m_willRender = true;
}

void RenderableNode::Render()
{
	if (m_mesh && m_willRender)
	{
		m_mesh->Render();
	}
}

AABB RenderableNode::GetCollisionBox()
{
	return *m_collision;
}

void RenderableNode::SetCollisionBox(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
	*m_collision = AABB(minX, maxX, minY, maxY, minZ, maxZ);
}

void RenderableNode::ToggleRender(bool value)
{
	m_willRender = value;
}

void RenderableNode::Update()
{
}

void RenderableNode::OnCollision(RenderableNode* other)
{
}