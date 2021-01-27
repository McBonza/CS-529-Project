/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Controller.cpp
Purpose: Implement the controller component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#include "Controller.h"
#include "..\InputManager.h"
#include "..\..\SDL2.0 Lib\include\SDL_scancode.h"
#include "..\..\SDL2.0 Lib\include\SDL_mouse.h"
#include "..\GameObject.h"
#include "Transform.h"
#include "Body.h"
#include "SpriteAnimator.h"
#include "Sprite.h"
#include "Cursor.h"
#include "Gun.h"
#include "Flamethrower.h"
#include "..\EventManager.h"


extern InputManager* gpInputManager;
extern EventManager* gpEventManager;


PlayerHitEvent::PlayerHitEvent() : Event(EventType::PLAYER_HIT) {

}

//----------------------------------------------------------


Controller::Controller() : Component("controller") {
}

Controller::~Controller() {

}

void Controller::Update() {

	Transform* pT = static_cast<Transform*>(mpOwner->GetComponent("T"));

	Body* pBody = static_cast<Body*>(mpOwner->GetComponent("body"));

	SpriteAnimator* pSA  = static_cast<SpriteAnimator*>(mpOwner->GetComponent("spriteAnimator"));

	if (pT != nullptr) {
		//movement
		pBody->mVelocityX = 0;
		pBody->mVelocityY = 0;

		float directionX = 0;
		float directionY = 0;

		if (gpInputManager->IsKeyPressed(SDL_SCANCODE_UP) || gpInputManager->IsKeyPressed(SDL_SCANCODE_W)) {
			directionY = -1;
			pSA->currSprite = pSA->mSprites["up"];
		}
		else if (gpInputManager->IsKeyPressed(SDL_SCANCODE_DOWN) || gpInputManager->IsKeyPressed(SDL_SCANCODE_S)) {
			directionY = 1;
			pSA->currSprite = pSA->mSprites["down"];
		}
		if (gpInputManager->IsKeyPressed(SDL_SCANCODE_LEFT) || gpInputManager->IsKeyPressed(SDL_SCANCODE_A)) {
			directionX = -1;
			pSA->currSprite = pSA->mSprites["left"];
		}
		else if (gpInputManager->IsKeyPressed(SDL_SCANCODE_RIGHT) || gpInputManager->IsKeyPressed(SDL_SCANCODE_D)) {
			directionX = 1;
			pSA->currSprite = pSA->mSprites["right"];
		}

		if(directionX == 0 && directionY == 0)
			pSA->currSprite = pSA->mSprites["idle"];

		float magnitude = sqrt((directionX * directionX) + (directionY * directionY));

		if (magnitude) {
			directionX = directionX / magnitude;
			directionY = directionY / magnitude;

			pBody->mVelocityX = directionX * speed;
			pBody->mVelocityY = directionY * speed;
		}

		//rotation
		if (gpInputManager->IsKeyPressed(SDL_SCANCODE_E)) {
			pT->mRotationZ += 5;
		}
		else if (gpInputManager->IsKeyPressed(SDL_SCANCODE_Q)) {
			pT->mRotationZ -= 5;
		}

		//gun - i should have made an array that hold the class weapon,
		//		from which all the weapons inherit so i can manage 
		//		them more easily, but im only making two weapons so it s fine.
		if (gpInputManager->IsKeyTriggered(SDL_SCANCODE_1)) {
			static_cast<Gun*>(mpOwner->GetComponent("gun"))->isActive = true;
			static_cast<Flamethrower*>(mpOwner->GetComponent("flamethrower"))->isActive = false;
		}
		if (gpInputManager->IsKeyTriggered(SDL_SCANCODE_2)) {
			static_cast<Gun*>(mpOwner->GetComponent("gun"))->isActive = false;
			static_cast<Flamethrower*>(mpOwner->GetComponent("flamethrower"))->isActive = true;
		}

		/*pBody->mPositionX = gpInputManager->mMousePosX;
		pBody->mPositionY = gpInputManager->mMousePosY;
		pT->mPositionX = gpInputManager->mMousePosX;
		pT->mPositionY = gpInputManager->mMousePosY;*/
	}
}


void Controller::Serialize(rapidjson::Value::ConstMemberIterator itr) {
	speed = itr->value["speed"].GetFloat();
}


void Controller::HandleEvent(Event* pEvent) {
/*
	if (pEvent->mType == EventType::COLLIDE) {

		Body* pBody = static_cast<Body*>(mpOwner->GetComponent("body"));

		Transform* pTransform = static_cast<Transform*>(mpOwner->GetComponent("transform"));

		if (pBody != nullptr) {
			pTransform->mPositionX -= pBody->mVelocityX/250;
			pTransform->mPositionY -= pBody->mVelocityY/250;
		}

		//PlayerHitEvent phe;
		//gpEventManager->BroadcastEvent(&phe);

		PlayerHitEvent * pPHE = new PlayerHitEvent(); 
		pPHE->mTimer = 2.0f;
		gpEventManager->AddTimedEvent(pPHE);
	}*/
}