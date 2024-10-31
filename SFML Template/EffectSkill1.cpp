#include "stdafx.h"
#include "EffectSkill1.h"

EffectSkill1::EffectSkill1() 
	: SpriteGo("graphics/Hadouken.png")
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

EffectSkill1::EffectSkill1(const std::string& texId, const std::string& name)
	: SpriteGo(texId, name)
{
}

void EffectSkill1::Update(float dt)
{
	timer += dt;
	if (timer > duration)
	{
		SetActive(false);
		return;
	}

	SetPosition(position + velocity * dt);
}

void EffectSkill1::Fire(sf::Vector2f v)
{
	velocity = v;
	timer = 0.f;
}
