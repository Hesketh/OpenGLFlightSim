#pragma once
#include "Matrix4x4.h"
#include "Vector4.h"

//axis alligned bounding box
class AABB
{
private:
	float m_minX, m_maxX;
	float m_minY, m_maxY;
	float m_minZ, m_maxZ;

	bool PointIsBetweenPoints(float point, float minPoint, float maxPoint);
public:
	AABB(float lowX, float highX, float lowY, float highY, float lowZ, float highZ);
	bool Intersects(AABB other);

	void DebugPrint();

	AABB operator*(const Matrix4x4& rhs);
	AABB operator+(const Vector4& rhs);
};