#pragma once
#include "Scene.h"

class Tree;
class Player;
class TextGo;

class SceneTitle : public Scene
{

public:
protected:
	Tree* tree;
	Player* player;
	TextGo* LeftMsg;
	TextGo* RigthMsg;
	TextGo* MainMsg;

public:
	SceneTitle();
	~SceneTitle() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetLeftMessage(const std::string& msg);
	void SetRightMessage(const std::string& msg);
	void SetMainMessage(const std::string& msg);
};

