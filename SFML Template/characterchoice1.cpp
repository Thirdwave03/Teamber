#include "stdafx.h"
#include "CharacterChoice1.h"
#include "Player.h"
#include "SpriteGo.h"
#include "Choice.h"
#include "TextGo.h"

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
	Select = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Ui Score"));


	Scene::Init();

	player1->SetPosition({ 1920.f / 4.f - 300, 800.f });
	player2->SetPosition({ ((1920.f / 4.f) * 3.f) - 300 , 800.f });

	auto choicepos = player1->GetPosition();
	choicepos.y = player1->GetPosition().y + 100.f;
	choice->SetPosition(choicepos);
	auto choiceSide = player1->GetSide();
	choice->SetSide(choiceSide);

	Select->text.setString("Choose the character you want");
	Select->SetOrigin(Origins::MC);
	Select->text.setCharacterSize(75);
	Select->text.setFillColor(sf::Color::Blue);
	Select->SetPosition({ 1920.f / 2.f, 100.f });

}

void CharacterChoice1::Enter()
{
	TEXTURE_MGR.Load("graphics/background.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/player2.png");
	TEXTURE_MGR.Load("graphics/choice.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");

	Scene::Enter();
}

void CharacterChoice1::Exit()
{
	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/background.png");
	TEXTURE_MGR.Unload("graphics/player.png");
	TEXTURE_MGR.Unload("graphics/player2.png");
	TEXTURE_MGR.Unload("graphics/choice.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
}

void CharacterChoice1::Update(float dt)
{
	Scene::Update(dt);
	SceneMgr::Instance().setSide(choice->GetSide());
	if (choice->GetSide() == Sides::Left)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::D))
		{
			choice->SetSide(Sides::Right);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			SCENE_MGR.ChangeScene(SceneIds::Dev1);
		}
			auto choicepos = player1->GetPosition();
			choicepos.y = player1->GetPosition().y - 350.f;
			choice->SetPosition(choicepos);
	}

	if (choice->GetSide() == Sides::Right)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::A))
		{	
			choice->SetSide(Sides::Left);
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			SCENE_MGR.ChangeScene(SceneIds::Dev1);
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
