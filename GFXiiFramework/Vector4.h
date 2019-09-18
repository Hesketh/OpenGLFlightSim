#pragma once
#include "Vector3.h"
//Created for Graphics I and II
//Author: Minsi Chen

class Vector4
{
private:
	float		m_element[4];

public:
	Vector4()
	{
		m_element[0] = 0.0f;
		m_element[1] = 0.0f;
		m_element[2] = 0.0f;
		m_element[3] = 1.0f;
	}
	
	Vector4(float x, float y, float z, float w = 1.0f)
	{
		m_element[0] = x; m_element[1] = y; m_element[2] = z;
		m_element[3] = w;
	}

	Vector4(Vector3 vec, float w = 1.0f)
	{
		m_element[0] = vec[0]; m_element[1] = vec[1]; m_element[2] = vec[2];
		m_element[3] = w;
	}

	Vector4(const Vector4& rhs);

	virtual ~Vector4() { ; }

	//accessor for each vector component
	//e.g. Vector4 vec; 
	//		vec[0]
	float operator [] (const int i) const;
	float& operator [] (const int i);
	
	//some common vector operators
	Vector4 operator + (const Vector4& rhs) const;
	Vector4 operator - (const Vector4& rhs) const;
	Vector4& operator = (const Vector4& rhs);
	Vector4 operator * (const Vector4& rhs) const;
	Vector4 operator * (float scale) const;

	float Length()	const;
	float LengthSqr() const;
	void Normalise();

	float DotProduct(const Vector4& rhs) const;
	Vector4 CrossProduct(const Vector4& rhs) const;
	void SetZero();
	inline void SetVector(float x, float y, float z, float w) { m_element[0] = x; m_element[1] = y; m_element[2] = z; m_element[3] = w; }

};

