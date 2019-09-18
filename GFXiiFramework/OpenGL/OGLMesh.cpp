#include <Windows.h>
#include "OGLMesh.h"
#include "../Triangle.h"
#include "../OBJFileReader.h"
#include "OGLTexture.h"
#include "GLEW/include/glew.h"

void OGLMesh::CalculateSize(Triangle* mesh, int num)
{
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			float x = mesh[i].m_vertices[j].m_position[0];
			float y = mesh[i].m_vertices[j].m_position[1];
			float z = mesh[i].m_vertices[j].m_position[2];

			if (x > m_maxX)
			{
				m_maxX = x;
			}
			else if (x < m_minX)
			{
				m_minX = x;
			}

			if (y > m_maxY)
			{
				m_maxY = y;
			}
			else if (y < m_minY)
			{
				m_minY = y;
			}

			if (z > m_maxZ)
			{
				m_maxZ = z;
			}
			else if (z < m_minZ)
			{
				m_minZ = z;
			}
		}
	}
}

OGLMesh::OGLMesh()
{

}

OGLMesh::OGLMesh(LPCWSTR filename)
{
	LoadAndBuildMeshFromOBJFile(filename);
}

OGLMesh::~OGLMesh()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo_verts);
}

void OGLMesh::Render()
{
	unsigned int texHandle = dynamic_cast<OGLTexture*>(m_tex)->m_syshandle;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texHandle);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
	glDrawArrays(GL_TRIANGLES, 0, m_numtriangles*3);

	glBindVertexArray(0);
}

void OGLMesh::LoadAndBuildMeshFromOBJFile(LPCWSTR filename)
{
	Triangle* mesh;

	m_numtriangles = importOBJMesh(filename, &mesh);
	
	int offset = sizeof(Vector3);
	int stride = sizeof(Vertex);

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo_verts);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo_verts);
	glBufferData(GL_ARRAY_BUFFER, 3 * m_numtriangles * sizeof(Vertex), &(mesh[0].m_vertices[0].m_position[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(NULL + offset));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(NULL + 2*offset));
	glEnableVertexAttribArray(2);
			
	glBindVertexArray(0);

	CalculateSize(mesh, m_numtriangles);

	delete[] mesh;
}