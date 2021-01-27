/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Cursor.cpp
Purpose: implement the Cursor component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#include "Cursor.h"
#include "Transform.h"
#include "..\GameObject.h"
#include "..\FrameRateController.h"
#include "..\InputManager.h"
#include "..\..\SDL2.0 Lib\include\SDL_mouse.h"
#include "..\GameObject.h"

extern InputManager* gpInputManager;
//extern FrameRateController* gpFRC;
extern EventManager* gpEventManager;




MouseClickEvent::MouseClickEvent(bool heldDown, float mPosX, float mPosY) : Event(EventType::MOUSE_CLICK) {
	this->mPosX = mPosX;
	this->mPosY = mPosY;
	this->heldDown = heldDown;
}

//----------------------------------------------------------


Cursor::Cursor() : Component("cursor") {

}

Cursor::~Cursor() {

}

void Cursor::Update() {

	Transform* pT = static_cast<Transform*>(mpOwner->GetComponent("T"));

	if (pT != nullptr) {

		pT->mPositionX = gpInputManager->mMousePosX - mOffsetX;
		pT->mPositionY = gpInputManager->mMousePosY - mOffsetY;


		if (gpInputManager->IsButtonTriggered(SDL_BUTTON_LEFT)) {

			MouseClickEvent* pMCE = new MouseClickEvent(false, gpInputManager->mMousePosX, gpInputManager->mMousePosY);
			gpEventManager->BroadcastEventToSubscribers(pMCE);

		}
		if (gpInputManager->IsButtonPressed(SDL_BUTTON_LEFT)) {

			MouseClickEvent* pMCE = new MouseClickEvent(true, gpInputManager->mMousePosX, gpInputManager->mMousePosY);
			gpEventManager->BroadcastEventToSubscribers(pMCE);

		}
	}
}

void Cursor::Serialize(rapidjson::Value::ConstMemberIterator itr) {
	mOffsetX = itr->value["offsetX"].GetFloat();
	mOffsetY = itr->value["offsetY"].GetFloat();

	//added stuff for test
	//gpEventManager->Subscribe(EventType::BUTTON_CLICK, this->mpOwner);
}

void Cursor::HandleEvent(Event* pEvent) {
	/*if (pEvent->mType == EventType::BUTTON_CLICK) {

		Transform* pTransform = static_cast<Transform*>(mpOwner->GetComponent("transform"));

		if (pTransform != nullptr)
			pTransform->mPositionY += 10.0f;
	}*/
}