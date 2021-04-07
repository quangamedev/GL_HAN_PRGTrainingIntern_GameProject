#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "Sprite2DAnimated.h"
#include "Player.h"
#include "Gun.h"
#include "Enemy.h"
#include "Collisions.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

//extern enum PlayerState;
//extern PlayerState m_State;

GSPlay::GSPlay()
{
	m_Key = 0;
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("sWall");

	//BackGround Wall
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackgroundWall = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackgroundWall->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackgroundWall->SetSize(screenWidth - 100, screenWidth - 100);

	//Background
	texture = ResourceManagers::GetInstance()->GetTexture("sBg");
	m_Background = std::make_shared<Sprite2D>(model, shader, texture);
	m_Background->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_Background->SetSize(screenWidth * 2, screenWidth * 2);

	//Background Map
	texture = ResourceManagers::GetInstance()->GetTexture("sMap");
	m_BackgroundMap = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackgroundMap->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackgroundMap->SetSize(screenWidth - 100, screenWidth - 100);

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(40, 40);
	button->SetSize(70, 70);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	//player
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	texture = ResourceManagers::GetInstance()->GetTexture("sPlayerAll_strip11");
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_Player = std::make_shared<Player>(model, shader, texture, 11, 0.1);
	m_Player->Set2DPosition(m_BackgroundMap->Get2DPosition());
	m_Player->SetSize(70, 70);

	//gun
	texture = ResourceManagers::GetInstance()->GetTexture("sGunPivoted");
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Gun = std::make_shared<Gun>(model, shader, texture);
	m_Gun->Set2DPosition(m_BackgroundMap->Get2DPosition());
	m_Gun->SetSize(160, 40);

	//enemy
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("sEnemyAll_strip9");
	m_Dummy = std::make_shared<Enemy>(model, shader, texture, 9, 0.1, m_Player, m_Gun);
	m_Dummy->Set2DPosition(m_BackgroundMap->Get2DPosition() + Vector2(20, 20));

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_Score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_Score->Set2DPosition(Vector2(5, 25));
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	switch (key)
	{
	case KEY_MOVE_RIGHT:
		if (bIsPressed)
			m_Key |= MOVE_RIGHT;
		else
			m_Key ^= MOVE_RIGHT;
		break;
	case KEY_MOVE_LEFT:
		if (bIsPressed)
			m_Key |= MOVE_LEFT;
		else
			m_Key ^= MOVE_LEFT;
		break;
	case KEY_MOVE_FORWARD:
		if (bIsPressed)
			m_Key |= MOVE_UP;
		else
			m_Key ^= MOVE_UP;
		break;
	case KEY_MOVE_BACKWARD:
		if (bIsPressed)
			m_Key |= MOVE_DOWN;
		else
			m_Key ^= MOVE_DOWN;
		break;
	default:
		break;
	}

}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}

	if(bIsPressed)
	m_Gun->Fire(x,y);

	std::cout << x << " " << y << std::endl;
}

void GSPlay::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	m_Player->Update(deltaTime);
	m_Dummy->Update(deltaTime);
	m_Gun->Update(deltaTime);

	m_Gun->Set2DPosition(m_Player->Get2DPosition());

	for (auto it : m_Gun->GetBulletsList())
	{
		
		if (Collisions::GetInstance()->Circle(it, m_Player)) {
			
		}
		if (Collisions::GetInstance()->Circle(it, m_Dummy)) {
			if (m_Dummy->GetState() == Enemy::rest) {

				m_Dummy->ChangeState(Enemy::dead);
			}
			else
				m_Dummy->ChangeState(Enemy::rest);

			
		}
		
	}


	m_Player->MovementInputHandling(m_Key);


}

void GSPlay::Draw()
{
	m_Background->Draw();
	m_BackgroundMap->Draw();
	m_BackgroundWall->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_Gun->Draw();
	m_Player->Draw();
	m_Dummy->Draw();
	//m_Score->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}