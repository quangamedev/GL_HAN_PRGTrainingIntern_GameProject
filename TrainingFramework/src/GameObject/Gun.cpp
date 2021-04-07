#include "Gun.h"

Gun::Gun(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture) : Sprite2D(model, shader, texture)
{
	m_Model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	m_Shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Texture = ResourceManagers::GetInstance()->GetTexture("sBullet");
	m_RecoilRange = 0.7;
	m_FireRate = 0.3;
	m_FireTime = 0;
	//init randomness
	srand(time(NULL));
	m_CanFire = true;
}

Gun::~Gun()
{
}

void Gun::Update(GLfloat deltaTime)
{
	for (auto it : m_listBullet)
	{
		it->Update(deltaTime);
	}

	
	m_FireTime += deltaTime;

	if (m_FireTime > m_FireRate) {
		m_CanFire = true;
		m_FireTime = 0;
	}
}

void Gun::Draw()
{
	for (auto it : m_listBullet)
	{
		it->Draw();
	}
	Sprite2D::Draw();
}

void Gun::Fire(GLfloat x, GLfloat y)
{
	if (m_CanFire) {

		//random vector
		float randX = -m_RecoilRange / 2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_RecoilRange / 2 + m_RecoilRange / 2)));
		float randY = -m_RecoilRange / 2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (m_RecoilRange / 2 + m_RecoilRange / 2)));

		//bullets directional vector
		Vector2 tempDir = Vector2(x - Get2DPosition().x, y - Get2DPosition().y).Normalize();

		//make gun look at aim
		LookAt2D(x, y);

		//spawn bullet
		std::shared_ptr<Bullet> b = std::make_shared<Bullet>(m_Model, m_Shader, m_Texture);
		//b->Init(tempDir, Vector2(randX, randY));
		//set position to be at the end of the gun 50 is the aprrox. length of the gun
		b->Set2DPosition(Get2DPosition() + tempDir * 70.0f);
		b->SetSize(40, 30);
		b->SetMovementDirection(tempDir.x + randX, tempDir.y + randY);
		m_listBullet.push_back(b);

		ResourceManagers::GetInstance()->PlaySound("aBullet.wav");

		m_CanFire = false;
	}

	//std::sha
}
