#pragma once
#include "GameObject.h"
class SkillCD : public GameObject
{
protected:
	sf::Sprite skillIcon1;
	sf::Sprite skillIcon2;
	sf::Sprite skillIcon3;
	
	sf::RectangleShape skillShader1;
	sf::RectangleShape skillShader2;
	sf::RectangleShape skillShader3;

	sf::Sprite spriteSkill1;
	sf::Sprite spriteSkill2;
	sf::Sprite spriteSkill3;

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

