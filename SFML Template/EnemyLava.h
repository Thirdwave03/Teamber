#pragma once
#include "Enemy.h"
class EnemyLava :
    public Enemy
{
protected:
    std::string texidLava = "graphics/Lava.png";
    sf::Vector2f speed = { 270.f,0.f };

public:
    EnemyLava();
    EnemyLava(const std::string texId);
    ~EnemyLava() = default;
    EnemyLava(const EnemyLava& other) = default;
    EnemyLava& operator=(const EnemyLava& other) = default;

    void Update(float dt) override;
    void Reset() override;
    void SetSpeed(sf::Vector2f speed_in) override;
    void Draw(sf::RenderWindow& window) override;
    void SetPosition(const sf::Vector2f pos);
    sf::FloatRect GGB() const override;
};
