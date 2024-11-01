#include "stdafx.h"
#include "Anim.h"

Animation::Animation()
{
}

Animation::Animation(sf::Texture* texture_in, sf::Vector2u imgCnt_in, float switchTime_in)
{
	this->imageCnt = imgCnt_in;
	this->switchTime = switchTime_in;
	this->totalTime = 0.f;
	
	currentImage.x = 0.f;

	uvRect.width = texture_in->getSize().x / float(imgCnt_in.x);
}

Animation::~Animation()
{

}

void Animation::SetUvRect(sf::IntRect rect_in)
{
	uvRect = rect_in;
}

void Animation::Update(float dt)
{
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
}
