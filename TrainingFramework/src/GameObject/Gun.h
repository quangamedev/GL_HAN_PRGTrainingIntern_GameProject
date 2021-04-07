#pragma once
#include "Sprite2D.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "ResourceManagers.h"
#include "Bullet.h"
//random
#include <stdlib.h>
#include <time.h>  

class Gun :
    public Sprite2D
{
public:
    Gun(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
    ~Gun();

    void Update(GLfloat deltaTime) override;
    void Draw() override;
    void Fire(GLfloat x, GLfloat y);

    std::list<std::shared_ptr<Bullet>> GetBulletsList() { return m_listBullet; }
private:
    std::shared_ptr<Models> m_Model;
    std::shared_ptr<Shaders> m_Shader;
    std::shared_ptr<Texture> m_Texture;

    std::list<std::shared_ptr<Bullet>> m_listBullet;

    float m_RecoilRange;
    float m_FireRate;
    float m_FireTime;
    bool m_CanFire;
};

