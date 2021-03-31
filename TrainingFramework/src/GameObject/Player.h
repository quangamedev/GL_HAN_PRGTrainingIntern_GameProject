#pragma once
#include "Sprite2DAnimated.h"
class Player :
    public Sprite2DAnimated
{
private:
    int m_Health;
    int m_Speed;
    int m_Score;
    
public:
    Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float numFrames, float frameTime);
    ~Player();

    int GetHealth() { return m_Health; }
    int GetScore() { return m_Score; }

    void Update(GLfloat deltatime) override;
    void Move(GLbyte key, GLfloat deltaTime);

    //void SetIsMoving
};

