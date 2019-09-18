#include "CameraNode.h"
#include "Vector4.h"

CameraNode::CameraNode(SceneNode* parent) : SceneNode(parent)
{
	m_type = ENodeType::CameraNode;
	InitCamera();
}

CameraNode::~CameraNode() {}

void CameraNode::InitCamera()
{
	m_fov = 90.0f;
	m_aspectRatio = 1.0f;
	m_zNear = 1.0f;
	m_zFar = 5000.0f;
	m_cameratype = ECameraType::CAM_PERSPECTIVE;

	m_dirtyView = true;
	m_dirtyProj = true;

	UpdateProjectionMatrix();
	UpdateViewMatrix();
}

void CameraNode::SetLookAtPoint(const Vector3 * lookAt)
{
	Transform()->SetAxis(Transform()->GetUp(),((*lookAt) - GetWorldPosition()));

	m_dirtyView = true;
}

void CameraNode::SetUpVector(const Vector3* up)
{
	Transform()->SetAxis((*up), Transform()->GetForward());

	m_dirtyView = true;
}

void CameraNode::SetFOV(float fov)
{
	m_fov = fov;

	m_dirtyProj = true;
}

void CameraNode::SetAspectRatio(float ar)
{
	m_aspectRatio = ar;

	m_dirtyProj = true;
}

void CameraNode::UpdateViewMatrix()
{
	m_viewMatrix = GetWorldTransform().Inverse();

	m_dirtyView = false;
}

void CameraNode::UpdateProjectionMatrix()
{
	m_projectionMatrix.SetPerspective(m_fov, m_aspectRatio, m_zNear, m_zFar);
	m_dirtyProj = false;
}

void CameraNode::SetProjectionMatrix(float fovy, float aspect, float zNear, float zFar)
{
	m_fov = fovy;
	m_aspectRatio = aspect;
	m_zFar = zFar;
	m_zNear = zNear;

	m_dirtyProj = true;
}

void CameraNode::StrafeCamera(float amount)
{
	Transform()->Translate(Transform()->GetRight() * -amount);

	m_dirtyView = true;
}

void CameraNode::DollyCamera(float amount)
{
	Transform()->Translate(Transform()->GetForward() * -amount);

	m_dirtyView = true;
}

void CameraNode::PedCamera(float amount)
{
	Transform()->Translate(Transform()->GetUp() * -amount);

	m_dirtyView = true;
}

void CameraNode::ZoomCamera(float amount)
{
	m_fov -= amount;

	m_dirtyProj = true;
}

void CameraNode::RotateCamera(float yaw, float pitch, float roll)
{
	Transform()->AddRotation(yaw, pitch, roll);

	m_dirtyView = true;
}

Matrix4x4 CameraNode::GetViewMatrix()
{
	if (m_dirtyView)
	{
		UpdateViewMatrix();
	}

	return m_viewMatrix;
}

Matrix4x4 CameraNode::GetProjectionMatrix() 
{
	if (m_dirtyProj)
	{
		UpdateProjectionMatrix();
	}

	return m_projectionMatrix;
}