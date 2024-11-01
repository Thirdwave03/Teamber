#pragma once
#include "SpriteGo.h"
class Enemy :
    public SpriteGo
{
protected:

public:
    Enemy(const std::string texId, std::string name_in);
    virtual ~Enemy() = default;
    Enemy(const Enemy& other) = default;
    Enemy& operator=(const Enemy& other) = default;
};
