/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Flamethrower.cpp
Purpose: implement the Flamethrower component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#include "Flamethrower.h"
#include "Transform.h"
//#include "LevelLoader.h"
#include "Body.h"
//#include "..\GameObject.h"
#include "Cursor.h"
#include "Projectile.h"
#include "..\FrameRateController.h"
#include "..\EventManager.h"
#include "..\ObjectFactory.h"


extern FrameRateController* gpFRC;
extern EventManager* gpEventManager;
extern ObjectFactory* gpObjectFactory;


Flamethrower::Flamethrower() : Component("flamethrower") {

}

Flamethrower::~Flamethrower() {

}

void Flamethrower::Update() {
	if(isShooting)
		nextBulletTimer -= gpFRC->GetFrameTime(); //in milliseconds
}

void Flamethrower::Serialize(rapidjson::Value::ConstMemberIterator itr) {

	//added stuff for test
	gpEventManager->Subscribe(EventType::MOUSE_CLICK, this->mpOwner);


}

void Flamethrower::HandleEvent(Event* pEvent) {
	if (isActive && pEvent->mType == EventType::MOUSE_CLICK) {

		MouseClickEvent* pMouseClickEvent = static_cast<MouseClickEvent*>(pEvent);
		if (pMouseClickEvent->heldDown == false) {
			isShooting = false;
			nextBulletTimer = -1;
			return;
		}
		isShooting = true;

		//how many bullets to create
		int bulletsNb = -nextBulletTimer / (1000 / bulletRate) + 1;

		//reset timer
		nextBulletTimer = 1000 / bulletRate;


		for (int i = 0; i < bulletsNb; i++) {
			GameObject* currBullet = gpObjectFactory->BuildObject("FlameBullet.json");

			Body* pB = static_cast<Body*>(currBullet->GetComponent("body"));
			Transform* pT = static_cast<Transform*>(currBullet->GetComponent("T"));
			Projectile* pP = static_cast<Projectile*>(currBullet->GetComponent("projectile"));

			pT->mPositionX = static_cast<Transform*>(mpOwner->GetComponent("T"))->mPositionX;
			pT->mPositionY = static_cast<Transform*>(mpOwner->GetComponent("T"))->mPositionY;

			float directionX = pMouseClickEvent->mPosX  - pT->mPositionX;
			float directionY = pMouseClickEvent->mPosY  - pT->mPositionY;

			float magnitude = sqrt((directionX * directionX) + (directionY * directionY));

			if (magnitude) {
				directionX = directionX / magnitude - 0.15 + rand() % 300 / 1000.0;
				directionY = directionY / magnitude - 0.15 + rand() % 300 / 1000.0;

				pB->mVelocityX = directionX * pP->speed;
				pB->mVelocityY = directionY * pP->speed;
			}
		}
	}
}