/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Follow.cpp
Purpose: Implement the Follow component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#include "Follow.h"
#include "Body.h"
#include "Tag.h"
#include "SpriteAnimator.h"
#include "..\GameObject.h"
#include "..\GameObjectManager.h"

extern GameObjectManager* gpGameObjectManager;

Follow::Follow() : Component("follow") {
	targetBody = nullptr;
}

Follow::~Follow() {

}

void Follow::Update() {
	float directionX = targetBody->mPositionX - ownerBody->mPositionX;
	float directionY = targetBody->mPositionY - ownerBody->mPositionY;

	float magnitude = sqrt((directionX * directionX) + (directionY * directionY));

	directionX = directionX / magnitude;
	directionY = directionY / magnitude;

	SpriteAnimator* pSA = static_cast<SpriteAnimator*>(mpOwner->GetComponent("spriteAnimator"));

	if (abs(directionX) > abs(directionY)) {
		if(directionX > 0)
			pSA->currSprite = pSA->mSprites["right"];
		else
			pSA->currSprite = pSA->mSprites["left"];
	}
	else {
		if (directionY > 0)
			pSA->currSprite = pSA->mSprites["down"];
		else
			pSA->currSprite = pSA->mSprites["up"];
	}

	ownerBody->mVelocityX = directionX * speed;
	ownerBody->mVelocityY = directionY * speed;
}



void Follow::Serialize(rapidjson::Value::ConstMemberIterator itr) {

	ownerBody = static_cast<Body*>(mpOwner->GetComponent("body")); //is here cuz cant put it in default ctor

	targetTag = itr->value["targettag"].GetString();
	speed = itr->value["speed"].GetFloat();

	//search old objects
	for (auto pGO : gpGameObjectManager->mGameObjects) {

		if (static_cast<Tag*>(pGO->GetComponent("tag"))->tagName.compare(targetTag) == 0) //they re the same
			targetBody = static_cast<Body*>(pGO->GetComponent("body"));
	}
	//search new objects created within this game loop
	for (auto pGO : gpGameObjectManager->mAddedGameObjects) {

		if (static_cast<Tag*>(pGO->GetComponent("tag"))->tagName.compare(targetTag) == 0) //they re the same
			targetBody = static_cast<Body*>(pGO->GetComponent("body"));
	}
}