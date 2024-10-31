#include "stdafx.h"
#include "CharacterChoice1.h"
#include "Player.h"
#include "SpriteGo.h"
#include "Choice.h"

CharacterChoice1::CharacterChoice1()
	:Scene(SceneIds::Choice1)
{
}

void CharacterChoice1::Init()
{
	GameObject* obj = AddGo(new SpriteGo("graphics/background.png"));
	obj->sortingLayer = SortingLayers::Background;
	obj->sortingOrder = -1;
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });

	player1 = AddGo(new Player("graphics/player.png", "player"));
	player2 = AddGo(new Player("graphics/player2.png", "player2"));
	choice = AddGo(new Choice("graphics/choice.png", "choice"));

	Scene::Init();

	player1->SetPosition({ 1920.f / 4.f - 300, 800.f });
	player2->SetPosition({ ((1920.f / 4.f) * 3.f) - 300 , 800.f });

	auto choicepos = player1->GetPosition();
	choicepos.y = player1->GetPosition().y + 100.f;
	choice->SetPosition(choicepos);
	auto choiceSide = player1->GetSide();
	choice->SetSide(choiceSide);
}

void CharacterChoice1::Enter()
{
	TEXTURE_MGR.Load("graphics/background.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/choice.png");

	Scene::Enter();
}

void CharacterChoice1::Exit()
{
	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/background.png");
	TEXTURE_MGR.Unload("graphics/player.png");
	TEXTURE_MGR.Unload("graphics/choice.png");
}

void CharacterChoice1::Update(float dt)
{
	Scene::Update(dt);

	if (choice->GetSide() == Sides::Left)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			SCENE_MGR.ChangeScene(SceneIds::Dev1);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			choice->SetSide(Sides::Right);
		}
			auto choicepos = player1->GetPosition();
			choicepos.y = player1->GetPosition().y - 350.f;
			choice->SetPosition(choicepos);
	}

	if (choice->GetSide() == Sides::Right)
	{

		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			SCENE_MGR.ChangeScene(SceneIds::Dev1);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			choice->SetSide(Sides::Left);
		}
			auto choicepos = player2->GetPosition();
			choicepos.y = player2->GetPosition().y - 350.f;
			choice->SetPosition(choicepos);
	}
}

void CharacterChoice1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void CharacterChoice1::SetMainMessage(const std::string& msg)
{
}
