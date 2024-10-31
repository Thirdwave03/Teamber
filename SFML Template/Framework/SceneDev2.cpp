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
	TEXTURE_MGR.Load("graphics/player2.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/axe.png");

	tree1 = AddGo(new Tree("Tree"));
	tree2 = AddGo(new Tree("Tree2"));

	player1 = AddGo(new Player("graphics/player.png", "Player"));
	player2 = AddGo(new Player("graphics/player2.png", "Player2"));

	centerMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Center Message"));
	centerMsg->sortingLayer = SortingLayers::UI;

	uiScore1 = AddGo(new UiScore("fonts/KOMIKAP_.ttf", "Ui Score"));
	uiTimer1 = AddGo(new UiTimebar("Ui Timer"));

	uiScore2 = AddGo(new UiScore("fonts/KOMIKAP_.ttf", "Ui Score"));
	uiTimer2 = AddGo(new UiTimebar("Ui Timer"));

	Scene::Init();

	tree1->SetPosition({ 1920 / 4, 850 });
	tree2->SetPosition({ (1920 / 4) + 960 , 850 });

	player1->SetPosition({ 1920 / 4, 850 });
	player2->SetPosition({ (1920 / 4) + 960 , 850 });

	centerMsg->text.setCharacterSize(100);
	centerMsg->text.setOutlineThickness(3);
	centerMsg->text.setOutlineColor(sf::Color::Black);
	centerMsg->text.setFillColor(sf::Color::White);
	centerMsg->SetPosition({ 1920.f / 2.f, 1080.f / 2.f });

	uiScore1->text.setCharacterSize(75);
	uiScore1->text.setOutlineThickness(3);
	uiScore1->text.setOutlineColor(sf::Color::Black);
	uiScore1->text.setFillColor(sf::Color::White);
	uiScore1->SetPosition({ 30.f, 30.f });

	uiScore2->text.setCharacterSize(75);
	uiScore2->text.setOutlineThickness(3);
	uiScore2->text.setOutlineColor(sf::Color::Black);
	uiScore2->text.setFillColor(sf::Color::White);
	uiScore2->SetPosition({ 1920 / 2 + 30.f, 30.f });

	uiTimer1->Set({ 500.f, 100.f }, sf::Color::Red);
	uiTimer1->SetOrigin(Origins::ML);
	uiTimer1->SetPosition({ 1920.f / 4.f - 250.f, 1080.f - 100.f });

	uiTimer2->Set({ 500.f, 100.f }, sf::Color::Red);
	uiTimer2->SetOrigin(Origins::ML);
	uiTimer2->SetPosition({ 1920.f / 4.f + 710.f, 1080.f - 100.f });

	Scene::Init();
}

void SceneDev2::Enter()
{

	TEXTURE_MGR.Load("graphics/background.png");
	TEXTURE_MGR.Load("graphics/cloud.png");
	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/log.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/player2.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/axe.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Load("sound/chop.wav");
	SOUNDBUFFER_MGR.Load(sbIdDeath);
	SOUNDBUFFER_MGR.Load(sbIdTimeOut);

	sfxDeath.setBuffer(SOUNDBUFFER_MGR.Get(sbIdDeath));
	sfxTimeOut.setBuffer(SOUNDBUFFER_MGR.Get(sbIdTimeOut));

	player1->SetSceneGame2(this);

	player2->SetSceneGame2(this);
	Scene::Enter();

	SetStatus(Status::Awake);
}

