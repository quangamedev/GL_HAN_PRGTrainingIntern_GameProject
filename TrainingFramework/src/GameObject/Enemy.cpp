#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, float numFrames, float frameTime, std::shared_ptr<Player> player, std::shared_ptr<Gun> gun) : Sprite2DAnimated(model, shader, texture, numFrames, frameTime)
{
	
	srand(time(NULL));


	m_RankModifier = (rand() % 5) - 2;
	m_Speed = 130 - m_RankModifier * 20 + (int)(player->GetKillCount() / 2);
	m_Health = 3 + m_RankModifier + (int)(player->GetKillCount()/7);

	SetSize(70 + m_RankModifier * 5, 70 + m_RankModifier * 5);
	m_CollisionRadius = 5 + m_RankModifier;

	m_RestDuration = 1.5;
	m_RestTime = 0;
	m_ChaseDuration = 1.5f;
	m_ChaseRange = 90;
	m_CanAttack = true;
	m_IsActive = true;
	m_Waypoint = player->Get2DPosition();
	m_ChangeDirectionTime = 0;
	m_ChangeDirectionDuration = 2;

	m_currentFrame = 0;
	m_currentTime = 0;
	m_numFrames = numFrames;
	m_frameTime = frameTime;
	

	m_FirstFrame = 0;
	m_LastFrame = m_numFrames - 1;
	m_Player = player;
	m_Gun = gun;
	ChangeState(run);
}

Enemy::~Enemy()
{
}

void Enemy::Update(GLfloat deltaTime)
{
	if (m_IsActive) {

		RunAnimation(deltaTime, m_FirstFrame, m_LastFrame);

		//MoveTo2DPosition(10, 10, m_Speed, deltaTime);

		//faces at player
		if (m_Player->Get2DPosition().x - m_Vec2DPos.x < 0 && m_iWidth > 0) {
			SetSize(-m_iWidth, m_iHeight);
		}
		else if (m_Player->Get2DPosition().x - m_Vec2DPos.x > 0 && m_iWidth < 0) {
			SetSize(-m_iWidth, m_iHeight);
		}


		//enemy behaviour
		if (GetDistance(m_Player->Get2DPosition(), Get2DPosition()) > m_ChaseRange) {

			//close in
			//GetNewWaypoint

			if (m_ChangeDirectionTime >= m_ChangeDirectionDuration) {
				m_Waypoint = m_Player->Get2DPosition();
				m_ChangeDirectionTime = rand()% 2;
			}

			m_ChangeDirectionTime += deltaTime;

			MoveTo2DPosition(m_Waypoint.x, m_Waypoint.y, m_Speed, deltaTime);
			ChangeState(run);
		}
		else {
			//chase and attack
			if (!Collisions::GetInstance()->Circle(m_Player, std::make_shared<Sprite2D>(*this)) && m_CanAttack) {

				//chase
				
				MoveTo2DPosition(m_Player->Get2DPosition(), m_Speed, deltaTime);
				ChangeState(run);
			}
			else {
				//successfully attacked by colliding
				//remove players health
				if(m_CanAttack)
				m_Player->ReduceHealth(1);

				//rest
				m_RestTime += deltaTime;
				if (m_RestTime >= m_RestDuration) {
					m_RestTime = 0;
					m_CanAttack = true;
					ChangeState(run);
				}
				else {
					ChangeState(rest);
					m_CanAttack = false;
				}
			}
		}

		//collision with bullet

		for (auto it : m_Gun->GetBulletsList())
		{
			if (Collisions::GetInstance()->Circle(it, std::make_shared<Sprite2D>(*this))) {
				m_Health--;
				if (m_Health <= 0) {
					ChangeState(dead);
					Reset();
					m_Player->IncreaseKillCount();
				}
				it->Reset();
			}
		}
	}

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
	case Enemy::rest:
		m_FirstFrame = 7;
		m_LastFrame = 7;
		break;
	case Enemy::dead:
		m_FirstFrame = 8;
		m_LastFrame = 8;
		break;
	default:
		break;
	}
	
}



GLfloat Enemy::GetDistance(Vector2 pos1, Vector2 pos2)
{
	Vector2 tempVector = pos1 - pos2;
	double distance = sqrt((tempVector.x * tempVector.x) + (tempVector.y * tempVector.y));
	return distance;
}

void Enemy::Reset()
{
	m_IsActive = false;
	Set2DPosition(900, 900);
	m_CollisionRadius = 0;
}

