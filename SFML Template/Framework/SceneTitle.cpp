#include "stdafx.h"
#include "SceneTitle.h"
#include "SpriteGo.h"
#include "CloudGo.h"
#include "Tree.h"
#include "Player.h"
#include "TextGo.h"
#include "UiScore.h"
#include "UiTimebar.h"

SceneTitle::SceneTitle()
	:Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
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

	tree = AddGo(new Tree("Tree"));
	player = AddGo(new Player("graphics/player.png", "Player"));
	MainMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Rigth Message"));
	LeftMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Left Message"));
	RigthMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Rigth Message"));


	MainMsg->sortingLayer = SortingLayers::UI;
	LeftMsg->sortingLayer = SortingLayers::UI;
	RigthMsg->sortingLayer = SortingLayers::UI;

	Scene::Init();

	tree->SetPosition({ 1920 / 2, 880 });
	player->SetPosition({ 1920 / 2, 880 });
	MainMsg->text.setCharacterSize(100);
	MainMsg->text.setFillColor(sf::Color::Red);
	MainMsg->SetPosition({ 1920.f / 2.f, 100.f });
	SetMainMessage("Timber Game!");

	LeftMsg->text.setCharacterSize(70);
	LeftMsg->text.setFillColor(sf::Color::White);
	LeftMsg->SetPosition({ 1920.f / 4.f, 1080.f / 2.f });
	SetLeftMessage("If you want 1p,\n  press 'num1'");

	RigthMsg->text.setCharacterSize(70);
	RigthMsg->text.setFillColor(sf::Color::White);
	RigthMsg->SetPosition({ (1920.f / 4.f) * 3.f, 1080.f / 2.f });
	SetRightMessage("If you want 2p,\n  press 'num2'");
}

void SceneTitle::Enter()
{
	TEXTURE_MGR.Load("graphics/background.png");
	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/player.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	Scene::Enter();
}

void SceneTitle::Exit()
{
	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/background.png");
	TEXTURE_MGR.Unload("graphics/tree.png");
	TEXTURE_MGR.Unload("graphics/player.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev2);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneTitle::SetLeftMessage(const std::string& msg)
{
	LeftMsg->text.setString(msg);
	LeftMsg->SetOrigin(Origins::MC);
}

void SceneTitle::SetRightMessage(const std::string& msg)
{
	RigthMsg->text.setString(msg);
	RigthMsg->SetOrigin(Origins::MC);
}

void SceneTitle::SetMainMessage(const std::string& msg)
{
	MainMsg->text.setString(msg);
	MainMsg->SetOrigin(Origins::MC);
}
