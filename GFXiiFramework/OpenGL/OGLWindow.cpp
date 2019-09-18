#include "OGLWindow.h"
#include "Resource.h"
#include "Matrix4x4.h"
#include "Vector4.h"
#include "GLEW/include/glew.h"

#include "SkyBox.h"
#include <iostream>

OGLWindow::OGLWindow() {}

OGLWindow::~OGLWindow()
{
	delete m_shader;

	DestroyOGLContext();
}

OGLWindow::OGLWindow(HINSTANCE hInstance, int width, int height)
{
	//InitWindow(hInstance, width, height);
}

HGLRC OGLWindow::CreateOGLContext(HDC hdc)
{
	unsigned int pixelformat;
	HGLRC hglrc;

	static PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Support Window
		PFD_SUPPORT_OPENGL |						// Format Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request RGBA Format
		32,											// Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits mask
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// Z-Buffer depth
		0,											// Stencil Buffer
		0,											// Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(pixelformat=ChoosePixelFormat(hdc,&pfd)))
	{
		return 0;
	}

	if(!SetPixelFormat(hdc,pixelformat,&pfd))
	{
		return 0;
	}

	if (!(hglrc=wglCreateContext(hdc)))
	{
		return 0;
	}

	if(!wglMakeCurrent(hdc,hglrc))
	{
		return 0;
	}

	return hglrc;
}

void OGLWindow::DestroyRenderWindow()
{
	DestroyWindow( m_hwnd );

	m_hwnd = NULL;
	m_hdc = NULL;
}

BOOL OGLWindow::DestroyOGLContext()
{

	glDeleteSamplers( 1, (GLuint*)(&m_texDefaultSampler) );

	if ( m_hglrc )
	{
		wglMakeCurrent( NULL, NULL );
		wglDeleteContext( m_hglrc );
		m_hglrc = NULL;
	}
	
	if ( !ReleaseDC ( m_hwnd, m_hdc ) )
		return FALSE;

	return TRUE;
}

BOOL OGLWindow::InitWindow(HINSTANCE hInstance, int width, int height)
{
	m_hwnd = CreateWindowEx( WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		L"RenderWindow", L"OGLWindow", WS_OVERLAPPEDWINDOW|WS_CLIPSIBLINGS|WS_CLIPCHILDREN,
		0, 0, width, height, NULL, NULL, hInstance, NULL);

	if ( ! m_hwnd )
		return FALSE;

	m_hdc = GetDC( m_hwnd );

	if ( !(m_hglrc = CreateOGLContext( m_hdc )) )
		return FALSE;

	glewInit();

	InitOGLState();

	m_width = width;
	m_height = height;

	m_scene = Scene();
	m_scene.SetRoot(m_builder.LoadDefaultScene());
	m_scene.SetSkyBox(m_builder.LoadDefaultSkyBox());

	return TRUE;
}

void OGLWindow::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	CameraNode* camera = m_scene.GetActiveCamera();
	if (camera == NULL)
	{
		std::cout << "Camera was not found in the scene!" << std::endl;
		return;
	}

	camera->SetProjectionMatrix(90.0f, ((float)m_width / (float)m_height), 1.0f, 5000.0f);

	glUniformMatrix4fv(m_uniform_view, 1, GL_TRUE, (camera->GetViewMatrix()).ToPtr());
	glUniformMatrix4fv(m_uniform_projection, 1, GL_FALSE, camera->GetProjectionMatrix().ToPtr());

	glUniform4f(m_uniform_lightpos, -2000, 2000, -2000, 1);

	//Render the gameobjects
	m_shader->ActivateShaderProgram();

	std::vector<SceneNode*> renderables = m_scene.GetRenderables();
	for (SceneNode* node : renderables)
	{
		Matrix4x4 modelview = (camera->GetViewMatrix()) * node->GetWorldTransform();

		glUniformMatrix4fv(m_uniform_modelview, 1, GL_TRUE, modelview.ToPtr());
		glUniformMatrix4fv(m_uniform_model, 1, GL_TRUE, node->GetWorldTransform().ToPtr());
		glBindSampler(0, m_texDefaultSampler);

		static_cast<RenderableNode*>(node)->Render();
	}

	//Render the skybox
	m_skyboxShader->ActivateShaderProgram();

	RenderableNode* skybox = m_scene.GetSkyBox();

	Matrix4x4 modelview = skybox->GetWorldTransform() * camera->Transform()->GetRotation().Inverse();
	glUniformMatrix4fv(m_uniform_modelview, 1, GL_TRUE, modelview.ToPtr());
	glUniformMatrix4fv(m_uniform_model, 1, GL_TRUE, skybox->GetWorldTransform().ToPtr());
	glBindSampler(0, m_texDefaultSampler);

	skybox->Render();

	SwapBuffers(m_hdc);

	return;
}

