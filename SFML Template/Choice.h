#pragma once
#include "GameObject.h"

class SceneDev1;
class SceneDev2;

class Choice :  public GameObject
{
protected:
	sf::Sprite spriteChoice;

	std::string texIdChoice = "graphice/choice.png";

	Sides side = Sides::Right;

	sf::Vector2f localPosChoice[3] = { { 300.f, 0.f },  { 300.f, 0.f },  { 0.f, 0.f } };

public:
	Choice(const std::string& name = "");
	Choice(const std::string& id, const std::string& name = "");
	virtual ~Choice() = default;

	Sides GetSide() const { return side; }
	void SetSide(Sides s);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset()  override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window)  override;
};