void SceneDev2::Exit()
{
	std::cout << "SceneDev1::Exit()" << std::endl;

	player1->SetSceneGame(nullptr);
	tree1->ClearEffectLog();

	player2->SetSceneGame(nullptr);
	tree2->ClearEffectLog();

	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/cloud.png");
	TEXTURE_MGR.Unload("graphics/background.png");
	TEXTURE_MGR.Unload("graphics/tree.png");
	TEXTURE_MGR.Unload("graphics/branch.png");
	TEXTURE_MGR.Unload("graphics/log.png");
	TEXTURE_MGR.Unload("graphics/player.png");
	TEXTURE_MGR.Unload("graphics/player2.png");
	TEXTURE_MGR.Unload("graphics/rip.png");
	TEXTURE_MGR.Unload("graphics/axe.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Unload("sound/chop.wav");
	SOUNDBUFFER_MGR.Unload("sound/death.wav");
	SOUNDBUFFER_MGR.Unload("sound/out_of_time.wav");
}

void SceneDev2::Update(float dt)
{
	Scene::Update(dt);

	switch (currentStatus)
	{
	case SceneDev2::Status::Awake:
		UpdateAwake(dt);
		break;
	case SceneDev2::Status::Game:
		UpdateGame(dt);
		break;
	case SceneDev2::Status::GameOver:
		UpdateGameOver(dt);
		break;
	case SceneDev2::Status::Pause:
		UpdatePause(dt);
		break;
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		SCENE_MGR.ChangeScene(SceneIds::Dev1);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}
}

void SceneDev2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneDev2::SetCenterMessage(const std::string& msg)
{
	centerMsg->text.setString(msg);
	centerMsg->SetOrigin(Origins::MC);
}

void SceneDev2::SetVisibleCenterMessage(bool visible)
{
	centerMsg->SetActive(visible);
}

void SceneDev2::SetScore(int playernumber, int score)
{
	if (playernumber == 1)
	{
		this->score1 = score;
		uiScore1->SetScore(this->score1);
	}
	if (playernumber == 2)
	{
		this->score2 = score;
		uiScore2->SetScore(this->score2);
	}
}

void SceneDev2::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case SceneDev2::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("Press Enter To Start!!");
		score1 = 0;
		timer1 = gameTime;
		SetScore(1, score1);
		uiTimer1->SetValue(1.f);

		score2 = 0;
		timer2 = gameTime;
		SetScore(2, score2);
		uiTimer2->SetValue(1.f);
		break;
	case SceneDev2::Status::Game:
		if (prevStatus == Status::GameOver)
		{
			score1 = 0;
			timer1 = gameTime;

			SetScore(1, score1);
			uiTimer1->SetValue(1.f);

			player1->Reset();
			tree1->Reset();

			score2 = 0;
			timer2 = gameTime;

			SetScore(2, score1);
			uiTimer2->SetValue(1.f);

			player2->Reset();
			tree2->Reset();
		}
		FRAMEWORK.SetTimeScale(1.f);
		SetVisibleCenterMessage(false);
		break;
	case SceneDev2::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		break;
	case SceneDev2::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("PAUSE! ESC TO RESUME!");
		break;
	}
}

void SceneDev2::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev2::UpdateGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Pause);
		return;
	}

	timer1 = Utils::Clamp(timer1 - dt, 0.f, gameTime);
	uiTimer1->SetValue(timer1 / gameTime);

	timer2 = Utils::Clamp(timer2 - dt, 0.f, gameTime);
	uiTimer2->SetValue(timer2 / gameTime);

	if (timer1 <= 0 && timer2 <= 0)
	{
		sfxTimeOut.play();
		sfxTimeOut.play();

		player2->OnDie();
		player1->OnDie();

		SetCenterMessage("Yours Chicken!! Press Enter!");
		SetStatus(Status::GameOver);
		return;
	}

	if (timer1 <= 0.f)
	{
		sfxTimeOut.play();

		player1->OnDie();
		SetCenterMessage("Player1 Time Over! Press Enter!");
		SetStatus(Status::GameOver);
		return;
	}

	if (timer2 <= 0.f)
	{
		sfxTimeOut.play();

		player2->OnDie();
		SetCenterMessage("Player2 Time Over! Press Enter!");
		SetStatus(Status::GameOver);
		return;
	}
}

void SceneDev2::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}
}

void SceneDev2::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Escape))
	{
		SetStatus(Status::Game);
	}
}

void SceneDev2::OnChop(int playernumber, Sides side)
{
	if (playernumber == 1)
	{
		Sides branchSide1 = tree1->Chop(side);
		if (player1->GetSide() == branchSide1)
		{
			sfxDeath.play();

			player1->OnDie();
			SetCenterMessage("Player1 You Die! Press Enter!");
			SetStatus(Status::GameOver);
		}
		else
		{
			SetScore(1, score1 + 100);
			timer1 += 1.f;
		}
	}

	if (playernumber == 2)
	{
		Sides branchSide2 = tree2->Chop(side);
		if (player2->GetSide() == branchSide2)
		{
			sfxDeath.play();

			player2->OnDie();
			SetCenterMessage("Player2 You Die! Press Enter!");
			SetStatus(Status::GameOver);
		}
		else
		{
			SetScore(2, score2 + 100);
			timer2 += 1.f;
		}
	}
}
