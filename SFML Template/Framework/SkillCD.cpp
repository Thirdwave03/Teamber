#include "stdafx.h"
#include "SkillCD.h"
#include "SceneDev1.h"
#include "SceneDev2.h"
#include "SceneStage2.h"
#include "SceneStage3.h"
#include "SceneStage4.h"
//#include "EffectSkill1.h"
//#include "EffectSkill2.h"
//#include "EffectSkill3.h"
#include "Anim.h"

SkillCD::SkillCD(const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

SkillCD::SkillCD(const std::string& id, const std::string& name)
	: GameObject(name)
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

SkillCD::~SkillCD()
{
	Release();
}

void SkillCD::Init()
{
	Release();

	shaderBlack = sf::Color(0, 0, 0, 255);
	shaderCD = sf::Color(0, 0, 0, 160);

	skillIcon1.setTexture(TEXTURE_MGR.Get(skill1TexId), true);
	skillIcon1.setPosition(iconPos);
	Utils::SetOrigin(skillIcon1, Origins::TL);

	skillIcon2.setTexture(TEXTURE_MGR.Get(skill2TexId), true);
	skillIcon2.setPosition({ iconPos.x + 80, iconPos.y });
	Utils::SetOrigin(skillIcon2, Origins::TL);

	skillIcon3.setTexture(TEXTURE_MGR.Get(skill3TexId), true);
	skillIcon3.setPosition({ iconPos.x + 160, iconPos.y });
	Utils::SetOrigin(skillIcon3, Origins::TL);

	for (int i = 0; i < 3; i++)
	{
		skillShader[i].setSize(shaderSize);
		skillShader[i].setPosition({ iconPos.x + i * 80, iconPos.y });
		skillShader[i].setFillColor(shaderBlack);
	}
}

void SkillCD::Release()
{
	for (auto skill1effect : Skill1Effects)
	{
		effectSkill1Pool.Return(skill1effect);
		SCENE_MGR.GetCurrentScene()->RemoveGo(skill1effect);
	}
	Skill1Effects.clear();
}

void SkillCD::Reset()
{
	shaderBlack = sf::Color(0, 0, 0, 255);
	shaderCD = sf::Color(0, 0, 0, 160);

	skillIcon1.setTexture(TEXTURE_MGR.Get(skill1TexId), true);
	skillIcon1.setPosition(iconPos);
	Utils::SetOrigin(skillIcon1, Origins::TL);

	skillIcon2.setTexture(TEXTURE_MGR.Get(skill2TexId), true);
	skillIcon2.setPosition({ iconPos.x + 80, iconPos.y });
	Utils::SetOrigin(skillIcon2, Origins::TL);

	skillIcon3.setTexture(TEXTURE_MGR.Get(skill3TexId), true);
	skillIcon3.setPosition({ iconPos.x + 160, iconPos.y });
	Utils::SetOrigin(skillIcon3, Origins::TL);

	for (int i = 0; i < 3; i++)
	{
		skillShader[i].setSize(shaderSize);
		skillShader[i].setPosition({ iconPos.x + i * 80, iconPos.y });
		skillShader[i].setFillColor(shaderBlack);
	}
}

void SkillCD::Update(float dt)
{
	UpdateCDshader();
	for (int i = 0; i < 3; i++)
	{
		skillCD[i] -= dt;
	}
	
	auto it = Skill1Effects.begin();
	while (it != Skill1Effects.end())
	{
		auto s1Effect = *it;
		if (!s1Effect->IsActive())
		{
			effectSkill1Pool.Return(s1Effect);
			SCENE_MGR.GetCurrentScene()->RemoveGo(s1Effect);
			it = Skill1Effects.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void SkillCD::Draw(sf::RenderWindow& window)
{
	window.draw(skillIcon1);
	window.draw(skillIcon2);
	window.draw(skillIcon3);
	for (int i = 0; i < 3; i++)
	{
		window.draw(skillShader[i]);
	}


}

void SkillCD::UpdateCDshader()
{
	for (int i = 0; i < 3; i++)
	{
		skillShader[i].setFillColor(shaderCD);
		if (skillCD[i] <= 0.f)
			skillShader[i].setFillColor(sf::Color::Transparent);
	}


	for (int i = 0; i < 3; i++)
	{
		if (!skillUnlock[i])
			skillShader[i].setFillColor(shaderBlack);
	}
}

void SkillCD::SkillUnlock(int index)
{
	skillUnlock[index] = true;
}

bool SkillCD::Hadouken(Sides side)
{
	if (side != Sides::None && skillCD[0] <= 0)
	{
		sf::Vector2f tempPos;
		sf::Vector2f tempSpeed;
		EffectSkill1* s1effect = effectSkill1Pool.Take();
		if (side == Sides::Left)
		{
			tempPos = { 660.f, 810.f };
			tempSpeed = { 500.f,0 };
			s1effect->SetScale({ 1.f,1.f });
		}
		else
		{
			tempPos = { 1260.f,810.f };
			tempSpeed = { -500.f,0 };
			s1effect->SetScale({ -1.f,1.f });
		}
		SCENE_MGR.GetCurrentScene()->AddGo(s1effect);
		s1effect->SetOrigin(Origins::MC);
		s1effect->SetPosition(tempPos);
		s1effect->Fire(tempSpeed);
		Skill1Effects.push_back(s1effect);
		skillCD[0] = 0.5f;
		return true;
	}
	else
		return false;
}

bool SkillCD::Shoryuken(Sides side)
{
	if (side != Sides::None && skillCD[1] <= 0)
	{
		sf::Vector2f tempPos;
		sf::Vector2f tempSpeed;
		EffectSkill2* s2effect = effectSkill2Pool.Take();
		if (side == Sides::Left)
		{
			tempPos = { 660.f, 750.f };
			tempSpeed = { 0.f, -900.f };
			s2effect->SetScale({ 3.f,3.f });
		}
		else
		{
			tempPos = { 1260.f,750.f };
			tempSpeed = { 0.f, -900.f };
			s2effect->SetScale({ -3.f,3.f });
		}

		SCENE_MGR.GetCurrentScene()->AddGo(s2effect);
		s2effect->SetOrigin(Origins::MC);
		s2effect->SetPosition(tempPos);
		s2effect->Fire(tempSpeed);
		Skill2Effects.push_back(s2effect);
		skillCD[1] = 2.5f;
		return true;
	}
	else
		return false;
}

bool SkillCD::Tatsumaki()
{
	if (skillCD[2] <= 0)
	{
		/*	EffectSkill3 tempS3Effect(p_txtT, sf::Vector2u(0,10), 0.2f);*/
		EffectSkill3* s3effect = effectSkill3Pool.Take();
		SCENE_MGR.GetCurrentScene()->AddGo(s3effect);
		s3effect->SetOrigin(Origins::TL);
		s3effect->SetPosition({ 1920.f/4, 100.f});
		s3effect->Fire();
		s3effect->SetScale({7.5f, 7.f});
		skillCD[2] = 5;
		return true;
	}
	else
		return false;
}
