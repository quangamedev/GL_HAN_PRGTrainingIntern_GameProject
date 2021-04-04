#pragma once
#include "Sprite2D.h"
class Gun :
    public Sprite2D
{
public:
    Gun(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
    ~Gun();

    void Update(GLfloat deltaTime) override;
    void Fire(GLfloat x, GLfloat y);
};

