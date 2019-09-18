#include "Obstruction.h"
#include <iostream>

Obstruction::Obstruction(SceneNode * node, Renderable * renderable)
{
}

void Obstruction::Update()
{
}

void Obstruction::OnCollision(RenderableNode * other)
{
	std::cout << "Collision With Object" << std::endl;
	//TODO: Stuff
}

Obstruction::~Obstruction()
{
}
