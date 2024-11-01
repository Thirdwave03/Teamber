#include "stdafx.h"
#include "EffectSkill3.h"

EffectSkill3::EffectSkill3()
	:SpriteGo("graphics/Tatsumaki.png", "Tatsumaki")
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;
}

EffectSkill3::EffectSkill3(sf::Vector2u imgCnt_in, float switchTime_in)
	: imageCnt(imgCnt_in), switchTime(switchTime_in)
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;
	skill3.setTexture(&TEXTURE_MGR.Get("graphics/Tatsumaki.png"));
}

EffectSkill3::~EffectSkill3()
{

}

void EffectSkill3::SetUvRect(sf::IntRect rect_in)
{
}

void EffectSkill3::Update(float dt)
{	
	timer += dt;
	if (timer > duration)
	{
		SetActive(false);
		return;
	}
	currentImage.y = 0;
	totalTime += dt;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCnt.x)
		{
			currentImage.x = 0;
			if (currentImage.y >= imageCnt.y)
				currentImage.y--;
			else
				currentImage.y++;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
	sprite.setTextureRect(uvRect);
}

void EffectSkill3::Fire()
{
	timer = 0.f;
}

void EffectSkill3::Draw(sf::RenderWindow& window)
{
	GameObject::Draw(window);
	window.draw(sprite);
}

sf::FloatRect EffectSkill3::GGB() const
{
	return sprite.getGlobalBounds();
}
