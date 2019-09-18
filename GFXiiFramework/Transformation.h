#pragma once
#include "Vector3.h"
#include "Quaternion.h"
#include "Matrix4x4.h"

class Transformation
{
protected:
	Matrix4x4	m_transformation;
	Matrix4x4	m_scale;
	Quaternion	m_rotation;
	Vector3		m_position;

	bool		m_dirty;			//We only recalculate the matrix if something changes

	Vector3		m_up;
	Vector3		m_right;
	Vector3		m_forward;

	void UpdateMatrix();
public:
	Transformation(Vector3 up = Vector3(0.0f,1.0f,0.0f), Vector3 forward = Vector3(0.0f,0.0f,-1.0f));
	~Transformation() { ; };

	void		SetPosition(Vector3 position);
	void		SetPosition(float x, float y, float z);
	void		Translate(Vector3 translation);
	void		Translate(float x, float y, float z);

	void		SetRotation(float yaw, float pitch, float roll);
	void		AddRotation(float yaw, float pitch, float roll);
	Matrix4x4	GetRotation();

	void		SetAxis(Vector3 up, Vector3 forward, bool print = false);

	Vector3		GetPosition();
	Vector3		GetUp();
	Vector3		GetForward();
	Vector3		GetRight();

	void		SetScale(float sx, float sy, float sz);
	Matrix4x4	GetScale();

	Matrix4x4	GetMatrix();
};