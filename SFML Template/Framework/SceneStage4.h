#pragma once
#include "Scene.h"

class Tree;
class Player;
class TextGo;
class UiScore;
class UiTimebar;
class SkillCD;
class RotatingObject;
class Enemy;

class SceneStage4 : public Scene
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
	RotatingObject* rotatingobject[2];

	int score = 17000;
	float timer = 0.f;
	float gameTime = 5.f;

	TextGo* timeLimMsg;
	float timeLim = 0.1f;

	int stage = 4;

	float spawnCnt = 1.f;
	float spawnCnt2 = 1.f;
	float spawnCnt3 = 1.f;

	sf::Sound sfxDeath;
	sf::Sound sfxTimeOut;
	sf::Sound sfxShoryuken;
	sf::Sound sfxHadouken;
	sf::Sound sfxTatsumaki;

	std::string sbIdDeath = "sound/death.wav";
	std::string sbIdTimeOut = "sound/out_of_time.wav";
	std::string sbIdShoryuken = "sound/Shoryuken.wav";
	std::string sbIdHadouken = "sound/Hadouken.wav";
	std::string sbIdTatsumaki = "sound/Tatsumaki.wav";

public:
	SceneStage4();
	~SceneStage4() = default;

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

	void SpawnLava(int num);
	void SpawnMeteor(int num);
	void SpawnHOS(int num);

	void OnChop(Sides side);

	void OnQ();
	void OnW();
	void OnE();
};