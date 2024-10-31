#pragma once
#include "GameObject.h"
class SkillCD : public GameObject
{
protected:
	sf::Sprite spriteIcon;
	sf::RectangleShape shader;

	Sides side = Sides::Right;

public:
	SkillCD(const std::string& name = "");
	SkillCD(const std::string& id, const std::string& name = "");
	virtual ~SkillCD() = default;

	void Init() override;
	void Release() override;
	void Reset()  override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window)  override;
};

