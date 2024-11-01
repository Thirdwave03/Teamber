#pragma once


class Animation
{
private:
	sf::Vector2u imageCnt;
	sf::Vector2u currentImage;

	float totalTime;
	float switchTime;

public:
	sf::IntRect uvRect;

	Animation();
	Animation(sf::Texture* texture_in, sf::Vector2u imgCnt_in, float switchTime_in);
	virtual ~Animation();
	Animation(const Animation& other) = default;
	virtual Animation& operator=(const Animation& other) = default;

	void SetUvRect(sf::IntRect rect_in);

	virtual void Update(float dt);
};