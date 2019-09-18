#pragma once
#include "RenderableNode.h"
class Plane : public RenderableNode
{
private:
	float m_movementSpeed;
	float m_rotationSpeed;
public:
	Plane(SceneNode* node, Renderable* renderable);
	~Plane();

	inline float GetRotationSpeed()
	{
		return m_rotationSpeed;
	}
	
	void Update();
};