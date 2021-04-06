#include "Player.h"

Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float numFrames, float frameTime) : Sprite2DAnimated (model, shader, texture, numFrames, frameTime)
{
	m_Health = 3;
	m_Speed = 100;
	m_Score = 0;
	m_MovementDir = Vector2(0, 0);
	m_FirstFrame = 0;
	m_LastFrame = numFrames - 1;
	m_CollisionRadius = 70;
	ChangeState(PlayerState::idle);
}

Player::~Player()
{
}

void Player::SetMovementDirection(GLfloat x, GLfloat y)
{
	m_MovementDir = Vector2(x, y);
}

void Player::ChangeState(PlayerState state)
{
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
	}
	if (key & MOVE_RIGHT) {
		SetMovementDirection(1, GetMovementDirection().y);
	}
	if (key & MOVE_UP) {
		SetMovementDirection(GetMovementDirection().x, -1);
	}
	if (key & MOVE_DOWN) {
		SetMovementDirection(GetMovementDirection().x, 1);
	}
}
