/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Button.cpp
Purpose: implement the Button component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#include "Button.h"
#include "Transform.h"
#include "LevelLoader.h"
#include "Body.h"
#include "..\GameObject.h"
#include "Cursor.h"
//#include "..\FrameRateController.h"
#include "..\EventManager.h"
#include "..\CollisionManager.h"


//extern FrameRateController* gpFRC;
extern EventManager* gpEventManager;


Button::Button() : Component("button") {

}

Button::~Button() {

}

void Button::Update() {

}

void Button::Serialize(rapidjson::Value::ConstMemberIterator itr) {
	//late init
	ShapeAABB* pShapeAABB = static_cast<ShapeAABB*>(static_cast<Body*>(mpOwner->GetComponent("body"))->mpShape);
	mHalfWidth = (pShapeAABB->mRight - pShapeAABB->mLeft) / 2;
	mHalfHeight = (pShapeAABB->mBottom - pShapeAABB->mTop) / 2;

	//added stuff for test
	gpEventManager->Subscribe(EventType::MOUSE_CLICK, this->mpOwner);


	if (mpOwner->GetComponent("levelloader") != nullptr) {
		mIsLevelLoader = true;
	}
}

void Button::HandleEvent(Event* pEvent) {
	if (pEvent->mType == EventType::MOUSE_CLICK) {

		MouseClickEvent* pMouseClickEvent = static_cast<MouseClickEvent*>(pEvent);

		Transform* pT = static_cast<Transform*>(mpOwner->GetComponent("T"));
		
		if (pMouseClickEvent->heldDown == true)
			return;

		if (pT->mPositionX - mHalfWidth < pMouseClickEvent->mPosX && pMouseClickEvent->mPosX < pT->mPositionX + mHalfWidth)
			if (pT->mPositionY - mHalfHeight < pMouseClickEvent->mPosY && pMouseClickEvent->mPosY < pT->mPositionY + mHalfHeight)
				if (mIsLevelLoader) {
					static_cast<LevelLoader*>(mpOwner->GetComponent("levelloader"))->LoadLevel();
				}
					
	}
}