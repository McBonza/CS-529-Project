/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Body.cpp
Purpose: implement the Body component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#include "Body.h"
#include "Tag.h"
#include "Transform.h"
#include "HealthPoints.h"
#include "..\GameObject.h"
#include "..\CollisionManager.h"
#include "..\EventManager.h"
//#include "..\FrameRateController.h"


//extern FrameRateController* gpFRC;


Body::Body() : Component("body") {
	 mPositionX = mPositionY = 0.0f;
	 mPrevPositionX = mPrevPositionY = 0.0f;
	 mVelocityX = mVelocityY = 0.0f;
	 mAccX = mAccY = 0.0f;
	 mTotalForceX = mTotalForceY = 0.0f;
	 mMass = mInvMass = 1.0f;

	 mpShape = nullptr;
}

Body::~Body() {
	if (mpShape != nullptr)
		delete mpShape;
}

void Body::Update(void) {

}

void Body::Serialize(rapidjson::Value::ConstMemberIterator itr) {
	isStatic = itr->value.FindMember("isstatic")->value.GetBool();

	mMass = itr->value.FindMember("mass")->value.GetDouble();

	//mInvMass was useless tbh
	/*if (mMass != 0.0f)
		mInvMass = 1.0f / mMass;
	else
		mInvMass = 0.0f; //object wont move*/

	if(itr->value.HasMember("shapetype")){
		std::string shapeType;
		shapeType = itr->value.FindMember("shapetype")->value.GetString();

		if (shapeType == "circle") {
			mpShape = new ShapeCircle(itr->value.FindMember("radius")->value.GetDouble());
			mpShape->mpOwnerBody = this;
		}
		else if (shapeType == "AABB") {
			mpShape = new ShapeAABB(itr->value.FindMember("left")->value.GetDouble(),
									itr->value.FindMember("right")->value.GetDouble(), 
									itr->value.FindMember("top")->value.GetDouble(),
									itr->value.FindMember("bottom")->value.GetDouble());
			mpShape->mpOwnerBody = this;
		}
	}
}

//////////////////////////////////////////////////apply friction?
void Body::Integrate(float gravity, float deltaTime) {

	Transform* pT = static_cast<Transform*>(mpOwner->GetComponent("T"));

	if (pT != nullptr) {
		mPositionX = pT->mPositionX;
		mPositionY = pT->mPositionY;
	}

	if (isStatic)
		return;

	mPrevPositionX = mPositionX;
	mPrevPositionY = mPositionY;

	//Compute the acceleration
	mTotalForceY += gravity;
	mAccX = mTotalForceX * mMass;
	mAccY = mTotalForceY * mMass;

	mTotalForceX = mTotalForceY = 0.0f;

	//Integrate the Velocity
	mVelocityX = mAccX * deltaTime + mVelocityX;
	mVelocityY = mAccY * deltaTime + mVelocityY;

	//Integrate the Position
	mPositionX = mVelocityX * deltaTime + mPositionX;
	mPositionY = mVelocityY * deltaTime + mPositionY;

	if (pT != nullptr) {
		pT->mPositionX = mPositionX;
		pT->mPositionY = mPositionY;
	}
}


void Body::HandleEvent(Event* pEvent) {

	if (isStatic)
		return;

	if (pEvent->mType == EventType::COLLIDE) {

		CollideEvent* castEvent = static_cast<CollideEvent*>(pEvent);

		if (!static_cast<Tag*>(mpOwner->GetComponent("tag"))->tagName.compare("enemy"))
			if (!static_cast<Tag*>(castEvent->otherObject->GetComponent("tag"))->tagName.compare("player")) {
				static_cast<HealthPoints*>(castEvent->otherObject->GetComponent("healthpoints"))->health -= 99999; //instant death
				return;
			}

		Transform* pT = static_cast<Transform*>(mpOwner->GetComponent("T"));

		if (castEvent->hitTop && mVelocityY < 0)
			mPositionY = mPrevPositionY;

		if (castEvent->hitBot && mVelocityY > 0)
			mPositionY = mPrevPositionY;

		if (castEvent->hitRight && mVelocityX > 0)
			mPositionX = mPrevPositionX;

		if (castEvent->hitLeft && mVelocityX < 0)
			mPositionX = mPrevPositionX;

		if (pT != nullptr) {
			pT->mPositionX = mPositionX;
			pT->mPositionY = mPositionY;
		}
	}

}