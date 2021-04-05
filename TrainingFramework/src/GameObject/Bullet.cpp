#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, GLfloat tarX, GLfloat tarY) : Sprite2D (model, shader, texture)
{
	m_TarX = tarX;
	m_TarY = tarY;
	m_BulletSpeed = 400.0f;
	///std::cout << "x: " << tarX << "y: " << tarY << std::endl;
	m_MovementDirection = Vector2(0, 0);
	m_CollisionRadius = 40;
}

Bullet::~Bullet()
{
}

void Bullet::SetMovementDirection(GLfloat x, GLfloat y)
{
	m_MovementDirection = Vector2(x, y);
}

void Bullet::Update(GLfloat deltaTime)
{
	//move to where the play aims
	MoveInDirection2D(m_MovementDirection, m_BulletSpeed, deltaTime);

	//spins around
	Set2DRotation(GetZRotation() + 500 * deltaTime);
	//std::cout << Get2DPosition().x << std::endl;
}


