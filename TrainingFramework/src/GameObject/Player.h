#pragma once
#include "Sprite2DAnimated.h"
class Player :
    public Sprite2DAnimated
{
private:
    int m_Health;
    int m_Speed;
    int m_Score;
    Vector2 m_MovementDir;
    int m_FirstFrame;
    int m_LastFrame;

    
    
public:
    enum PlayerState
    {
        idle = 0,
        run,
        dead
    };
    PlayerState m_State;

    Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float numFrames, float frameTime);
    ~Player();

    int GetHealth() { return m_Health; }
    int GetScore() { return m_Score; }
    Vector2 GetMovementDirection() { return m_MovementDir; }

    void SetMovementDirection(GLfloat x, GLfloat y);

    void ChangeState(PlayerState state);

    void Update(GLfloat deltatime) override;
    void Move(GLfloat deltaTime);

    //void SetIsMoving
};

