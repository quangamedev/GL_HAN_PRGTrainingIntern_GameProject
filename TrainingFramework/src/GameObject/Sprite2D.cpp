#include "Sprite2D.h"
#include "Shaders.h"
#include "Models.h"
#include "Camera.h"
#include "Texture.h"

extern GLint screenWidth;
extern GLint screenHeight;



void Sprite2D::CaculateWorldMatrix()
{
	Matrix m_Sc, m_T, m_R;
	m_Sc.SetScale(m_Vec3Scale);
	m_T.SetTranslation(m_Vec3Position);

	GLfloat tempZ = (GLfloat)(m_Vec3Rotation.z * PI * -2 / MAX_DEGREE);
	m_R.SetRotationZ(tempZ);
	m_WorldMat = m_Sc * m_R * m_T;
}

Sprite2D::Sprite2D(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: BaseObject()
{
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = nullptr;
	m_pTexture = texture;

	m_Vec3Position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);

	m_CollisionRadius = 0;
}

Sprite2D::Sprite2D(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, Vector4 color)
	: BaseObject()
{
	m_pModel = model;
	m_pShader = shader;
	m_pCamera = nullptr;
	m_pTexture = nullptr;
	m_Color = color;

	m_Vec3Position = Vector3(0, 0, 0);
	m_iHeight = 50;
	m_iWidth = 100;
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
}

Sprite2D::~Sprite2D()
{
}

void Sprite2D::Init()
{
	CaculateWorldMatrix();
}

void Sprite2D::Draw()
{
	glUseProgram(m_pShader->program);
	glBindBuffer(GL_ARRAY_BUFFER, m_pModel->GetVertexObject());
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_pModel->GetIndiceObject());

	GLuint iTempShaderVaribleGLID = -1;
	Matrix matrixWVP;

	matrixWVP = m_WorldMat;//* m_pCamera->GetLookAtCamera();

	if (m_pTexture != nullptr)
	{
		glActiveTexture(GL_TEXTURE0);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, m_pTexture->Get2DTextureAdd());
		if (m_pShader->iTextureLoc[0] != -1)
			glUniform1i(m_pShader->iTextureLoc[0], 0);
	}
	else
	{
		iTempShaderVaribleGLID = -1;
		iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_color");
		if (iTempShaderVaribleGLID != -1)
			glUniform4f(iTempShaderVaribleGLID, m_Color.x, m_Color.y, m_Color.z, m_Color.w);
	}


	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*)"a_posL");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_POSITION);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetAttribLocation((char*) "a_uv");
	if (iTempShaderVaribleGLID != -1)
	{
		glEnableVertexAttribArray(iTempShaderVaribleGLID);
		glVertexAttribPointer(iTempShaderVaribleGLID, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), VETEX_UV);
	}

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_alpha");
	if (iTempShaderVaribleGLID != -1)
		glUniform1f(iTempShaderVaribleGLID, 1.0);

	iTempShaderVaribleGLID = -1;
	iTempShaderVaribleGLID = m_pShader->GetUniformLocation((char*)"u_matMVP");
	if (iTempShaderVaribleGLID != -1)
		glUniformMatrix4fv(iTempShaderVaribleGLID, 1, GL_FALSE, matrixWVP.m[0]);



	glDrawElements(GL_TRIANGLES, m_pModel->GetNumIndiceObject(), GL_UNSIGNED_INT, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Sprite2D::Update(GLfloat deltatime)
{
}



void Sprite2D::SetText(std::string text)
{
	m_Text = text;
}

std::string Sprite2D::GetText()
{
	return m_Text;
}

void Sprite2D::Set2DPosition(GLfloat width, GLfloat height)
{
	m_Vec2DPos.x = width;
	m_Vec2DPos.y = height;

	float xx = (2.0 * m_Vec2DPos.x) / screenWidth - 1.0;
	float yy = 1.0 - (2.0 * m_Vec2DPos.y) / screenHeight;
	m_Vec3Position = Vector3(xx, yy, 1.0);

	CaculateWorldMatrix();
}

void Sprite2D::Set2DPosition(Vector2 pos)
{
	m_Vec2DPos = pos;

	float xx = (2.0 * m_Vec2DPos.x) / screenWidth - 1.0;
	float yy = 1.0 - (2.0 * m_Vec2DPos.y) / screenHeight;
	m_Vec3Position = Vector3(xx, yy, 1.0);

	CaculateWorldMatrix();
}

bool Sprite2D::MoveTo2DPosition(GLfloat x, GLfloat y, float speed, GLfloat deltaTime)
{
	if (Get2DPosition().x - x == 0 && Get2DPosition().y - y == 0)
		return true;
	
	Vector2 tempDir = (Vector2(x,y) - Get2DPosition()).Normalize();
	Set2DPosition(Get2DPosition().x + tempDir.x * speed * deltaTime, Get2DPosition().y + tempDir.y * speed * deltaTime);
	return false;
	
}

bool Sprite2D::MoveTo2DPosition(Vector2 pos, float speed, GLfloat deltaTime)
{
	if (Get2DPosition().x - pos.x == 0 && Get2DPosition().y - pos.y == 0)
		return true;

	Vector2 tempDir = (pos - Get2DPosition()).Normalize();
	Set2DPosition(Get2DPosition().x + tempDir.x * speed * deltaTime, Get2DPosition().y + tempDir.y * speed * deltaTime);
	return false;
}

void Sprite2D::MoveInDirection2D(Vector2 dir, float speed, GLfloat deltaTime)
{
	if (dir.x != 0 || dir.y != 0) {

		Vector2 tempDir = dir.Normalize();

		Set2DPosition(Get2DPosition().x + tempDir.x * speed * deltaTime, Get2DPosition().y + tempDir.y * speed * deltaTime);
	}
}

void Sprite2D::Set2DRotation(GLfloat z)
{
	m_Vec3Rotation = Vector3(m_Vec3Rotation.x, m_Vec3Rotation.y, z);

	CaculateWorldMatrix();
}

GLfloat Sprite2D::GetZRotation()
{
	return m_Vec3Rotation.z;
}

void Sprite2D::LookAt2D(GLfloat x, GLfloat y)
{
	Vector2 target = Vector2(x, y);
	Vector2 currentPos = Get2DPosition();
	Vector2 dir = target - currentPos;

	//user clicks to the left of the player; use of m_iHeight is to make sure that the image isnt already flipped
	if (dir.x < 0 && m_iHeight > 0) {
		SetSize(m_iWidth, -m_iHeight);
	}
	//user clicks to the right of the player
	else if (dir.x > 0 && m_iHeight < 0) {
		SetSize(m_iWidth, -m_iHeight);
	}

	Set2DRotation((-atan2(dir.x, dir.y) * 180 / PI) + 90);

}

Vector2 Sprite2D::Get2DPosition()
{
	return m_Vec2DPos;
}


void Sprite2D::SetSize(GLint width, GLint height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_Vec3Scale = Vector3((float)m_iWidth / screenWidth, (float)m_iHeight / screenHeight, 1);
	CaculateWorldMatrix();
}

GLfloat Sprite2D::GetCollisionRadius()
{
	return m_CollisionRadius;
}
