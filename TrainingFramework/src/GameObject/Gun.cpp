#include "Gun.h"

Gun::Gun(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture) : Sprite2D(model, shader, texture)
{
	m_Model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	m_Shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_Texture = ResourceManagers::GetInstance()->GetTexture("sBullet");
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

//void Gun::Draw()
//{
//	for (auto it : m_listBullet)
//	{
//		it->Draw();
//	}
//}

void Gun::Fire(GLfloat x, GLfloat y)
{
	//u need to update bullet and draw
	LookAt2D(x, y);
	printf("A");
	//fire
	std::shared_ptr<Bullet> b = std::make_shared<Bullet>(m_Model, m_Shader, m_Texture, x, y);
	m_listBullet.push_back(b);
	b->Draw();
}
