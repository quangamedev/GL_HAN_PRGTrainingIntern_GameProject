#include "Collisions.h"

Collisions::Collisions()
{
}

Collisions::~Collisions()
{
}

bool Collisions::Circle(std::shared_ptr<Sprite2D> obj1, std::shared_ptr<Sprite2D> obj2)
{
	Vector2 tempVector = Vector2((obj1->Get2DPosition().x - obj2->Get2DPosition().x),
		(obj1->Get2DPosition().y - obj2->Get2DPosition().y));

	double distance = sqrt((tempVector.x * tempVector.x) + (tempVector.y * tempVector.y));
	double obj1Radius = obj1->GetCollisionRadius();
	double obj2Radius = obj2->GetCollisionRadius();
	double combinedDistance = obj1Radius + obj2Radius;

	return distance < combinedDistance;
}
