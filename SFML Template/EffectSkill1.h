#pragma once
#include "SpriteGo.h"

class EffectSkill1 :
    public SpriteGo
{
protected:
	sf::Vector2f velocity;

	float duration = 5.f;
	float timer = 0.f;

public:
	EffectSkill1();
	EffectSkill1(const std::string& texId, const std::string& name = "");
	~EffectSkill1() = default;

	void Update(float dt) override;

	void Fire(sf::Vector2f v);

	sf::FloatRect GGB() const override;
};

