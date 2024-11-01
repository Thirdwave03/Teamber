#include "stdafx.h"
#include "GameObject.h"

GameObject::GameObject(const std::string& name)
	: name(name), originPreset(Origins::TL)/*, objectIdentification(idCnt)*/
{

}

sf::FloatRect GameObject::GGB() const
{
	return sf::FloatRect(0.f, 0.f, 0.f, 0.f);
}

void GameObject::SetSpeed(sf::Vector2f)
{
}

void GameObject::SetOrigin(Origins preset)
{
	originPreset = preset;
	origin = { 0.f, 0.f };
}

void GameObject::Init()
{
}

void GameObject::Release()
{
}

void GameObject::Reset()
{
}

void GameObject::Update(float dt)
{
}

void GameObject::Draw(sf::RenderWindow& window)
{
}
