#pragma once
#include "Sprite2D.h"

class Sprite2DAnimated :
    public Sprite2D
{
protected:
    float m_numFrames;
    float m_currentFrame;
    float m_frameTime;
    float m_currentTime;
public:
    //Sprite2DAnimated(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
    Sprite2DAnimated(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float numFrames, float frameTime);
    ~Sprite2DAnimated();

    void Draw() override;
    void Update(GLfloat deltatime) override;
};

