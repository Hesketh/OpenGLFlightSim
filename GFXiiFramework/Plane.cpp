#include "Plane.h"
#include "Input.h"
#include "KeyCodes.h"

Plane::Plane(SceneNode* node, Renderable* renderable) : RenderableNode(node, renderable)
{
	Input::Instance()->RegisterKeybinding("YawPos", KEY_D);
	Input::Instance()->RegisterKeybinding("YawNeg", KEY_A);
	Input::Instance()->RegisterKeybinding("PitchPos", KEY_S);
	Input::Instance()->RegisterKeybinding("PitchNeg", KEY_W);
	Input::Instance()->RegisterKeybinding("RollPos", KEY_Q);
	Input::Instance()->RegisterKeybinding("RollNeg", KEY_E);

	m_movementSpeed = 0.5;
	m_rotationSpeed = 0.0025;
}

Plane::~Plane()
{
}

void Plane::Update()
{
	Transform()->Translate(Transform()->GetRight() * -m_movementSpeed);

	if (Input::Instance()->KeybindingPressed("YawPos"))
	{
		Transform()->AddRotation(m_rotationSpeed, 0, 0);
	}
	else if (Input::Instance()->KeybindingPressed("YawNeg"))
	{
		Transform()->AddRotation(-m_rotationSpeed, 0, 0);
	}

	if (Input::Instance()->KeybindingPressed("PitchPos"))
	{
		Transform()->AddRotation(0, 0, -m_rotationSpeed);
	}
	else if (Input::Instance()->KeybindingPressed("PitchNeg"))
	{
		Transform()->AddRotation(0, 0, m_rotationSpeed);
	}

	if (Input::Instance()->KeybindingPressed("RollPos"))
	{
		Transform()->AddRotation(0, m_rotationSpeed, 0);
	}
	else if (Input::Instance()->KeybindingPressed("RollNeg"))
	{
		Transform()->AddRotation(0, -m_rotationSpeed, 0);
	}
}
