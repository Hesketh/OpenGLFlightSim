#include <stdlib.h>
#include <math.h>

#include "Quaternion.h"

Quaternion::Quaternion()
{
	m_scalar = 1.0f;
}

Quaternion::~Quaternion()
{
}

const Vector3& Quaternion::GetVector() const
{
	return m_vector;
}

const float Quaternion::GetScalar() const
{
	return m_scalar;
}

const float& Quaternion::operator [] (int index) const
{
	if (index == 3)
		return m_scalar;

	return m_vector[index];
}

Quaternion Quaternion::operator + (const Quaternion& rhs) const
{
	Quaternion quat;
	Vector3 vec;
	float scalar;

	vec = m_vector + rhs.GetVector();
	scalar = m_scalar + rhs.GetScalar();

	quat.SetQuaternion(vec, scalar);

	return quat;
}

Quaternion Quaternion::operator * (const Quaternion& rhs) const
{
	Quaternion quat;
	Vector3 vec;
	float scalar;

	scalar = m_scalar*rhs.GetScalar() - m_vector.DotProduct(rhs.GetVector());

	vec[0] = m_scalar*rhs[0] + m_vector[0]*rhs.GetScalar() + m_vector[1]*rhs[2] - m_vector[2]*rhs[1];
	vec[1] = m_scalar*rhs[1] + m_vector[1] * rhs.GetScalar() + m_vector[2] * rhs[0] - m_vector[0] * rhs[2];
	vec[2] = m_scalar*rhs[2] + m_vector[2] * rhs.GetScalar() + m_vector[0] * rhs[1] - m_vector[1] * rhs[0];

	//vec = vec + m_vector*rhs.GetScalar() + rhs.GetVector()*m_scalar;

	quat.SetQuaternion(vec, scalar);

	return quat;
}

void Quaternion::SetQuaternion(float vx, float vy, float vz, float s)
{
	m_vector.SetVector(vx, vy, vz);
	m_scalar = s;
}

void Quaternion::SetQuaternion(const Vector3& vec, float s)
{
	m_vector = vec;
	m_scalar = s;
}

float Quaternion::Norm()
{
	float lengthSqr = 0.0f;

	lengthSqr = this->Norm_Sqr();

	return sqrt(lengthSqr);
}

float Quaternion::Norm_Sqr() const
{
	return m_vector.Norm_Sqr() + (m_scalar*m_scalar);
}

void Quaternion::ConvertToRotationMatrix(float* rot) const
{
	if (rot == NULL)
		return;

	//float rotmat[16];
	float norm = Norm_Sqr();
	float s = (norm > 0.0f) ? (2.0f / norm) : 0.0f;

	float xs = m_vector[0] * s;
	float ys = (m_vector)[1] * s;
	float zs = (m_vector)[2] * s;
	float wxs = m_scalar*xs;
	float wys = m_scalar*ys;
	float wzs = m_scalar*zs;
	float xxs = (m_vector)[0] * xs;
	float xys = (m_vector)[0] * ys;
	float xzs = (m_vector)[0] * zs;
	float yys = (m_vector)[1] * ys;
	float yzs = (m_vector)[1] * zs;
	float zzs = (m_vector)[2] * zs;

	rot[0] = 1.0f - (yys + zzs);
	rot[1] = xys + wzs;
	rot[2] = xzs - wys;
	rot[3] = 0.0;

	rot[4] = xys - wzs;
	rot[5] = 1.0f - (xxs + zzs);
	rot[6] = yzs + wxs;
	rot[7] = 0.0;

	rot[8] = xzs + wys;
	rot[9] = yzs - wxs;
	rot[10] = 1.0f - (xxs + yys);
	rot[11] = 0.0f;

	rot[12] = rot[13] = rot[14] = 0.0f;
	rot[15] = 1.0f;
}