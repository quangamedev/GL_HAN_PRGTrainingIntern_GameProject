#pragma once
#include "Sprite2D.h"
class Bullet :
    public Sprite2D
{
public:
    Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLfloat tarX, GLfloat tarY);
    ~Bullet();

    void SetMovementDirection(GLfloat x, GLfloat y);

    void Update(GLfloat deltaTime) override;

private:
    GLfloat m_TarX;
    GLfloat m_TarY;
    GLfloat m_BulletSpeed;
    Vector2 m_MovementDirection;
};

