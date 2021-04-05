#include "Gun.h"

Gun::Gun(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture) : Sprite2D(model, shader, texture)
{
	m_Model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	m_Shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Texture = ResourceManagers::GetInstance()->GetTexture("sBullet");
	recoilRange = 0.5;
	//init randomness
	srand(time(NULL));
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
	//random vector
	float randX = -recoilRange/2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (recoilRange/2 + recoilRange / 2)));
	float randY = -recoilRange/2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (recoilRange/2 + recoilRange / 2)));
	
	//bullets directional vector
	Vector2 tempDir = Vector2(x - Get2DPosition().x, y - Get2DPosition().y).Normalize();
	
	//make gun look at aim
	LookAt2D(x, y);

	//spawn bullet
	std::shared_ptr<Bullet> b = std::make_shared<Bullet>(m_Model, m_Shader, m_Texture, x, y);

	//set position to be at the end of the gun 50 is the aprrox. length of the gun
	b->Set2DPosition(Get2DPosition() + tempDir * 60.0f);
	b->SetSize(40, 30);
	b->SetMovementDirection(tempDir.x + randX, tempDir.y + randY);
	m_listBullet.push_back(b);
	
	ResourceManagers::GetInstance()->PlaySound("aBullet.wav");
}
