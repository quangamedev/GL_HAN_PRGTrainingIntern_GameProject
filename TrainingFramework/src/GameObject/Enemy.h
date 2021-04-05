#pragma once
#include "Sprite2DAnimated.h"
#include "Player.h"
class Enemy :
    public Sprite2DAnimated
{
    Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, std::shared_ptr<Player> player);
    ~Enemy();


};

