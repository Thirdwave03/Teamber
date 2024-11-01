#include "stdafx.h"
#include "Player.h"
#include "SceneDev1.h"	
#include "SceneDev2.h"
#include "SceneStage2.h"
#include "SceneStage3.h"
#include "SceneStage4.h"

Player::Player(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

Player::Player(const std::string& id, const std::string& name)
	: texIdPlayer(id), GameObject(name)
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void Player::SetSide(Sides s)
{
	side = s;

	if (side == Sides::Left)
	{
		SetScale({ -1.f, 1.f });
	}
	else if (side == Sides::Right)
	{
		SetScale({ 1.f, 1.f });
	}

	sf::Vector2f newPos = position + localPosPlayer[(int)s];
	spritePlayer.setPosition(newPos);
	spriteAxe.setPosition(newPos + localPosAxe);
	spriteRip.setPosition(newPos + localRipAxe);
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	SetSide(side);
}

void Player::OnDie()
{
	isAlive = false;
	isChppoing = false;


}

void Player::SetScale(const sf::Vector2f& scale)
{
	this->scale = scale;
	spritePlayer.setScale(this->scale);

	sf::Vector2f axeScale = this->scale;
	axeScale.x *= -1.f;
	spriteAxe.setScale(axeScale);

	sf::Vector2f axeRip = this->scale;
	axeRip.x = abs(axeScale.x);
	spriteRip.setScale(axeRip);
}

void Player::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (preset != Origins::Custom)
	{
		origin = Utils::SetOrigin(spritePlayer, preset);
	}
}

void Player::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	spritePlayer.setOrigin(origin);
}

void Player::Init()
{
	spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer));
	SetOrigin(Origins::BC);

	spriteAxe.setTexture(TEXTURE_MGR.Get(texIdAxe));
	spriteAxe.setOrigin(originAxe);

	spriteRip.setTexture(TEXTURE_MGR.Get(texIdRip));
	Utils::SetOrigin(spriteRip, Origins::BC);
}

void Player::Reset()
{
	sfxChop.setBuffer(SOUNDBUFFER_MGR.Get(sbIdChop));

	spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer));
	spriteAxe.setTexture(TEXTURE_MGR.Get(texIdAxe));
	spriteRip.setTexture(TEXTURE_MGR.Get(texIdRip));

	isAlive = true;
	isChppoing = false;
	SetPosition(position);
	SetScale({ 1.f, 1.f });
	SetSide(Sides::Right);
}

void Player::SetTexture(const std::string& changeId)
{
	texIdPlayer = changeId;
	spritePlayer.setTexture(TEXTURE_MGR.Get(texIdPlayer));
}


void Player::Release()
{
}


void Player::Update(float dt)
{
	if (!isAlive || FRAMEWORK.GetTimeScale() <= 0.f)
		return;
	if (GameObject::name == "Player")
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::A))
		{
			isChppoing = true;
			SetSide(Sides::Left);
			if (sceneGame != nullptr)
			{
				sceneGame->OnChop(Sides::Left);
				sfxChop.play();
			}
			if (sceneGame2 != nullptr)
			{
				sceneGame2->OnChop(1, Sides::Left);
				sfxChop.play();
			}
			if (sceneStage2 != nullptr)
			{
				sceneStage2->OnChop(Sides::Left);
				sfxChop.play();
			}
			if (sceneStage3 != nullptr)
			{
				sceneStage3->OnChop(Sides::Left);
				sfxChop.play();
			}
			if (sceneStage4 != nullptr)
			{
				sceneStage4->OnChop(Sides::Left);
				sfxChop.play();
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::Q))
		{
			if (sceneStage2 != nullptr)
			{
				sceneStage2->OnQ();
			}
			if (sceneStage3 != nullptr)
			{
				sceneStage3->OnQ();
			}
			if (sceneStage4 != nullptr)
			{
				sceneStage4->OnQ();
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::W))
		{
			if (sceneGame2 != nullptr)
			{
				sceneGame2->OnChop(1, Sides::Left);
				sfxChop.play();
			}
			if (sceneStage3 != nullptr)
			{
				sceneStage3->OnW();
			}
			if (sceneStage4 != nullptr)
			{
				sceneStage4->OnW();
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::E))
		{
			if (sceneStage4 != nullptr)
			{
				sceneStage4->OnE();
			}
		}
		if (InputMgr::GetKeyUp(sf::Keyboard::A))
		{
			isChppoing = false;
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::D))
		{
			isChppoing = true;
			SetSide(Sides::Right);
			if (sceneGame != nullptr)
			{
				sceneGame->OnChop(Sides::Right);
				sfxChop.play();
			}
			if (sceneGame2 != nullptr)
			{
				sceneGame2->OnChop(1, Sides::Right);
				sfxChop.play();
			}
			if (sceneStage2 != nullptr)
			{
				sceneStage2->OnChop(Sides::Right);
				sfxChop.play();
			}
			if (sceneStage3 != nullptr)
			{
				sceneStage3->OnChop(Sides::Right);
				sfxChop.play();
			}
			if (sceneStage4 != nullptr)
			{
				sceneStage4->OnChop(Sides::Right);
				sfxChop.play();
			}
		}

		if (InputMgr::GetKeyUp(sf::Keyboard::D))
		{
			isChppoing = false;
		}
	}
	else if (GameObject::name == "Player2")
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Left))
		{
			isChppoing = true;
			SetSide(Sides::Left);
			if (sceneGame != nullptr)
			{
				sceneGame->OnChop(Sides::Left);
				sfxChop.play();
			}
			if (sceneGame2 != nullptr)
			{
				sceneGame2->OnChop(2, Sides::Left);
				sfxChop.play();
			}
		}

		if (InputMgr::GetKeyUp(sf::Keyboard::Left))
		{
			isChppoing = false;
		}

		if (InputMgr::GetKeyDown(sf::Keyboard::Right))
		{
			isChppoing = true;
			SetSide(Sides::Right);
			if (sceneGame != nullptr)
			{
				sceneGame->OnChop(Sides::Right);
				sfxChop.play();
			}
			if (sceneGame2 != nullptr)
			{
				sceneGame2->OnChop(2, Sides::Right);
				sfxChop.play();
			}

		}

		if (InputMgr::GetKeyUp(sf::Keyboard::Right))
		{
			isChppoing = false;
		}
	}


}

void Player::Draw(sf::RenderWindow& window)
{
	if (isAlive)
	{
		window.draw(spritePlayer);
		if (isChppoing)
		{
			window.draw(spriteAxe);
		}
	}
	else
	{
		window.draw(spriteRip);
	}
}

void Player::SetSceneGame(SceneDev1* scene)
{
	sceneGame = scene;
}

void Player::SetSceneGame2(SceneDev2* scene)
{
	sceneGame2 = scene;
}

void Player::SetSceneGameStage2(SceneStage2* scene)
{
	sceneStage2 = scene;
}

void Player::SetSceneGameStage3(SceneStage3* scene)
{
	sceneStage3 = scene;
}

void Player::SetSceneGameStage4(SceneStage4* scene)
{
	sceneStage4 = scene;
}
