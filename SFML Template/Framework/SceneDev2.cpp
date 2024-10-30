#include "stdafx.h"
#include "SceneDev2.h"
#include "SpriteGo.h"
#include "CloudGo.h"
#include "Tree.h"
#include "Player.h"
#include "TextGo.h"
#include "UiScore.h"
#include "UiTimebar.h"

SceneDev2::SceneDev2() 
	: Scene(SceneIds::Dev2)
{

}

void SceneDev2::Init()
{
	std::cout << "SceneDev2::Init()" << std::endl;

	GameObject* obj = AddGo(new SpriteGo("graphics/background.png"));
	obj->sortingLayer = SortingLayers::Background;
	obj->sortingOrder = -1;
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });

	for (int i = 0; i < 3; ++i)
	{
		CloudGo* cloud = AddGo(new CloudGo("graphics/cloud.png"));
		cloud->sortingLayer = SortingLayers::Background;
		cloud->sortingOrder = 0;
	}

	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/axe.png");

	GameObject* tree1 = AddGo(new Tree("Tree"));
	tree1->sortingLayer = SortingLayers::Background;
	tree1->sortingOrder = -1;
	tree1->SetOrigin(Origins::MC);
	tree1->SetPosition({ 1920 / 4, 850 });

	GameObject* tree2 = AddGo(new Tree("Tree"));
	tree2->sortingLayer = SortingLayers::Background;
	tree2->sortingOrder = -1;
	tree2->SetOrigin(Origins::MC);
	tree2->SetPosition({ (1920 / 4) * 3, 850 });

	Scene::Init();
}

void SceneDev2::Enter()
{

	TEXTURE_MGR.Load("graphics/tree.png");


	TEXTURE_MGR.Load("graphics/player.png");

	Scene::Enter();
}

void SceneDev2::Exit()
{
	std::cout << "SceneDev2::Exit()" << std::endl;

	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/player.png");
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
