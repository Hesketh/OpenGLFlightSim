#include "SceneBuilder.h"
#include "Vector3.h"
#include "SkyBox.h"
#include "Plane.h"
#include "Camera.h"
#include "Collectable.h"
#include "AABB.h"



SceneBuilder::SceneBuilder() 
{
	//OGLResourceLoader()::Instance(). = new OGLResourceLoader();
}

SceneBuilder::~SceneBuilder() {}

//TEMP: This is to be replaced, a file specifying all of this is to be loaded from disk and the scene should be constructed from that
SceneNode* SceneBuilder::LoadDefaultScene()
{
	//Create the root node
	SceneNode* origin = new SceneNode();

	//Loading Mesh / Textures
	Renderable* houseMesh = static_cast<OGLMesh*>(static_cast<OGLResourceLoader*>(OGLResourceLoader::Instance())->GetResource(ResourceLoader::EResourceType::Mesh, "../asset/models/house.obj"));
	BaseTexture* houseTexture = static_cast<OGLTexture*>(static_cast<OGLResourceLoader*>(OGLResourceLoader::Instance())->GetResource(ResourceLoader::EResourceType::Texture, "../asset/texture/house_diffuse.tga"));
	houseMesh->SetTexture(houseTexture);

	Renderable* planeMesh = static_cast<OGLMesh*>(static_cast<OGLResourceLoader*>(OGLResourceLoader::Instance())->GetResource(ResourceLoader::EResourceType::Mesh, "../asset/models/space_frigate.obj"));
	BaseTexture* planeTexture = static_cast<OGLTexture*>(static_cast<OGLResourceLoader*>(OGLResourceLoader::Instance())->GetResource(ResourceLoader::EResourceType::Texture, "../asset/texture/space_frigate_color.tga"));
	planeMesh->SetTexture(planeTexture);

	Renderable* mountainMesh = static_cast<OGLMesh*>(static_cast<OGLResourceLoader*>(OGLResourceLoader::Instance())->GetResource(ResourceLoader::EResourceType::Mesh, "../asset/models/mountain.obj"));
	BaseTexture* mountainTexture = static_cast<OGLTexture*>(static_cast<OGLResourceLoader*>(OGLResourceLoader::Instance())->GetResource(ResourceLoader::EResourceType::Texture, "../asset/texture/mountain_colour.tga"));
	mountainMesh->SetTexture(mountainTexture);

	Renderable* coinMesh = static_cast<OGLMesh*>(static_cast<OGLResourceLoader*>(OGLResourceLoader::Instance())->GetResource(ResourceLoader::EResourceType::Mesh, "../asset/models/coin.obj"));
	BaseTexture* coinTexture = static_cast<OGLTexture*>(static_cast<OGLResourceLoader*>(OGLResourceLoader::Instance())->GetResource(ResourceLoader::EResourceType::Texture, "../asset/texture/coin_diffuse.tga"));
	coinMesh->SetTexture(coinTexture);

	//Creating the Nodes
	RenderableNode* terrain = new RenderableNode(origin, mountainMesh);
	terrain->Transform()->SetPosition(0, -1000, 0);
	terrain->Transform()->SetScale(20, 20, 20);
	terrain->SetCollisionBox(0, 0, 0, 0, 0, 0); //disable terrain collision for the moment

	//Houses
	RenderableNode* house = new RenderableNode(origin, houseMesh);
	house->Transform()->SetPosition(0,-480,0);
	house->Transform()->SetRotation(0,0,-0.35);
	house->Transform()->SetScale(10,10,10);
	house->SetCollisionBox(0,0,0,0,0,0); //disable collision with houses for the moment
	
	RenderableNode* house2 = new RenderableNode(origin, houseMesh);
	house2->Transform()->SetPosition(750, -600, 750);
	house2->Transform()->SetRotation(0,0,0);
	house2->Transform()->SetScale(100, 100, 100);
	house2->SetCollisionBox(0,0,0,0,0,0);

	RenderableNode* house3 = new RenderableNode(origin, houseMesh);
	house3->Transform()->SetPosition(-250, -470, -800);
	house3->Transform()->SetRotation(1.3,0,0);
	house3->Transform()->SetScale(10, 10, 10);
	house3->SetCollisionBox(0, 0, 0, 0, 0, 0);

	//Coins
	Collectable* coin = new Collectable(origin, coinMesh);
	coin->Transform()->SetPosition(1000, -250, 1000);

	Collectable* coin2 = new Collectable(origin, coinMesh);
	coin2->Transform()->SetPosition(-1000, 250, -1000);

	Collectable* coin3 = new Collectable(origin, coinMesh);
	coin3->Transform()->SetPosition(1000, 250, -1000);

	Collectable* coin4 = new Collectable(origin, coinMesh);
	coin4->Transform()->SetPosition(-1000, -250, 1000);

	Collectable* coin5 = new Collectable(origin, coinMesh);
	coin5->Transform()->SetPosition(500, 250, 500);

	Collectable* coin6 = new Collectable(origin, coinMesh);
	coin6->Transform()->SetPosition(-500, 250, -500);

	Collectable* coin7 = new Collectable(origin, coinMesh);
	coin7->Transform()->SetPosition(500, 250, -500);

	Collectable* coin8 = new Collectable(origin, coinMesh);
	coin8->Transform()->SetPosition(-500, -250, 500);

	Plane* plane = new Plane(origin, planeMesh);
	//plane->Transform()->SetScale(0.1,0.1,0.1);
	plane->Transform()->SetRotation(0, 0, 0);
	plane->Transform()->Translate(0, 0, -100);

	//Camera
	Camera* camera = new Camera(origin, plane);

	return origin;
}

RenderableNode* SceneBuilder::LoadDefaultSkyBox()
{
	SkyBox* skyboxMesh = static_cast<SkyBox*>(static_cast<OGLResourceLoader*>(OGLResourceLoader::Instance())->GetResource(ResourceLoader::EResourceType::Skybox, "default"));

	RenderableNode* skybox = new RenderableNode(nullptr, skyboxMesh);
	skybox->Transform()->SetPosition(0,0,0);
	skybox->Transform()->SetScale(5000, 5000, 5000);

	return skybox;
}