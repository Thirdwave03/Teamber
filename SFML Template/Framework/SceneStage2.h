#pragma once
#include "Scene.h"

class Tree;
class Player;
class TextGo;
class UiScore;
class UiTimebar;
class SkillCD;

class SceneStage2 : public Scene
{
public:
	enum class Status
	{
		Awake,
		Game,
		GameOver,
		Pause,
	};

protected:
	Status currentStatus = Status::Awake;

	Tree* tree;
	Player* player;
	SkillCD* skillMgr;

	TextGo* centerMsg;
	UiScore* uiScore;
	UiTimebar* uiTimer;

	int score = 0;
	float timer = 0.f;
	float gameTime = 5.f;

	TextGo* timeLimMsg;
	float timeLim = 30.f;

	int stage = 1;

	sf::Sound sfxDeath;
	sf::Sound sfxTimeOut;
	sf::Sound sfxShoryuken;

	std::string sbIdDeath = "sound/death.wav";
	std::string sbIdTimeOut = "sound/out_of_time.wav";
	std::string sbIdShoryuken = "sound/Shoryuken.wav";

public:
	SceneStage2();
	~SceneStage2() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void SetCenterMessage(const std::string& msg);
	void SetVisibleCenterMessage(bool visible);

	void SetTimeLimMsg(const std::string& msg);

	void SetScore(int score);
	int GetScore();

	void SetStatus(Status newStatus);
	void UpdateAwake(float dt);
	void UpdateGame(float dt);
	void UpdateGameOver(float dt);
	void UpdatePause(float dt);

	void OnChop(Sides side);

};
