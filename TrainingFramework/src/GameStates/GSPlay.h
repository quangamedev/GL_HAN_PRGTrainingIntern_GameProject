#pragma once
#include "gamestatebase.h"

class Sprite2D;
class Sprite3D;
class Sprite2DAnimated;
class Text;
class GameButton;
class Player;
class Gun;

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

	
	void SetNewPostionForBullet();

private:
	int m_Key;

	std::shared_ptr<Sprite2D> m_BackgroundWall;
	std::shared_ptr<Sprite2D> m_BackgroundMap;
	std::shared_ptr<Text>  m_Score;
	std::shared_ptr<Player> m_Player;
	std::shared_ptr<Gun> m_Gun;

	std::list<std::shared_ptr<GameButton>>	m_listButton;

};

