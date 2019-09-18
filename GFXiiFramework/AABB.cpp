#include "AABB.h"
#include <iostream>

bool AABB::PointIsBetweenPoints(float point, float minPoint, float maxPoint)
{
	return (point >= minPoint && point <= maxPoint);
}

AABB::AABB(float lowX, float highX, float lowY, float highY, float lowZ, float highZ)
{
	m_maxX = highX;
	m_maxY = highY;
	m_maxZ = highZ;

	m_minX = lowX;
	m_minY = lowY;
	m_minZ = lowZ;
}

bool AABB::Intersects(AABB other)
{
	if (PointIsBetweenPoints(other.m_maxX, m_minX, m_maxX) || PointIsBetweenPoints(other.m_minX, m_minX, m_maxX))
	{
		//std::cout << "X is same" << std::endl;
		if (PointIsBetweenPoints(other.m_maxY, m_minY, m_maxY) || PointIsBetweenPoints(other.m_minY, m_minY, m_maxY))
		{
			//std::cout << "Y is same" << std::endl;
			if (PointIsBetweenPoints(other.m_maxZ, m_minZ, m_maxZ) || PointIsBetweenPoints(other.m_minZ, m_minZ, m_maxZ))
			{
				//std::cout << "Z is same" << std::endl;
				return true;
			}
		}
	}
	return false;
}

void AABB::DebugPrint()
{
	std::cout << m_minX << "," << m_maxX << "     " << m_minY << "," << m_maxY << "     " << m_minZ  << "," << m_maxZ << std::endl;
}

AABB AABB::operator*(const Matrix4x4 & rhs)
{
	Vector4 min = Vector4(m_minX, m_minY, m_minZ);
	Vector4 max = Vector4(m_maxX, m_maxY, m_maxZ);

	min = rhs * min;
	max = rhs * max;

	return AABB(min[0], max[0], min[1], max[1], min[2], max[2]);
}

AABB AABB::operator+(const Vector4& rhs)
{
	Vector4 min = Vector4(m_minX, m_minY, m_minZ);
	Vector4 max = Vector4(m_maxX, m_maxY, m_maxZ);

	min = min + rhs;
	max = max + rhs;

	return AABB(min[0], max[0], min[1], max[1], min[2], max[2]);
}