void OGLWindow::Update()
{
	m_scene.Update();
	m_scene.CheckCollisions();
}

void OGLWindow::Resize(int width, int height)
{
	m_width = width;
	m_height = height;

	glViewport( 0, 0, width, height );

	return;
}

void OGLWindow::InitOGLState()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glEnable(GL_CULL_FACE);

	//Initialise Skybox Shader
	m_skyboxShader = new OGLShaderProgram();

	m_skyboxShader->CreateShaderProgram();
	m_skyboxShader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/skybox.vert", SHADER_VERTEX);
	m_skyboxShader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/skybox.frag", SHADER_FRAGMENT);

	m_skyboxShader->BindAttributeLocation(0, "position");
	m_skyboxShader->BindAttributeLocation(2, "inUV");

	glBindFragDataLocation(m_skyboxShader->GetProgramHandle(), 0, "outFrag");

	m_skyboxShader->BuildShaderProgram();
	m_skyboxShader->ActivateShaderProgram();

	m_uniform_modelview = glGetUniformLocation(m_skyboxShader->GetProgramHandle(), "modelview");
	m_uniform_projection = glGetUniformLocation(m_skyboxShader->GetProgramHandle(), "projection");

	glUniform1i(m_uniform_texture, 0);

	//Enable depth testing
	glEnable(GL_DEPTH_TEST);

	//Initialise OGL shader
	m_shader = new OGLShaderProgram();

	m_shader->CreateShaderProgram();
	m_shader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/basic.vert", SHADER_VERTEX);
	m_shader->AttachAndCompileShaderFromFile(L"../asset/shader/glsl/basic.frag", SHADER_FRAGMENT);

	m_shader->BindAttributeLocation( 0, "position" );
	m_shader->BindAttributeLocation( 1, "inNormal" );
	m_shader->BindAttributeLocation( 2, "inUV" );

	glBindFragDataLocation( m_shader->GetProgramHandle(), 0, "outFrag" );

	m_shader->BuildShaderProgram();
	m_shader->ActivateShaderProgram();

	m_uniform_modelview = glGetUniformLocation(m_shader->GetProgramHandle(), "modelview");
	m_uniform_projection = glGetUniformLocation(m_shader->GetProgramHandle(), "projection");
	m_uniform_texture = glGetUniformLocation(m_shader->GetProgramHandle(), "texColour");
	m_uniform_lightpos = glGetUniformLocation(m_shader->GetProgramHandle(), "lightpos");
	m_uniform_model = glGetUniformLocation(m_shader->GetProgramHandle(), "model");
	m_uniform_view = glGetUniformLocation(m_shader->GetProgramHandle(), "view");

	glUniform1i( m_uniform_texture, 0 );

	//Create a texture sampler
	glGenSamplers( 1, (GLuint*)(&m_texDefaultSampler) );
	
	glSamplerParameteri(m_texDefaultSampler , GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  
	glSamplerParameteri(m_texDefaultSampler , GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);  
	glSamplerParameteri(m_texDefaultSampler , GL_TEXTURE_MIN_FILTER , GL_LINEAR);  
	glSamplerParameteri(m_texDefaultSampler , GL_TEXTURE_MAG_FILTER , GL_LINEAR);
}

BOOL OGLWindow::MouseLBDown ( int x, int y )
{
	return TRUE;
}

BOOL OGLWindow::MouseLBUp ( int x, int y )
{
	return TRUE;
}

BOOL OGLWindow::MouseMove ( int x, int y )
{
	return TRUE;
}
