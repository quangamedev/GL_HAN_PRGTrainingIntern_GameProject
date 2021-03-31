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

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
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
	m_BackgroundWall->Set2DPosition(screenWidth / 2, screenHeight / 2 - 50);
	m_BackgroundWall->SetSize(screenWidth, screenWidth);

	//Background Map
	texture = ResourceManagers::GetInstance()->GetTexture("sMap");
	m_BackgroundMap = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackgroundMap->Set2DPosition(screenWidth / 2, screenHeight / 2 - 50);
	m_BackgroundMap->SetSize(screenWidth, screenWidth);

	//back button
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(50, 50);
	button->SetSize(100, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	//player
	model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	texture = ResourceManagers::GetInstance()->GetTexture("Grass");
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_player = std::make_shared<Sprite2DAnimated>(model, shader, texture, 4.0, 0.1);
	m_player->Set2DPosition(m_BackgroundMap->Get2DPosition());
	m_player->SetSize(50, 50);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
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
		m_player->Set2DRotation(m_player->GetZRotation() + 30);
		std::cout << m_player->GetZRotation() << std::endl;
		std::cout << m_player->Get2DPosition().x << " " << m_player->Get2DPosition().y << std::endl;
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
}

void GSPlay::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	m_player->Update(deltaTime);
}

void GSPlay::Draw()
{
	m_BackgroundMap->Draw();
	m_BackgroundWall->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_player->Draw();
	//m_score->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}