#include "Player.h"

Player::Player(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float numFrames, float frameTime) : Sprite2DAnimated (model, shader, texture, numFrames, frameTime)
{
	m_Health = 3;
	m_Speed = 100;
	m_Score = 0;
}

Player::~Player()
{
}

void Player::Update(GLfloat deltatime)
{
	//Update(deltatime);
	Sprite2DAnimated::Update(deltatime);
	
	if (KEY_MOVE_RIGHT) {
		//Set2DPosition(Get2DPosition().x + m_Speed * deltatime, Get2DPosition().y);
	}
}

void Player::Move(GLbyte key, GLfloat deltaTime)
{
	switch (key)
	{
	case KEY_MOVE_RIGHT:
		std::cout << "yeet\n";
	default:
		break;
	}
}
