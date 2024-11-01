#include "stdafx.h"
#include "SceneStage3.h"
#include "SpriteGo.h"
#include "CloudGo.h"
#include "Tree.h"
#include "Player.h"
#include "TextGo.h"
#include "UiScore.h"
#include "UiTimebar.h"
#include "SkillCD.h"
#include "EnemyLava.h"

SceneStage3::SceneStage3() : Scene(SceneIds::Stage3)
{

}

void SceneStage3::Init()
{
	std::cout << "SceneStage3::Init()" << std::endl;

	GameObject* obj = AddGo(new SpriteGo("graphics/background3.png"));
	obj->sortingLayer = SortingLayers::Background;
	obj->sortingOrder = -1;
	obj->SetOrigin(Origins::MC);
	obj->SetPosition({ 1920 / 2, 1080 / 2 });

	tree = AddGo(new Tree("Tree"));
	player = AddGo(new Player("graphics/player.png", "Player"));

	timeLimMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Time Limit"));
	timeLimMsg->sortingLayer = SortingLayers::UI;
	timeLimMsg->text.setCharacterSize(120);
	timeLimMsg->text.setFillColor(sf::Color::White);
	timeLimMsg->SetPosition({ 1920.f / 2.f, 0 });
	timeLimMsg->SetOrigin({ 50.f,0.f });
	SetTimeLimMsg(std::to_string((int)timeLim));

	centerMsg = AddGo(new TextGo("fonts/KOMIKAP_.ttf", "Center Message"));
	centerMsg->sortingLayer = SortingLayers::UI;

	uiScore = AddGo(new UiScore("fonts/KOMIKAP_.ttf", "Ui Score"));
	uiTimer = AddGo(new UiTimebar("Ui Timer"));

	skillMgr = AddGo(new SkillCD("default", "skillMgr"));
	skillMgr->SkillUnlock(0);
	skillMgr->SkillUnlock(1);

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

void SceneStage3::Enter()
{
	TEXTURE_MGR.Load("graphics/background3.png");
	TEXTURE_MGR.Load("graphics/cloud.png");
	TEXTURE_MGR.Load("graphics/tree.png");
	TEXTURE_MGR.Load("graphics/branch.png");
	TEXTURE_MGR.Load("graphics/log.png");
	TEXTURE_MGR.Load("graphics/player.png");
	TEXTURE_MGR.Load("graphics/rip.png");
	TEXTURE_MGR.Load("graphics/axe.png");
	TEXTURE_MGR.Load("graphics/Lava.png");
	TEXTURE_MGR.Load("graphics/Meteor.png");
	TEXTURE_MGR.Load("graphics/Hadouken.png");
	TEXTURE_MGR.Load("graphics/Hadouken_icon.png");
	TEXTURE_MGR.Load("graphics/Shoryuken.png");
	TEXTURE_MGR.Load("graphics/Shoryuken_icon.png");
	FONT_MGR.Load("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Load(sbIdDeath);
	SOUNDBUFFER_MGR.Load(sbIdTimeOut);
	SOUNDBUFFER_MGR.Load(sbIdHadouken);
	SOUNDBUFFER_MGR.Load(sbIdShoryuken);

	sfxDeath.setBuffer(SOUNDBUFFER_MGR.Get(sbIdDeath));
	sfxTimeOut.setBuffer(SOUNDBUFFER_MGR.Get(sbIdTimeOut));
	sfxHadouken.setBuffer(SOUNDBUFFER_MGR.Get(sbIdHadouken));
	sfxShoryuken.setBuffer(SOUNDBUFFER_MGR.Get(sbIdShoryuken));

	player->SetSceneGameStage3(this);

	Scene::Enter();

	SetStatus(Status::Awake);
}

void SceneStage3::Exit()
{
	std::cout << "SceneStage3::Exit()" << std::endl;

	player->SetSceneGameStage3(nullptr);
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
	TEXTURE_MGR.Unload("graphics/Lava.png");
	TEXTURE_MGR.Unload("graphics/Meteor.png");
	TEXTURE_MGR.Unload("graphics/Hadouken.png");
	TEXTURE_MGR.Unload("graphics/Hadouken_icon.png");
	TEXTURE_MGR.Unload("graphics/Shoryuken.png");
	TEXTURE_MGR.Unload("graphics/Shoryuken_icon.png");
	FONT_MGR.Unload("fonts/KOMIKAP_.ttf");
	SOUNDBUFFER_MGR.Unload("sound/chop.wav");
	SOUNDBUFFER_MGR.Unload("sound/death.wav");
	SOUNDBUFFER_MGR.Unload("sound/out_of_time.wav");
	SOUNDBUFFER_MGR.Unload("sound/Hadouken.wav");

	for (auto obj : gameObjects)
	{
		if (!obj->IsActive())
			continue;
		if (obj->GetName() == "Enemy")
			obj->SetActive(false);
	}
}

void SceneStage3::Update(float dt)
{
	Scene::Update(dt);

	SetTimeLimMsg(std::to_string((int)timeLim));
	spawnCnt -= dt;
	spawnCnt2 -= dt;

	if (InputMgr::GetKeyDown(sf::Keyboard::R))
	{
		SCENE_MGR.ChangeScene(SceneIds::Title);
	}

	switch (currentStatus)
	{
	case SceneStage3::Status::Awake:
		UpdateAwake(dt);
		break;
	case SceneStage3::Status::Game:
		UpdateGame(dt);
		break;
	case SceneStage3::Status::GameOver:
		UpdateGameOver(dt);
		break;
	case SceneStage3::Status::Pause:
		UpdatePause(dt);
		break;
	}
}

void SceneStage3::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}

void SceneStage3::SetCenterMessage(const std::string& msg)
{
	centerMsg->text.setString(msg);
	centerMsg->SetOrigin(Origins::MC);
}

void SceneStage3::SetVisibleCenterMessage(bool visible)
{
	centerMsg->SetActive(visible);
}

void SceneStage3::SetTimeLimMsg(const std::string& msg)
{
	timeLimMsg->text.setString(msg);
	timeLimMsg->SetOrigin(Origins::MC);
}

void SceneStage3::SetScore(int score)
{
	this->score = score;
	uiScore->SetScore(this->score);
}

int SceneStage3::GetScore()
{
	return score;
}

void SceneStage3::SetStatus(Status newStatus)
{
	Status prevStatus = currentStatus;
	currentStatus = newStatus;

	switch (currentStatus)
	{
	case SceneStage3::Status::Awake:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("Press Enter To Start!!");
		score = 0;
		timer = gameTime;
		SetScore(score);
		uiTimer->SetValue(1.f);
		break;
	case SceneStage3::Status::Game:
		if (prevStatus == Status::GameOver)
		{
			SCENE_MGR.ChangeScene(SceneIds::Dev1);
			score = 0;
			timer = gameTime;
			timeLim = 30.f;
			stage = 1;
			tree->SetTreeHp(80);

			SetScore(score);
			uiTimer->SetValue(1.f);

			player->Reset();
			tree->Reset();
		}
		FRAMEWORK.SetTimeScale(1.f);
		SetVisibleCenterMessage(false);
		break;
	case SceneStage3::Status::GameOver:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		break;
	case SceneStage3::Status::Pause:
		FRAMEWORK.SetTimeScale(0.f);
		SetVisibleCenterMessage(true);
		SetCenterMessage("PAUSE! ESC TO RESUME!");
		break;
	}
}

void SceneStage3::UpdateAwake(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneStage3::UpdateGame(float dt)
{
	if (score >= 4000)
	{
		SCENE_MGR.ChangeScene(SceneIds::Stage4);
		score = 0;
		timer = gameTime;
		timeLim = 30.f;
	}

	if (spawnCnt <= 0.f)
	{
		spawnCnt += 2;
		SpawnLava(Utils::RandomRange(0, 2));
	}
	if (spawnCnt2 <= 0.f)
	{
		spawnCnt2 += 4;
		SpawnMeteor(Utils::RandomRange(0, 2));
	}

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

	for (auto obj1 : gameObjects)
	{
		if (!obj1->IsActive())
			continue;
		if (obj1->GetName() == "Enemy")
		{
			if (std::find(enemyList.begin(), enemyList.end(), obj1) == enemyList.end())
				enemyList.push_back(obj1);
		}
		if (obj1->GetName() == "Hadouken" || obj1->GetName() == "Shoryuken" || obj1->GetName() == "Tatsumaki")
		{
			if (std::find(bulletList.begin(), bulletList.end(), obj1) == bulletList.end())
				bulletList.push_back(obj1);
		}
	}
	for (auto i : enemyList)
	{
		if (!i->IsActive())
			continue;
		if (player->GetScale().x < 0.f)
		{
			if (i->GGB().left < 740.f && i->GGB().left + i->GGB().width > 590.f &&
				i->GGB().top < 842.f && i->GGB().top + i->GGB().height > 650.f)
				SetStatus(Status::GameOver);
		}
		if (player->GetScale().x > 0.f)
		{
			if (i->GGB().left < 1330.f && i->GGB().left + i->GGB().width > 1180.f &&
				i->GGB().top < 842.f && i->GGB().top + i->GGB().height > 650.f)
				SetStatus(Status::GameOver);
		}
		for (auto j : bulletList)
		{
			if (!j->IsActive())
				continue;
			if (i->GGB().left < j->GGB().left + j->GGB().width && i->GGB().left + i->GGB().width > j->GGB().left &&
				i->GGB().top < j->GGB().top + j->GGB().height && i->GGB().top + i->GGB().height > j->GGB().top)
			{
				i->SetActive(false);
				if (j->GetName() != "Tatsumaki")
					j->SetActive(false);
			}
		}
	}
}

void SceneStage3::UpdateGameOver(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SetStatus(Status::Game);
	}
}

void SceneStage3::UpdatePause(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Grave))
	{
		SetStatus(Status::Game);
	}
}

