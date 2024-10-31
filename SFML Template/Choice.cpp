#include "stdafx.h"
#include "Choice.h"

Choice::Choice(const std::string& name)
	:GameObject(name)
{
}

Choice::Choice(const std::string& id, const std::string& name)
	: texIdChoice(id), GameObject(name)
{
}

void Choice::SetSide(Sides s)
{
	side = s;

	sf::Vector2f newPos = position + localPosChoice[(int)s];
	spriteChoice.setPosition(newPos);
}

void Choice::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	SetSide(side);
}

void Choice::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (preset != Origins::Custom)
	{
		origin = Utils::SetOrigin(spriteChoice, preset);
	}
}

void Choice::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	spriteChoice.setOrigin(origin);
}

void Choice::Init()
{
}

void Choice::Release()
{
}

void Choice::Reset()
{
	spriteChoice.setTexture(TEXTURE_MGR.Get(texIdChoice));
	SetOrigin(Origins::TC);

	SetPosition(position);
	SetScale({ 1.f, 1.f });
	SetSide(Sides::Right);
}

void Choice::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		SetSide(Sides::Left);
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		SetSide(Sides::Right);
	}
}

void Choice::Draw(sf::RenderWindow& window)
{
	window.draw(spriteChoice);
}
