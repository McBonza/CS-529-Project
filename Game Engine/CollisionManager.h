#pragma once
#include <list>
#include <tuple>
#include "EventManager.h"

class Body;


class CollideEvent : public Event {

public:
	CollideEvent();
	~CollideEvent();

public:
	bool hitTop, hitBot, hitLeft, hitRight;
	GameObject* otherObject;
};

//---------------------------------------------------


class Shape {
public:
	enum ShapeType {
		CIRCLE,
		AABB,

		NUM
	};

	Shape(ShapeType Type);
	virtual ~Shape() { }

	virtual bool TestPoint(float ptX, float ptY) = 0;

public:
	Body* mpOwnerBody;
	ShapeType mType;

private:

};


//---------------------------------------------------

class ShapeCircle : public Shape {

public:
	ShapeCircle(float Radius);
	~ShapeCircle() { }

	virtual bool TestPoint(float ptX, float ptY);

public:
	float mRadius;

private:
private:
};


//---------------------------------------------------

class ShapeAABB : public Shape {

public:
	ShapeAABB(float Left, float Right, float Top, float Bottom);
	~ShapeAABB() { }
	 
	virtual bool TestPoint(float ptX, float ptY);

public:
	float mLeft, mRight, mTop, mBottom;

private:
private:
};

//---------------------------------------------------

class Contact {

public:
	Contact() {
		mBodies[0] = mBodies[1] = nullptr;
		mCollisionInfo[0] = new CollideEvent();
		mCollisionInfo[1] = new CollideEvent();
	}
	~Contact(){ }

public:
	Body* mBodies[2];
	CollideEvent* mCollisionInfo[2];
};

//---------------------------------------------------

class CollisionManager {

public:
	CollisionManager();
	~CollisionManager();

	void Reset();

	bool CheckCollisionAndGenerateContact(Shape* pShape1, float Pos1X, float Pos1Y, Shape* pShape2, float Pos2X, float Pos2Y);

public:
	std::list<Contact*> mContacts;

	//2D array of functions pointers , used to store the collision functions
	bool (*CollisionFunctions[Shape::ShapeType::NUM][Shape::ShapeType::NUM]) (Shape* pShape1, float Pos1X, float Pos1Y, Shape* pShape2, float Pos2X, float Pos2Y, std::list<Contact*>& mContacts);

}; 