#include "Player.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float numFrames, float frameTime) : Sprite2DAnimated (model, shader, texture, numFrames, frameTime)
{
	m_Health = 3;
	m_Speed = 150;
	m_KillCount = 0;
	m_MovementDir = Vector2(0, 0);
	m_FirstFrame = 0;
	m_LastFrame = numFrames - 1;
	m_CollisionRadius = 35;
	ChangeState(PlayerState::idle);

	m_InvulnerableTime = 0;
	m_InvulnerableDuration = 2;
	m_isInvulnerable = false;
}

Player::~Player()
{
}

void Player::ReduceHealth(int amount)
{
	if (!m_isInvulnerable) {

		m_Health -= amount;
		std::cout << m_Health << std::endl;
		m_isInvulnerable = true;
	}
}

void Player::SetMovementDirection(GLfloat x, GLfloat y)
{
	m_MovementDir = Vector2(x, y);
}

void Player::ChangeState(PlayerState state)
{
	if (m_State != state) {
		m_State = state;

		switch (m_State)
		{
		case Player::idle:
			//range from 0-3 perhaps
			m_FirstFrame = 0;
			m_LastFrame = 3;
			break;
		case Player::run:
			m_FirstFrame = 4;
			m_LastFrame = 10;
			break;
		case Player::dead:
			break;
		default:
			break;
		}
	}
	
}

void Player::Update(GLfloat deltaTime)
{
	//std::cout << m_currentFrame << std::endl;
	RunAnimation(deltaTime, m_FirstFrame, m_LastFrame);

	if (m_MovementDir.x < 0 && m_iWidth > 0) {
		SetSize(-m_iWidth, m_iHeight);
	}
	else if (m_MovementDir.x > 0 && m_iWidth < 0) {
		SetSize(-m_iWidth, m_iHeight);
	}

	MoveInDirection2D(m_MovementDir, m_Speed, deltaTime);

	if (m_isInvulnerable) {

		m_InvulnerableTime += deltaTime;

		if (m_InvulnerableTime > m_InvulnerableDuration) {
			m_isInvulnerable = false;
			m_InvulnerableTime = 0;
		}
	}
}

void Player::MovementInputHandling(int key)
{
	SetMovementDirection(0, 0);
	if (!key) {
		SetMovementDirection(0, 0);
		ChangeState(idle);
	}
	else {
		ChangeState(run);
	}

	if (key & MOVE_LEFT) {
		SetMovementDirection(-1, GetMovementDirection().y);
		if (Get2DPosition().x <= 125)
			Set2DPosition(125, Get2DPosition().y);
	}
	if (key & MOVE_RIGHT) {
		SetMovementDirection(1, GetMovementDirection().y);
		if (Get2DPosition().x >= screenWidth - 125)
			Set2DPosition(screenWidth - 125, Get2DPosition().y);
	}
	if (key & MOVE_UP) {
		SetMovementDirection(GetMovementDirection().x, -1);
		if (Get2DPosition().y <= 125)
			Set2DPosition(Get2DPosition().x, 125);
	}
	if (key & MOVE_DOWN) {
		SetMovementDirection(GetMovementDirection().x, 1);
		if (Get2DPosition().y >= screenHeight - 125)
			Set2DPosition(Get2DPosition().x, screenHeight - 125);
	}
}
