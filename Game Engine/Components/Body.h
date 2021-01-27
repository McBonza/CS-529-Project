/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Body.h
Purpose: Header to the Body component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#pragma once
#include "Component.h"

class GameObject;
class Shape;

class Body : public Component {
public:
	Body();
	~Body();

	void Update(void);
	void Serialize(rapidjson::Value::ConstMemberIterator itr);

	void Integrate(float gravity, float deltaTime);

	void HandleEvent(Event* pEvent);

public:
	bool isStatic;

	float mPositionX, mPositionY;
	float mPrevPositionX, mPrevPositionY;
	float mVelocityX, mVelocityY;
	float mAccX, mAccY;
	float mTotalForceX, mTotalForceY;
	float mMass, mInvMass;
	float mFriction;
	// a = Sum F / m (or * 1/m, so we precompute 1/m for speed) 

	Shape* mpShape;

private:
private:
};