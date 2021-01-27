/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Gun.cpp
Purpose: implement the Gun component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#include "Gun.h"
#include "Transform.h"
//#include "LevelLoader.h"
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


Gun::Gun() : Component("gun") {

}

Gun::~Gun() {

}

void Gun::Update() {
}

void Gun::Serialize(rapidjson::Value::ConstMemberIterator itr) {

	//added stuff for test
	gpEventManager->Subscribe(EventType::MOUSE_CLICK, this->mpOwner);


}

void Gun::HandleEvent(Event* pEvent) {
	if (isActive && pEvent->mType == EventType::MOUSE_CLICK) {

		MouseClickEvent* pMouseClickEvent = static_cast<MouseClickEvent*>(pEvent);
		if (pMouseClickEvent->heldDown == true)
			return;
		GameObject * currBullet = gpObjectFactory->BuildObject("Bullet.json");

		Body* pB = static_cast<Body*>(currBullet->GetComponent("body"));
		Transform* pT = static_cast<Transform*>(currBullet->GetComponent("T"));
		Projectile* pP = static_cast<Projectile*>(currBullet->GetComponent("projectile"));

		pT->mPositionX = static_cast<Transform*>(mpOwner->GetComponent("T"))->mPositionX;
		pT->mPositionY = static_cast<Transform*>(mpOwner->GetComponent("T"))->mPositionY;

		float directionX = pMouseClickEvent->mPosX - pT->mPositionX;
		float directionY = pMouseClickEvent->mPosY - pT->mPositionY;

		float magnitude = sqrt((directionX * directionX) + (directionY * directionY));

		if (magnitude) {
			directionX = directionX / magnitude;
			directionY = directionY / magnitude;

			if(directionX > 0)
				pT->mRotationZ =-180 / 3.141592654 * acos(glm::dot(glm::vec2(0, 1), glm::vec2(directionX, directionY)));
			else
				pT->mRotationZ = 180 / 3.141592654 * acos(glm::dot(glm::vec2(0, 1), glm::vec2(directionX, directionY)));

			pB->mVelocityX = directionX * pP->speed;
			pB->mVelocityY = directionY * pP->speed;
		}

	}
}