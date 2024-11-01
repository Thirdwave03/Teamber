#include "stdafx.h"
#include "EffectSkill2.h"

EffectSkill2::EffectSkill2()
	: SpriteGo("graphics/Shoryuken.png", "Shoryuken")
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

EffectSkill2::EffectSkill2(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name)
{
}

void EffectSkill2::Update(float dt)
{
	timer += dt;
	if (timer > duration)
	{
		SetActive(false);
		return;
	}

	SetPosition(position + velocity * dt);
}

void EffectSkill2::Fire(sf::Vector2f v)
{
	velocity = v;
	timer = 0.f;
}

sf::FloatRect EffectSkill2::GGB() const
{
	return sprite.getGlobalBounds();
}
