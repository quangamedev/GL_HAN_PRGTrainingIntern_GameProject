#include "Gun.h"

Gun::Gun(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture) : Sprite2D(model, shader, texture)
{
}

Gun::~Gun()
{
}

void Gun::Update(GLfloat deltaTime)
{
}

void Gun::Fire(GLfloat x, GLfloat y)
{
	LookAt2D(x, y);

	//fire
}
