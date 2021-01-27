/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: EnemyGun.cpp
Purpose: implement the EnemyGun component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#include "EnemyGun.h"
#include "Transform.h"
#include "Tag.h"
#include "Body.h"
//#include "..\GameObject.h"
#include "Cursor.h"
#include "Projectile.h"
#include "..\FrameRateController.h"
#include "..\EventManager.h"
#include "..\ObjectFactory.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


extern FrameRateController* gpFRC;
extern EventManager* gpEventManager;
extern ObjectFactory* gpObjectFactory;


EnemyGun::EnemyGun() : Component("enemygun") {

}

EnemyGun::~EnemyGun() {

}

void EnemyGun::Update() {
	timeTillNextShot -= gpFRC->GetFrameTime(); //in milliseconds
	
	if (timeTillNextShot < 0) { //time to shoot
		timeTillNextShot = shootInterval + (rand() % shootFluctuation); //reset timer 
		Shoot();
	}
}

void EnemyGun::Shoot() {
	GameObject* currBullet = gpObjectFactory->BuildObject("EnemyBullet.json");

	Transform* pT = static_cast<Transform*>(currBullet->GetComponent("T"));
	Body* pB = static_cast<Body*>(currBullet->GetComponent("body"));
	Projectile* pP = static_cast<Projectile*>(currBullet->GetComponent("projectile"));

	pT->mPositionX = static_cast<Transform*>(mpOwner->GetComponent("T"))->mPositionX;
	pT->mPositionY = static_cast<Transform*>(mpOwner->GetComponent("T"))->mPositionY;

	float directionX = targetBody->mPositionX - ownerTransform->mPositionX;
	float directionY = targetBody->mPositionY - ownerTransform->mPositionY;

	float magnitude = sqrt((directionX * directionX) + (directionY * directionY));

	if (magnitude) {
		directionX = directionX / magnitude;
		directionY = directionY / magnitude;

		if (directionX > 0)
			pT->mRotationZ = -180 / 3.141592654 * acos(glm::dot(glm::vec2(0, 1), glm::vec2(directionX, directionY)));
		else
			pT->mRotationZ = 180 / 3.141592654 * acos(glm::dot(glm::vec2(0, 1), glm::vec2(directionX, directionY)));

		pB->mVelocityX = directionX * pP->speed;
		pB->mVelocityY = directionY * pP->speed;
	}
}

void EnemyGun::Serialize(rapidjson::Value::ConstMemberIterator itr) {

	shootInterval = itr->value.FindMember("shootinterval")->value.GetDouble();
	shootFluctuation = itr->value.FindMember("shootfluctuation")->value.GetDouble();

	ownerTransform = static_cast<Transform*>(mpOwner->GetComponent("T")); //is here cuz cant put it in default ctor

	targetTag = itr->value["targettag"].GetString();

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

	timeTillNextShot = shootInterval * 3 + (rand() % shootFluctuation);; //set timer 
}
