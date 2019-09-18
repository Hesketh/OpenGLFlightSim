#pragma once

#include <Windows.h>
#include "../Renderable.h"
#include "../Triangle.h"


class OGLMesh : public Renderable
{
private:
	unsigned int	m_vao;
	unsigned int	m_vbo_verts;
	int				m_numtriangles;

	float			m_minX, m_maxX;
	float			m_minY, m_maxY;
	float			m_minZ, m_maxZ;

	void			CalculateSize(Triangle* mesh, int num);
public:
	OGLMesh();
	OGLMesh(LPCWSTR filename);
	~OGLMesh();

	inline float GetMaxX() { return m_maxX; }
	inline float GetMinX() { return m_minX; }
	inline float GetMaxY() { return m_maxY; }
	inline float GetMinY() { return m_minY; }
	inline float GetMaxZ() { return m_maxZ; }
	inline float GetMinZ() { return m_minZ; }

	void LoadAndBuildMeshFromOBJFile(LPCWSTR filename);

	void Render();

};