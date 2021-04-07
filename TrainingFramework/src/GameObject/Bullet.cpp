#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture) : Sprite2D (model, shader, texture)
{
	m_BulletSpeed = 400.0f;
	///std::cout << "x: " << tarX << "y: " << tarY << std::endl;
	m_MovementDirection = Vector2(0, 0);
	m_CollisionRadius = 40;
	m_IsActive = true;
	m_Lifetime = 4;
	m_Age = 0;
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
	if (m_IsActive) {
		m_Age += deltaTime;
		if (m_Age >= m_Lifetime)
			Reset();

		//move to where the play aims
		MoveInDirection2D(m_MovementDirection, m_BulletSpeed, deltaTime);

		//spins around
		Set2DRotation(GetZRotation() + 500 * deltaTime);
		//std::cout << Get2DPosition().x << std::endl;
	}
	
}

void Bullet::Init(Vector2 dir, Vector2 rand)
{
	m_IsActive = true;
	Set2DPosition(Get2DPosition() + dir * 70.0f);
	SetSize(40, 30);
	SetMovementDirection(dir.x + rand.x, dir.y + rand.y);
}

void Bullet::Reset()
{
	m_IsActive = false;
	Set2DPosition(900, 900);
	m_CollisionRadius = 0;
}


