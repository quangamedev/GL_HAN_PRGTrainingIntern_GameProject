#pragma once
#include "Singleton.h"
#include "Sprite2D.h"

class Sprite2D;

class Collisions : public CSingleton<Collisions>
{
public:
	Collisions();
	~Collisions();
	bool Circle(std::shared_ptr<Sprite2D> obj1, std::shared_ptr<Sprite2D> obj2);
	//bool Circle(std::shared_ptr<Sprite2D> obj1, &obj2);
};

