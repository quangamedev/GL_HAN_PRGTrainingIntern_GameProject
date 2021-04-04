#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLfloat tarX, GLfloat tarY) : Sprite2D (model, shader, texture)
{
	m_TarX = tarX;
	m_TarY = tarY;
}

Bullet::~Bullet()
{
}

void Bullet::Update(GLfloat deltaTime)
{
	MoveInDirection2D(m_TarX, m_TarY, 100.0f, deltaTime);
	std::cout << Get2DPosition().x << std::endl;
}


