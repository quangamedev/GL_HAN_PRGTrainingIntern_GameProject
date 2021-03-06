#pragma once
#include "baseobject.h"

class Sprite2D : public BaseObject
{
private:
	std::string		m_Text;
	void			CaculateWorldMatrix();
protected:
	Vector2			m_Vec2DPos;
	GLint			m_iHeight;
	GLint			m_iWidth;
	GLint			m_CollisionRadius;

public:
	Sprite2D(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	Sprite2D(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color);
	~Sprite2D();

	void		Init() override;
	void		Draw();
	void		Update(GLfloat deltatime) override;

	void		SetText(std::string text);
	std::string	GetText();

	void		Set2DPosition(GLfloat x, GLfloat y);
	void		Set2DPosition(Vector2 pos);
	bool		MoveTo2DPosition(GLfloat x, GLfloat y, float speed, GLfloat deltaTime);
	bool		MoveTo2DPosition(Vector2 pos, float speed, GLfloat deltaTime);
	void		MoveInDirection2D(Vector2 dir, float speed, GLfloat deltaTime);

	void		Set2DRotation(GLfloat z);
	GLfloat		GetZRotation();

	void		LookAt2D(GLfloat x, GLfloat y);

	Vector2		Get2DPosition();
	void		SetSize(GLint width, GLint height);

	GLfloat		GetCollisionRadius();

};

