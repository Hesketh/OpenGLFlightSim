#pragma once
#include "RenderableNode.h"

class Collectable : public RenderableNode
{
private:
	static int CollectableCount;
	bool		m_collected;
public:
	Collectable(SceneNode* node, Renderable* renderable);
	void Update() override;
	void OnCollision(RenderableNode* other) override;
	~Collectable();
};

