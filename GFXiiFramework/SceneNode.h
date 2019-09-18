#pragma once
#include "Transformation.h"
#include "Matrix4x4.h"
#include <vector>

class SceneNode
{
//NodeType
	public:
		enum ENodeType
		{
			EmptyNode,
			RenderNode,
			CameraNode
		};

		inline ENodeType		GetNodeType()
		{
			return m_type;
		}
	protected:
		ENodeType				m_type;

//Node
	private:
		SceneNode*				m_parent;
		std::vector<SceneNode*>	m_children;
	public:
		SceneNode();
		SceneNode(SceneNode* parent);
		~SceneNode();
		virtual void			Update() { ; };
		void					AddChild(SceneNode* node);
		SceneNode*				GetChild(int nth);
		int						GetNumChildren();
		SceneNode*				GetParent();

//Transformation
	private:
		Transformation			m_transform;
	public:
		Transformation*			Transform();
		Matrix4x4				GetWorldTransform();
		Vector3					GetWorldPosition();
};

//look into normal map