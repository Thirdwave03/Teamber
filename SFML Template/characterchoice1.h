#pragma once
#include "Scene.h"

class SceneDev1;
class SceneDev2;
class SceneTitle;
class Player;
class Choice;

class CharacterChoice1 : public Scene
{
protected:
	Player* player1;
	Player* player2;
	Choice* choice; 
public:
	CharacterChoice1();
	~CharacterChoice1() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetMainMessage(const std::string& msg);

};

