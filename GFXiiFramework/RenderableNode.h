#pragma once
#include "SceneNode.h"
#include "Renderable.h"
#include "AABB.h"

class RenderableNode : public SceneNode
{
private:
	Renderable*		m_mesh;
	AABB*			m_collision;
	bool			m_willRender;
public:
	RenderableNode();
	RenderableNode(SceneNode* parent, Renderable* renderable);
	~RenderableNode();

	Renderable*  GetRenderable();
	void		 SetRenderable(Renderable* renderable);
	void		 Render();
	AABB		 GetCollisionBox();
	void		 SetCollisionBox(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	void		 ToggleRender(bool value);

	virtual void Update();
	virtual void OnCollision(RenderableNode* other);
};