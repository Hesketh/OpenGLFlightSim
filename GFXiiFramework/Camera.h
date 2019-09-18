#pragma once
#include "CameraNode.h"

class Camera : public CameraNode
{
private:
	SceneNode* m_followTarget; //We have to use this instead of the scenegraph because the view matrix does not behave correctly.
	float m_rotationSpeed;
public:
	Camera(SceneNode* parent);
	Camera(SceneNode* parent, SceneNode* followTarget);
	~Camera();
	void Update() override;
};