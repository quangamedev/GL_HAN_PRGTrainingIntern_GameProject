#pragma once
#include "Sprite2D.h"
class Bullet :
    public Sprite2D
{
public:
    Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
    ~Bullet();

    void SetMovementDirection(GLfloat x, GLfloat y);

    void Update(GLfloat deltaTime) override;

    void Init(Vector2 dir, Vector2 rand);
    void Reset();

private:
    GLfloat m_BulletSpeed;
    Vector2 m_MovementDirection;
    bool m_IsActive;
    GLfloat m_Lifetime;
    GLfloat m_Age;
};

