#pragma once

class Vector4;

class Matrix4x4
{
private:
	float				m_element[4][4];

public:
	Matrix4x4();
	Matrix4x4(const Matrix4x4& rhs);
	~Matrix4x4();

	void				SetZero();
	void				SetIdentity();
	void				SetMatrix(float* rhs);
	const float*		ToPtr() const;

	Matrix4x4			Inverse() const;
	
	Matrix4x4			operator*(const Matrix4x4& rhs) const;
	Vector4				operator*(const Vector4& rhs) const;

	void				SetRotationXAxis(float degrees);
	void				SetRotationYAxis(float degrees);
	void				SetRotationZAxis(float degrees);
	void				SetTranslate(const Vector4& tvec);
	void				SetScale(float sx, float sy, float sz);

	bool				IsZero();

	void				SetPerspective(float fovy, float aspect, float zNear, float zFar);

	void				SetViewMatrix(const Vector4& camera_position, const Vector4& view_vector, const Vector4& up_vector);
};

