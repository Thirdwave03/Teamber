#pragma once
#include "GameObject.h"

class SceneDev1;
class SceneDev2;
class SceneStage2;
class SceneStage3;
class SceneStage4;

class Player : public GameObject
{
protected:
	sf::Sound sfxChop;


	sf::Sprite spritePlayer;
	sf::Sprite spriteAxe;
	sf::Sprite spriteRip;

	std::string sbIdChop = "sound/chop.wav";
	std::string texIdPlayer = "graphics/player.png";
	std::string texIdAxe = "graphics/axe.png";
	std::string texIdRip = "graphics/rip.png";

	Sides side = Sides::Right;

	sf::Vector2f localPosPlayer[3] = { { -300.f, 0.f },  { 300.f, 0.f },  { 0.f, 0.f } };
	sf::Vector2f localPosAxe = { 0.f, -70.f };
	sf::Vector2f localRipAxe = { 0.f, 0.f };

	sf::Vector2f originAxe = { -65.f, 0.f };

	bool isAlive = true;
	bool isChppoing = false;

	SceneDev1* sceneGame = nullptr;
	SceneDev2* sceneGame2 = nullptr;
	SceneStage2* sceneStage2 = nullptr;
	SceneStage3* sceneStage3 = nullptr;
	SceneStage4* sceneStage4 = nullptr;

public:
	Player(const std::string& name = "");
	Player(const std::string& id, const std::string& name = "");
	virtual ~Player() = default;

	Sides GetSide() const { return side; }
	void SetSide(Sides s);
	void OnDie();

	void SetPosition(const sf::Vector2f& pos) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset()  override;

	void SetTexture(const std::string& changeId);
	

	void ChangeTexturIdPlayer(const std::string& changeid)
	{
		spritePlayer.setTexture(TEXTURE_MGR.Get(changeid));
	}

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window)  override;

	void SetSceneGame(SceneDev1* scene);
	void SetSceneGame2(SceneDev2* scene);
	void SetSceneGameStage2(SceneStage2* scene);
	void SetSceneGameStage3(SceneStage3* scene);
	void SetSceneGameStage4(SceneStage4* scene);
};