void SceneStage3::SpawnLava(int num)
{	
	if (num == 0)
	{
		GameObject* lava = AddGo(new EnemyLava("graphics/Lava.png"));
		lava->SetPosition({ -112.f, 750.f });
		lava->SetOrigin(Origins::MC);
		lava->sortingLayer = SortingLayers::Foreground;
		lava->sortingOrder = 0;
		lava->SetScale({ -1.f, 1.f });
		lava->SetSpeed({ 270.f,0.f });
		lava->Reset();
	}
	else if (num == 1)
	{
		GameObject* lava2 = AddGo(new EnemyLava("graphics/Lava.png"));
		lava2->SetPosition({ 2032.f, 750.f });
		lava2->SetOrigin(Origins::MC);
		lava2->sortingLayer = SortingLayers::Foreground;
		lava2->sortingOrder = 0;
		lava2->SetScale({ 1.f, 1.f });
		lava2->SetSpeed({ -270.f,0.f });
		lava2->Reset();
	}
	
}

void SceneStage3::SpawnMeteor(int num)
{
	if (num == 0)
	{
		GameObject* meteor = AddGo(new EnemyLava("graphics/Meteor.png"));
		meteor->SetPosition({ 660.f, -300.f });
		meteor->SetOrigin(Origins::MC);
		meteor->sortingLayer = SortingLayers::Foreground;
		meteor->sortingOrder = 0;
		meteor->SetScale({ 1.f, 1.f });
		meteor->SetSpeed({ 0.f, 400.f });
		meteor->Reset();
	}
	else if (num == 1)
	{
		GameObject* meteor2 = AddGo(new EnemyLava("graphics/Meteor.png"));
		meteor2->SetPosition({ 1250.f, -300.f });
		meteor2->SetOrigin(Origins::MC);
		meteor2->sortingLayer = SortingLayers::Foreground;
		meteor2->sortingOrder = 0;
		meteor2->SetScale({ 1.f, 1.f });
		meteor2->SetSpeed({ 0.f, 400.f });
		meteor2->Reset();
	}
}

void SceneStage3::OnChop(Sides side)
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

void SceneStage3::OnQ()
{
	if (skillMgr->Hadouken(player->GetSide()))
		sfxHadouken.play();
}

void SceneStage3::OnW()
{
	if (skillMgr->Shoryuken(player->GetSide()))
		sfxShoryuken.play();
}
