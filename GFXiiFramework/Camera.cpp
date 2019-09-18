#include "Camera.h"
#include "Input.h"
#include "KeyCodes.h"
#include "Plane.h"

#include <iostream>

Camera::Camera(SceneNode* parent) : CameraNode(parent) 
{
}

Camera::Camera(SceneNode* parent, SceneNode* followTarget) : CameraNode(parent)
{
	m_followTarget = followTarget;

	Transform()->SetRotation(-1, 0, 0);

	m_rotationSpeed = static_cast<Plane*>(m_followTarget)->GetRotationSpeed();
}

void Camera::Update()
{
	//This is a hacky way of making the camera follow the gameobject because of problems with my scene graph / transformation
	if (m_followTarget)
	{
		Transform()->SetPosition(m_followTarget->GetWorldPosition()[0], m_followTarget->GetWorldPosition()[1], m_followTarget->GetWorldPosition()[2]);
		Transform()->Translate(m_followTarget->Transform()->GetRight() * 50);
		Transform()->Translate(m_followTarget->Transform()->GetUp() * 25);
	}

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
		Transform()->AddRotation(0, m_rotationSpeed, 0);
	}
	else if (Input::Instance()->KeybindingPressed("PitchNeg"))
	{
		Transform()->AddRotation(0, -m_rotationSpeed, 0);
	}

	if (Input::Instance()->KeybindingPressed("RollPos"))
	{
		Transform()->AddRotation(0, 0, m_rotationSpeed);
	}
	else if (Input::Instance()->KeybindingPressed("RollNeg"))
	{
		Transform()->AddRotation(0, 0, -m_rotationSpeed);
	}

	UpdateViewMatrix();
}