#include "stdafx.h"
#include "RotatingObject.h"

RotatingObject::RotatingObject(std::string texId, std::string name)
	:SpriteGo(texId, name)
{
}

void RotatingObject::SetRotationMultiplier(float mtp_in)
{
	rotationMultiplier = mtp_in;
}

void RotatingObject::Update(float dt)
{
	SpriteGo::Update(dt);
	sprite.rotate(dt * rotationMultiplier);
	
}
