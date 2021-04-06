#pragma once
#include "Sprite2DAnimated.h"
#include "Player.h"
class Enemy :
    public Sprite2DAnimated
{
public:
    enum EnemyState
    {
        run = 0,
        dead
    };
    EnemyState m_State;

    Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float numFrames, float frameTime, std::shared_ptr<Player> player);
    ~Enemy();

    void Update(GLfloat deltaTime) override;
    int GetHealth() { return m_Health; }

    void ChangeState(EnemyState state);

private:

    GLfloat m_Speed;
    GLfloat m_AttackCooldown;
    int m_Health;
    GLfloat m_RankModifier;

    std::shared_ptr<Player> m_Player;

    bool canAttack;
    bool isActive;

    int m_FirstFrame;
    int m_LastFrame;

};

