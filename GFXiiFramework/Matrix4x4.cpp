#include <memory.h>
#include <math.h>
#include "Vector4.h"
#include "Matrix4x4.h"
#include "GLM\include\mat4x4.hpp"

#define PI_DIV_180 0.01745329251994329576923690768489f

Matrix4x4::Matrix4x4()
{
	SetIdentity();
}

Matrix4x4::Matrix4x4(const Matrix4x4& rhs)
{
	size_t matrix_size = sizeof(m_element);

	memcpy_s((&m_element[0][0]), matrix_size, rhs.ToPtr(), matrix_size);
}

Matrix4x4::~Matrix4x4()
{
}

const float* Matrix4x4::ToPtr() const
{
	return &(m_element[0][0]);
}

Matrix4x4 Matrix4x4::Inverse() const
{
	Matrix4x4 inverted;
	glm::mat4x4 val;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			val[i][j] = m_element[i][j];
		}
	}

	val = glm::inverse(val);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			inverted.m_element[i][j] = val[i][j];
		}
	}

	return inverted;
}

void Matrix4x4::SetZero()
{
	memset(&m_element, 0, sizeof(m_element));
}

void Matrix4x4::SetIdentity()
{
	SetZero();
	m_element[0][0] = m_element[1][1] = m_element[2][2] = m_element[3][3] = 1.0f;
}

void Matrix4x4::SetMatrix(float* rhs)
{
	m_element[0][0] = rhs[0];
	m_element[1][0] = rhs[1];
	m_element[2][0] = rhs[2];
	m_element[3][0] = rhs[3];

	m_element[0][1] = rhs[4];
	m_element[1][1] = rhs[5];
	m_element[2][1] = rhs[6];
	m_element[3][1] = rhs[7];

	m_element[0][2] = rhs[8];
	m_element[1][2] = rhs[9];
	m_element[2][2] = rhs[10];
	m_element[3][2] = rhs[11];

	m_element[0][3] = rhs[12];
	m_element[1][3] = rhs[13];
	m_element[2][3] = rhs[14];
	m_element[3][3] = rhs[15];

}

Matrix4x4 Matrix4x4::operator* (const Matrix4x4& rhs) const
{
	Matrix4x4 result;

	for (int r = 0; r < 4; r++)
		for (int c = 0; c < 4; c++)
			result.m_element[r][c] = m_element[r][0] * rhs.m_element[0][c]
			+ m_element[r][1] * rhs.m_element[1][c]
			+ m_element[r][2] * rhs.m_element[2][c]
			+ m_element[r][3] * rhs.m_element[3][c];

	return result;
}

Vector4 Matrix4x4::operator* (const Vector4& rhs) const
{
	Vector4 result;

	result = rhs;

	for (int row = 0; row < 4; row++)
	{
		Vector4 rowVector = Vector4(m_element[0][row], m_element[1][row], m_element[2][row], m_element[3][row]);
		result[row] = rowVector.DotProduct(rhs);
	}

	return result;
}

void Matrix4x4::SetRotationXAxis(float degrees)
{
	SetIdentity();

	float radian = degrees*PI_DIV_180;

	m_element[1][1] = cosf(radian);
	m_element[1][2] = -sinf(radian);
	m_element[2][1] = sinf(radian);
	m_element[2][2] = cosf(radian);
}

void Matrix4x4::SetRotationYAxis(float degrees)
{
	SetIdentity();

	float radian = degrees*PI_DIV_180;

	m_element[0][0] = cosf(radian);
	m_element[0][2] = sinf(radian);
	m_element[2][0] = -sinf(radian);
	m_element[2][2] = cosf(radian);

}

void Matrix4x4::SetRotationZAxis(float degrees)
{
	SetIdentity();

	float radian = degrees*PI_DIV_180;

	m_element[0][0] = cosf(radian);
	m_element[0][1] = -sinf(radian);
	m_element[1][0] = sinf(radian);
	m_element[1][1] = cosf(radian);
}

void Matrix4x4::SetTranslate(const Vector4& tvec)
{
	SetIdentity();

	m_element[0][3] = tvec[0];
	m_element[1][3] = tvec[1];
	m_element[2][3] = tvec[2];
}

void Matrix4x4::SetScale(float sx, float sy, float sz)
{
	SetIdentity();

	m_element[0][0] = sx;
	m_element[1][1] = sy;
	m_element[2][2] = sz;
}

bool Matrix4x4::IsZero()
{
	return
		m_element[0][0] ==
		m_element[0][1] ==
		m_element[0][2] ==
		m_element[0][3] ==
		m_element[1][0] ==
		m_element[1][1] ==
		m_element[1][2] ==
		m_element[1][3] ==
		m_element[2][0] ==
		m_element[2][1] ==
		m_element[2][2] ==
		m_element[2][3] ==
		m_element[3][0] ==
		m_element[3][1] ==
		m_element[3][2] ==
		m_element[3][3] == 0;
}

void Matrix4x4::SetPerspective(float fovy, float aspect_ratio, float zNear, float zFar)
{
	float radian = fovy*PI_DIV_180;
	float tan_fovy = tanf(radian*0.5f);

	SetZero();

	m_element[0][0] = 1.0f / (aspect_ratio*tan_fovy);
	m_element[1][1] = 1.0f / tan_fovy;
	m_element[2][2] = -(zFar + zNear) / (zFar - zNear);
	m_element[2][3] = -1.0f;
	m_element[3][2] = -(2.0f*zFar*zNear) / (zFar - zNear);
}

void Matrix4x4::SetViewMatrix(const Vector4& camera_position, const Vector4& view_vector, const Vector4& up_vector)
{
	//Set this matrix as a view matrix based on the given camera_position, view_vector and up_vector
	//Obtain the orthonormal vectors we need
	Vector4 view = view_vector;
	view.Normalise();

	Vector4 up = up_vector;
	up.Normalise();

	Vector4 right = view.CrossProduct(up);
	right.Normalise();

	//Create the view matrix
	SetZero();

	m_element[0][0] = right[0];
	m_element[0][1] = right[1];
	m_element[0][2] = right[2];

	m_element[1][0] = up[0];
	m_element[1][1] = up[1];
	m_element[1][2] = up[2];

	m_element[2][0] = -view[0];
	m_element[2][1] = -view[1];
	m_element[2][2] = -view[2];

	m_element[0][3] = camera_position[0];
	m_element[1][3] = camera_position[1];
	m_element[2][3] = camera_position[2];
	m_element[3][3] = 1.0f;
}
