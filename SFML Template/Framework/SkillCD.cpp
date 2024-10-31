#include "stdafx.h"
#include "SkillCD.h"
#include "SceneDev1.h"
#include "SceneDev2.h"
#include "SceneStage2.h"
#include "SceneStage3.h"
#include "SceneStage4.h"
#include "EffectSkill1.h"
//#include "EffectSkill2.h"
//#include "EffectSkill3.h"

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
	shaderCD = sf::Color(0, 0, 0, 100);

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
	shaderCD = sf::Color(0, 0, 0, 100);

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

void SkillCD::Hadouken(Sides side)
{
	if (side != Sides::None && skillCD[0] <= 0)
	{
		sf::Vector2f tempPos;
		sf::Vector2f tempSpeed;
		if (side == Sides::Left)
		{
			tempPos = { 660.f, 810.f };
			tempSpeed = { 500.f,0 };
		}
		else
		{
			tempPos = { 1260.f,810.f };
			tempSpeed = { -500.f,0 };
		}
		
		EffectSkill1* s1effect = effectSkill1Pool.Take();
		SCENE_MGR.GetCurrentScene()->AddGo(s1effect);
		s1effect->SetOrigin(Origins::MC);
		s1effect->SetPosition(tempPos);
		s1effect->Fire(tempSpeed);
		Skill1Effects.push_back(s1effect);
		skillCD[0] = 0.5f;
	}
}

void SkillCD::Shoryuken(Sides side)
{
}

void SkillCD::Tatsumaki()
{
}
