#pragma once
#include "Sprite2D.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "ResourceManagers.h"
#include "Bullet.h"

class Gun :
    public Sprite2D
{
public:
    Gun(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
    ~Gun();

    void Update(GLfloat deltaTime) override;
    //void Draw();
    void Fire(GLfloat x, GLfloat y);
private:
    std::shared_ptr<Models> m_Model;
    std::shared_ptr<Shaders> m_Shader;
    std::shared_ptr<Texture> m_Texture;

    std::list<std::shared_ptr<Bullet>> m_listBullet;
};

