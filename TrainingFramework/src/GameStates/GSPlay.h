#pragma once
#include "gamestatebase.h"

class Sprite2D;
class Sprite3D;
class Sprite2DAnimated;
class Text;
class GameButton;
class Player;
class Gun;
class Enemy;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

	void SpawnEnemies(float deltaTime);

private:
	int m_Key;
	float m_SpawnInterval;
	float m_TimeSinceLastSpawn;
	bool m_GameIsOver;

	std::shared_ptr<Sprite2D> m_Background;
	std::shared_ptr<Sprite2D> m_BackgroundWall;
	std::shared_ptr<Sprite2D> m_BackgroundMap;
	std::shared_ptr<Text>  m_ScoreText;
	std::shared_ptr<Text>  m_LivesText;
	std::shared_ptr<Text>  m_GameOverText;
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Gun> m_Gun;
	
	std::shared_ptr<Models> m_EnemyModel;
	std::shared_ptr<Shaders> m_EnemyShader;
	std::shared_ptr<Texture> m_EnemyTexture;

	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Enemy>>	m_listEnemy;

};

