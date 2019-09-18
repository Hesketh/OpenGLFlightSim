#pragma once
#include "RenderableNode.h"

class Obstruction : public RenderableNode
{
public:
	Obstruction(SceneNode* node, Renderable* renderable);
	void Update() override;
	void OnCollision(RenderableNode* other) override;
	~Obstruction();
};

