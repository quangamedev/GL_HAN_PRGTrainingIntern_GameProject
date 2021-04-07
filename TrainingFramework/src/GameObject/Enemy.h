#pragma once
#include "Sprite2DAnimated.h"
#include "Player.h"
#include "Collisions.h"
#include "Gun.h"
//random
#include <stdlib.h>
#include <time.h>  

class Enemy :
    public Sprite2DAnimated
{
public:
    enum EnemyState
    {
        run = 0,
        rest,
        dead
    };
    EnemyState m_State;

    Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float numFrames, float frameTime, std::shared_ptr<Player> player, std::shared_ptr<Gun> gun);
    ~Enemy();

    void Update(GLfloat deltaTime) override;
    int GetHealth() { return m_Health; }

    void ChangeState(EnemyState state);
    EnemyState GetState() { return m_State; }
    GLfloat GetDistance(Vector2 pos1, Vector2 pos2);

    bool IsActive() { return m_IsActive; }
    void Reset();

private:

    GLfloat m_Speed;
    int m_Health;
    GLfloat m_RankModifier;

    GLfloat m_RestDuration;
    GLfloat m_RestTime;
    GLfloat m_ChaseRange;
    GLfloat m_ChaseDuration;
    Vector2 m_Waypoint;
    GLfloat m_ChangeDirectionDuration;
    GLfloat m_ChangeDirectionTime;

    std::shared_ptr<Player> m_Player;
    std::shared_ptr<Gun> m_Gun;

    bool m_CanAttack;
    bool m_IsActive;

    int m_FirstFrame;
    int m_LastFrame;


};

