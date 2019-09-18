#pragma once
#include "SceneNode.h"
#include "Vector3.h"
#include "Matrix4x4.h"

class CameraNode : public SceneNode
{
public:
	enum ECameraType
	{
		CAM_ORTHOGRAPHIC,
		CAM_PERSPECTIVE
	};

private:
	Matrix4x4			m_viewMatrix;
	Matrix4x4			m_projectionMatrix;

	ECameraType			m_cameratype;

	bool				m_dirtyView;
	bool				m_dirtyProj;

	float				m_fov, m_aspectRatio;
	float				m_zNear, m_zFar;
public:
	CameraNode(SceneNode* parent);
	~CameraNode();

	void				InitCamera();

	void				SetLookAtPoint(const Vector3* lookAt);
	void				SetUpVector(const Vector3* up);

	void				SetFOV(float fov);
	void				SetAspectRatio(float ar);

	void				UpdateViewMatrix();
	void				UpdateProjectionMatrix();

	void				SetProjectionMatrix(float fovy, float aspect, float zNear, float zFar);

	void				StrafeCamera(float amount);
	void				DollyCamera(float amount);
	void				PedCamera(float amount);
	void				ZoomCamera(float amount);
	void				RotateCamera(float yaw, float pitch, float roll);

	Matrix4x4			GetViewMatrix();
	Matrix4x4			GetProjectionMatrix();

	virtual void		Update() = 0;
};