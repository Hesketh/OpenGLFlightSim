#include "Transformation.h"
#include "Vector4.h"
#include <iostream>

Transformation::Transformation(Vector3 up, Vector3 forward)
{
	m_transformation.SetIdentity();
	m_position.SetZero();

	SetAxis(up, forward);
}

void Transformation::UpdateMatrix()
{
	Matrix4x4	translation;
	Matrix4x4	rotation;
	float		rotationFloat[16];

	translation.SetTranslate(Vector4(m_position[0], m_position[1], m_position[2]));
	m_rotation.ConvertToRotationMatrix(rotationFloat);
	rotation.SetMatrix(rotationFloat);

	m_transformation = translation * rotation * m_scale;
}

Matrix4x4 Transformation::GetMatrix()
{
	if (m_dirty)
	{
		UpdateMatrix();
		m_dirty = false;
	}

	return m_transformation;
}

void Transformation::SetPosition(Vector3 position)
{
	m_position = position;

	m_dirty = true;
}

void Transformation::SetPosition(float x, float y, float z)
{
	m_position[0] = x;
	m_position[1] = y;
	m_position[2] = z;

	m_dirty = true;
}

void Transformation::Translate(Vector3 translation)
{
	m_position = m_position + translation;

	m_dirty = true;
}

void Transformation::Translate(float x, float y, float z)
{
	m_position[0] += x;
	m_position[1] += y;
	m_position[2] += z;

	m_dirty = true;
}

void Transformation::SetScale(float sx, float sy, float sz)
{
	m_scale.SetScale(sx, sy, sz);

	m_dirty = true;
}

void Transformation::SetRotation(float yaw, float pitch, float roll)
{
	Quaternion qYaw;
	Quaternion qPitch;
	Quaternion qRoll;

	qYaw.SetQuaternion(m_up, yaw);
	qPitch.SetQuaternion(m_right, pitch);
	qRoll.SetQuaternion(m_forward, roll);

	m_rotation = qRoll * qPitch * qYaw;

	m_dirty = true;
}

void Transformation::AddRotation(float yaw, float pitch, float roll)
{
	Quaternion qYaw;
	Quaternion qPitch;
	Quaternion qRoll;

	qYaw.SetQuaternion(m_up, yaw);
	qPitch.SetQuaternion(m_right, pitch);
	qRoll.SetQuaternion(m_forward, roll);

	m_rotation = m_rotation * qRoll * qPitch * qYaw;

	m_dirty = true;
}

Matrix4x4 Transformation::GetRotation()
{
	Matrix4x4	rotation;
	float		rotationFloat[16];

	m_rotation.ConvertToRotationMatrix(rotationFloat);
	rotation.SetMatrix(rotationFloat);

	return rotation;
}

void Transformation::SetAxis(Vector3 up, Vector3 forward, bool print)
{
	if (print)
	{
		std::cout << "Up:" << m_up[0] << "," << m_up[1] << "," << m_up[2] << std::endl;
		std::cout << "Right:" << m_right[0] << "," << m_right[1] << "," << m_right[2] << std::endl;
		std::cout << "Forward:" << m_forward[0] << "," << m_forward[1] << "," << m_forward[2] << std::endl;
	}

	m_up = up;
	m_forward = forward;
	m_right = m_forward.CrossProduct(m_up);
	m_up = m_right.CrossProduct(m_forward);

	if (print)
	{
		std::cout << "Up:" << m_up[0] << "," << m_up[1] << "," << m_up[2] << std::endl;
		std::cout << "Right:" << m_right[0] << "," << m_right[1] << "," << m_right[2] << std::endl;
		std::cout << "Forward:" << m_forward[0] << "," << m_forward[1] << "," << m_forward[2] << std::endl;
	}

	m_dirty = true;
}

Vector3 Transformation::GetPosition()
{
	UpdateMatrix();
	return m_position;
}

Vector3 Transformation::GetUp()
{
	UpdateMatrix();
	return Vector3(m_transformation.ToPtr()[1], m_transformation.ToPtr()[5], m_transformation.ToPtr()[9]).Normalise();
}

Vector3 Transformation::GetForward()
{
	UpdateMatrix();
	return Vector3(-m_transformation.ToPtr()[2], -m_transformation.ToPtr()[6], -m_transformation.ToPtr()[10]).Normalise();
}

Vector3 Transformation::GetRight()
{
	UpdateMatrix();
	return Vector3(m_transformation.ToPtr()[0], m_transformation.ToPtr()[4], m_transformation.ToPtr()[8]).Normalise();
}

Matrix4x4 Transformation::GetScale()
{
	UpdateMatrix();
	return m_scale;
}
