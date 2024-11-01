#pragma once
#include "SpriteGo.h"
class RotatingObject : public SpriteGo
{
protected:
    float rotationMultiplier = 10.0f;

public:
    RotatingObject(std::string texId, std::string name = "");

    void SetRotationMultiplier(float mtp_in);

    void Update(float dt) override;

    
};

