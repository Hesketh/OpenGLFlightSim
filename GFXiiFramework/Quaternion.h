#pragma once

#include "Vector3.h"

class Quaternion
{
private:
	Vector3					m_vector;
	float					m_scalar;

public:
	Quaternion();
	~Quaternion();

	const Vector3&		GetVector() const;
	const float			GetScalar() const;

	const float&		operator [] (int index) const;
	Quaternion			operator + (const Quaternion& rhs) const;
	Quaternion			operator * (const Quaternion& rhs) const;
	//Vector3				operator * (const Vector3& rhs)	const;

	float				Norm();
	float				Norm_Sqr() const;
	void				Normalise();
	void				ConvertToRotationMatrix(float* rot) const;
	void				SetQuaternion(float vx, float vy, float vz, float s);
	void				SetQuaternion(const Vector3& vec, float s);
};