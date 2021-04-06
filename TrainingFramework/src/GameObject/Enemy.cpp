#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float numFrames, float frameTime, std::shared_ptr<Player> player) : Sprite2DAnimated(model, shader, texture, numFrames, frameTime)
{
	m_RankModifier = 3;
	m_Speed = 200.0f - m_RankModifier * 20;
	m_AttackCooldown = 1.5;
	m_Health = 3 + m_RankModifier;

	SetSize(70 + m_RankModifier * 5, 70 + m_RankModifier * 5);

	m_currentFrame = 0;
	m_currentTime = 0;
	m_numFrames = numFrames;
	m_frameTime = frameTime;

	m_FirstFrame = 0;
	m_LastFrame = m_numFrames - 1;
	m_Player = player;
	ChangeState(run);
}

Enemy::~Enemy()
{
}

void Enemy::Update(GLfloat deltaTime)
{
	RunAnimation(deltaTime, m_FirstFrame, m_LastFrame);

	/*if (m_MovementDir.x < 0 && m_iWidth > 0) {
		SetSize(-m_iWidth, m_iHeight);
	}
	else if (m_MovementDir.x > 0 && m_iWidth < 0) {
		SetSize(-m_iWidth, m_iHeight);
	}*/

	//move players movement codes into sprites
}

void Enemy::ChangeState(EnemyState state)
{
	m_State = state;

	switch (m_State)
	{
	case Enemy::run:
		m_FirstFrame = 0;
		m_LastFrame = 6;
		break;
	case Enemy::dead:
		m_FirstFrame = 7;
		m_LastFrame = 7;
		break;
	default:
		break;
	}
}

