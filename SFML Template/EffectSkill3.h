#pragma once
#include "SpriteGo.h"

class EffectSkill3 : public SpriteGo
{
protected:
	sf::RectangleShape skill3 = sf::RectangleShape({ 120.f,120.f });

	sf::Vector2u imageCnt = { 4,1 };
	sf::Vector2u currentImage = { 0,0 };

	float totalTime=0;
	float switchTime=0.2f;

	float duration = 2.f;
	float timer = 0.f;

	sf::IntRect uvRect = sf::IntRect(0,0,120,120);

public:

	EffectSkill3();
	EffectSkill3(sf::Vector2u imgCnt_in, float switchTime_in);
	~EffectSkill3();
	EffectSkill3(const EffectSkill3& other) = default;
	EffectSkill3& operator=(const EffectSkill3& other) = default;

	void SetUvRect(sf::IntRect rect_in);

	void Update(float dt) override;

	void Fire();

	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GGB() const override;
};

