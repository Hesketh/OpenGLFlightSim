#include "Collectable.h"
#include <random>
#include <iostream>

int Collectable::CollectableCount = 0;

Collectable::Collectable(SceneNode * node, Renderable * renderable) : RenderableNode(node, renderable)
{
	CollectableCount++;
	Transform()->SetRotation((((double)rand() / (RAND_MAX)) + 1),(((double)rand() / (RAND_MAX)) + 1), (((double)rand() / (RAND_MAX)) + 1));
	m_collected = false;
}

void Collectable::Update()
{
	Transform()->AddRotation(0.0005,0.0005,0.0005);
}

void Collectable::OnCollision(RenderableNode* other)
{
	if (!m_collected)
	{
		CollectableCount--;

		if (CollectableCount <= 0)
		{
			std::cout << "All Coins Collected! Game Over" << std::endl;
		}
		else
		{
			std::cout << CollectableCount << " coin(s) remaining" << std::endl;
		}

		m_collected = true;
		ToggleRender(false);
	}
}

Collectable::~Collectable()
{
}