#include "stdafx.h"
#include "EnemyLava.h"

EnemyLava::EnemyLava()
	:Enemy(texidLava, "Enemy")
{
	
}

EnemyLava::EnemyLava(const std::string texId)
	:Enemy(texId, "Enemy")
{

}

void EnemyLava::Update(float dt)
{
	SetPosition(position + speed * dt);
}

void EnemyLava::Reset()
{
	SpriteGo::Reset();

}

void EnemyLava::SetSpeed(sf::Vector2f speed_in)
{
	speed = speed_in;
}

void EnemyLava::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void EnemyLava::SetPosition(const sf::Vector2f pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

sf::FloatRect EnemyLava::GGB() const
{
	return sprite.getGlobalBounds();
}
