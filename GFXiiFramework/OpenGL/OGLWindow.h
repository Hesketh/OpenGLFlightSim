#pragma once

#include "RenderWindow.h"
#include "OGLCube.h"
#include "OGLMesh.h"
#include "OGLShader.h"
#include "OGLTexture.h"

#include "OGLResourceLoader.h"
#include "Transformation.h"
#include "Vector4.h"

#include "SceneBuilder.h"
#include "Scene.h"
#include "RenderableNode.h"
#include "SceneNode.h"
#include "CameraNode.h"

class OGLWindow : public RenderWindow
{
	private:
		HDC			m_hdc;				//handle to a device context
		HGLRC		m_hglrc;			//handle to a gl rendering context

		int			m_width;
		int			m_height;

		SceneBuilder	m_builder;	//TODO: For some reason we have to build the scene in the window...
		Scene			m_scene;

		//Declear an OGL shader program
		OGLShaderProgram		*m_shader;
		OGLShaderProgram		*m_skyboxShader;
		int						m_uniform_modelview;
		int						m_uniform_model;
		int						m_uniform_projection;
		int                     m_uniform_texture;
		int						m_uniform_view;
		int						m_texDefaultSampler;
		int						m_uniform_lightpos;

protected:

		HGLRC CreateOGLContext (HDC hdc);
		BOOL DestroyOGLContext();
		void InitOGLState();

	public:
					OGLWindow();
					OGLWindow(HINSTANCE hInstance, int width, int height);
					~OGLWindow();
		
		BOOL		InitWindow(HINSTANCE hInstance, int width, int height);

		void		Render();
		void		Update();
		void		Resize( int width, int height );
		void		DestroyRenderWindow();

		BOOL		MouseLBDown ( int x, int y );
		BOOL		MouseLBUp ( int x, int y );
		BOOL		MouseMove ( int x, int y );
};
