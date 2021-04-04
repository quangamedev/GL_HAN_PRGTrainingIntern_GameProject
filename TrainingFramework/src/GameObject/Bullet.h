#pragma once
#include "Sprite2D.h"
class Bullet :
    public Sprite2D
{
public:
    Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLfloat tarX, GLfloat tarY);
    ~Bullet();

    void Update(GLfloat deltaTime) override;
    void SetMovementDirection2D(GLfloat x, GLfloat y);

private:
    GLfloat m_TarX;
    GLfloat m_TarY;
};

