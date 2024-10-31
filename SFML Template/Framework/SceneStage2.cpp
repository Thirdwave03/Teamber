#include "stdafx.h"
#include "SceneStage2.h"
#include "SpriteGo.h"
#include "CloudGo.h"
#include "Tree.h"
#include "Player.h"
#include "TextGo.h"
#include "UiScore.h"
#include "UiTimebar.h"

SceneStage2::SceneStage2() : Scene(SceneIds::Stage2)
{

}

void SceneStage2::Init()
{
	std::cout << "SceneStage2::Init()" << std::endl;

	Scene::Init();

	tree->SetPosition({ 1920.f / 2, 1080.f - 200.f });
	player->SetPosition({ 1920.f / 2, 1080.f - 200.f });

	centerMsg->text.setCharacterSize(100);
	centerMsg->text.setFillColor(sf::Color::White);
	centerMsg->SetPosition({ 1920.f / 2.f, 1080.f / 2.f });

	uiScore->text.setCharacterSize(75);
	uiScore->text.setFillColor(sf::Color::White);
	uiScore->SetPosition({ 30.f, 30.f });

	uiTimer->Set({ 500.f, 100.f }, sf::Color::Red);
	uiTimer->SetOrigin(Origins::ML);
	uiTimer->SetPosition({ 1920.f / 2.f - 250.f, 1080.f - 100.f });
}

void SceneStage2::Enter()
{
	TEXTURE_MGR.Load("graphics/background.png");
	TEXTURE_MGR.Load("graphics/cloud.png");
	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/log.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/axe.png");
	TEXTURE_MGR.Load("graphics/Shoryuken.png");
	TEXTURE_MGR.Load("graphics/Shoryuken_icon.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Load(sbIdDeath);
	SOUNDBUFFER_MGR.Load(sbIdTimeOut);
	SOUNDBUFFER_MGR.Load(sbIdShoryuken);

	sfxDeath.setBuffer(SOUNDBUFFER_MGR.Get(sbIdDeath));
	sfxTimeOut.setBuffer(SOUNDBUFFER_MGR.Get(sbIdTimeOut));
	sfxShoryuken.setBuffer(SOUNDBUFFER_MGR.Get(sbIdShoryuken));

	player->SetSceneGameStage2(this);

	Scene::Enter();

	SetStatus(Status::Awake);
}

void SceneStage2::Exit()
{
	std::cout << "SceneStage2::Exit()" << std::endl;

	player->SetSceneGame(nullptr);
	tree->ClearEffectLog();

	Scene::Exit();

	TEXTURE_MGR.Unload("graphics/cloud.png");
	TEXTURE_MGR.Unload("graphics/background.png");
	TEXTURE_MGR.Unload("graphics/tree.png");
	TEXTURE_MGR.Unload("graphics/branch.png");
	TEXTURE_MGR.Unload("graphics/log.png");
	TEXTURE_MGR.Unload("graphics/player.png");
	TEXTURE_MGR.Unload("graphics/rip.png");
	TEXTURE_MGR.Unload("graphics/axe.png");
	TEXTURE_MGR.Unload("graphics/Shoryuken.png");
	TEXTURE_MGR.Unload("graphics/Shoryuken_icon.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Unload("sound/chop.wav");
	SOUNDBUFFER_MGR.Unload("sound/death.wav");
	SOUNDBUFFER_MGR.Unload("sound/out_of_time.wav");
	SOUNDBUFFER_MGR.Unload("sound/Shoryuken.wav");
}

void SceneStage2::Update(float dt)
{
	Scene::Update(dt);

	SetTimeLimMsg(std::to_string((int)timeLim));

	switch (currentStatus)
	{
	case SceneStage2::Status::Awake:
		UpdateAwake(dt);
		break;
	case SceneStage2::Status::Game:
		UpdateGame(dt);
		break;
	case SceneStage2::Status::GameOver:
		UpdateGameOver(dt);
		break;
	case SceneStage2::Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SceneStage2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneStage2::SetCenterMessage(const std::string& msg)
{
	centerMsg->text.setString(msg);
	centerMsg->SetOrigin(Origins::MC);
}

void SceneStage2::SetVisibleCenterMessage(bool visible)
{
	centerMsg->SetActive(visible);
}

void SceneStage2::SetTimeLimMsg(const std::string& msg)
{
	timeLimMsg->text.setString(msg);
	timeLimMsg->SetOrigin(Origins::MC);
}

void SceneStage2::SetScore(int score)
{
	this->score = score;
	uiScore->SetScore(this->score);
}

int SceneStage2::GetScore()
{
	return score;
}

void SceneStage2::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case SceneStage2::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("Press Enter To Start!!");
		score = 0;
		timer = gameTime;
		SetScore(score);
		uiTimer->SetValue(1.f);
		break;
	case SceneStage2::Status::Game:
		if (prevStatus == Status::GameOver)
		{
			score = 0;
			timer = gameTime;
			timeLim = 30.f;
			stage = 1;

			SetScore(score);
			uiTimer->SetValue(1.f);

			player->Reset();
			tree->Reset();
		}
		FRAMEWORK.SetTimeScale(1.f);
		SetVisibleCenterMessage(false);
		break;
	case SceneStage2::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		break;
	case SceneStage2::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("PAUSE! ESC TO RESUME!");
		break;
	}
}

void SceneStage2::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneStage2::UpdateGame(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Grave))
	{
		SetStatus(Status::Pause);
		return;
	}

	if (timeLim > 0.f)
		timeLim -= dt;

	timer = Utils::Clamp(timer - dt, 0.f, gameTime);
	uiTimer->SetValue(timer / gameTime);
	if (timer <= 0.f || timeLim <= 0.f)
	{
		sfxTimeOut.play();

		player->OnDie();
		SetCenterMessage("Time Over!");
		SetStatus(Status::GameOver);
		return;
	}
}

void SceneStage2::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneStage2::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Grave))
	{
		SetStatus(Status::Game);
	}
}

void SceneStage2::OnChop(Sides side)
{
	Sides branchSide = tree->Chop(side);
	if (player->GetSide() == branchSide)
	{
		sfxDeath.play();

		player->OnDie();
		SetCenterMessage("You Die!");
		SetStatus(Status::GameOver);
	}
	else
	{
		SetScore(score + 100);
		timer += 1.f;
	}
}
