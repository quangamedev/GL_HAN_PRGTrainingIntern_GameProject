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
#include <stdlib.h>
#include <time.h>  

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

//extern enum PlayerState;
//extern PlayerState m_State;

GSPlay::GSPlay()
{
	m_Key = 0;
	m_TimeSinceLastSpawn = 0;
	m_SpawnInterval = 1.5;
	m_GameIsOver = false;
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

	m_EnemyModel = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	m_EnemyShader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	m_EnemyTexture = ResourceManagers::GetInstance()->GetTexture("sEnemyAll_strip9");

	//score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("friendlyscribbles");
	m_ScoreText = std::make_shared< Text>(shader, font, "score: " + m_Player->GetKillCount(), TEXT_COLOR::WHITE, 1.0);
	m_ScoreText->Set2DPosition(Vector2(600, 50));

	m_LivesText = std::make_shared< Text>(shader, font, "Live(s): " + m_Player->GetKillCount(), TEXT_COLOR::WHITE, 1.0);
	m_LivesText->Set2DPosition(Vector2(450, 50));

	m_GameOverText = std::make_shared< Text>(shader, font, "GAME OVER", TEXT_COLOR::WHITE, 5.0);
	m_GameOverText->Set2DPosition(screenWidth, screenHeight / 2);

	srand(time(NULL));
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

	//std::cout << x << " " << y << std::endl;
}

void GSPlay::Update(float deltaTime)
{
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	
	if (!m_GameIsOver) {
		m_Player->Update(deltaTime);
		m_Gun->Update(deltaTime);

		m_Gun->Set2DPosition(m_Player->Get2DPosition());

		for (auto it : m_listEnemy)
		{
			if (it->IsActive())
				it->Update(deltaTime);
		}

		SpawnEnemies(deltaTime);
		m_Player->MovementInputHandling(m_Key);

		m_ScoreText->setText("Kill Count: " + std::to_string(m_Player->GetKillCount()));
		m_LivesText->setText("Live(s): " + std::to_string(m_Player->GetHealth()));

		if (m_Player->GetHealth() <= 0) {
			m_GameIsOver = true;
		}
	}
	
	

	
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
	for (auto it : m_listEnemy)
	{
		if(it->IsActive())
		it->Draw();
	}
	m_ScoreText->Draw();
	m_LivesText->Draw();

	if(m_GameIsOver)
	m_GameOverText->Draw();
}

void GSPlay::SpawnEnemies(float deltaTime)
{
	m_TimeSinceLastSpawn += deltaTime;

	if (m_TimeSinceLastSpawn >= m_SpawnInterval) {
		//spawn
		int randTime = ((rand() % (int)m_SpawnInterval + 2) - m_Player->GetKillCount() / 25);
		if (randTime < 0.5)
			randTime += 0.5;
		m_TimeSinceLastSpawn -= randTime;

		std::shared_ptr<Enemy> e = std::make_shared<Enemy>(m_EnemyModel, m_EnemyShader, m_EnemyTexture, 9, 0.1, m_Player, m_Gun);
		m_listEnemy.push_back(e);

		int randX = 0;
		int randY = 0;
		double distance = 0;
		int tries = 0;
		Vector2 randomPos = Vector2(randX, randY);

		do
		{
			randX = rand() % 550 + 125;
			randY = rand() % 550 + 125;
			randomPos = Vector2(randX, randY);

			Vector2 tempVector = randomPos - m_Player->Get2DPosition();
			distance = sqrt((tempVector.x * tempVector.x) + (tempVector.y * tempVector.y));

			tries++;
			
		} while (distance < 170 || tries > 100);
		
		//std::cout << distance << std::endl;
		//b->Init(tempDir, Vector2(randX, randY));
		//set position to be at the end of the gun 50 is the aprrox. length of the gun
		e->Set2DPosition(randomPos);
		
	}

	


}
