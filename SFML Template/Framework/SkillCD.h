#pragma once
#include "GameObject.h"
#include "EffectSkill1.h"
#include "EffectSkill2.h"


class SkillCD : public GameObject
{
protected:
	sf::Sprite skillIcon1;
	sf::Sprite skillIcon2;
	sf::Sprite skillIcon3;

	std::string skill1TexId = "graphics/Hadouken_icon.png";
	std::string skill2TexId = "graphics/Shoryuken_icon.png";
	std::string skill3TexId = "graphics/Tatsumaki_icon.png";
	
	sf::Sprite spriteSkill1;
	sf::Sprite spriteSkill2;
	sf::Sprite spriteSkill3;

	sf::Vector2f iconPos = { 1680.f, 1000.f };
	
	sf::RectangleShape skillShader[3];
	
	sf::Vector2f shaderSize = { 60.f,60.f };
	
	sf::Color shaderBlack;
	sf::Color shaderCD;

	ObjectPool<EffectSkill1> effectSkill1Pool;
	std::list<EffectSkill1*> Skill1Effects;

	ObjectPool<EffectSkill2> effectSkill2Pool;
	std::list<EffectSkill2*> Skill2Effects;
	
	float skillCD[3] = { 0.5f, 3.f, 5.f };

	bool skillUnlock[3] = { false };
	
public:
	SkillCD(const std::string& name = "");
	SkillCD(const std::string& id, const std::string& name = "");
	virtual ~SkillCD();

	void Init() override;
	void Release() override;
	void Reset()  override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window)  override;

	void UpdateCDshader();

	void SkillUnlock(int index);

	bool Hadouken(Sides side);
	bool Shoryuken(Sides side);
	bool Tatsumaki();
};

