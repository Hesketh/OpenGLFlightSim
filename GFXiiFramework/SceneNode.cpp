#include "SceneNode.h"

SceneNode::SceneNode()
{
	m_parent = nullptr;
	m_type = ENodeType::EmptyNode;
}

SceneNode::~SceneNode() {}

SceneNode::SceneNode(SceneNode* parent)
{
	if (parent)
	{
		m_parent = parent;
		parent->AddChild(this);
	}

	m_type = ENodeType::EmptyNode;
}

void SceneNode::AddChild(SceneNode* node)
{
	m_children.push_back(node);
}

SceneNode* SceneNode::GetChild(int nth)
{
	return m_children[nth];
}

int SceneNode::GetNumChildren()
{
	return m_children.size();
}

SceneNode* SceneNode::GetParent()
{
	return m_parent;
}

Transformation* SceneNode::Transform()
{
	return &m_transform;
}

Matrix4x4 SceneNode::GetWorldTransform()
{
	if (!m_parent)
	{
		return m_transform.GetMatrix();
	}
	return m_parent->GetWorldTransform() * m_transform.GetMatrix();
}

Vector3 SceneNode::GetWorldPosition()
{
	if (!m_parent)
	{
		return m_transform.GetPosition();
	}
	return m_parent->GetWorldPosition() + m_transform.GetPosition();
}
