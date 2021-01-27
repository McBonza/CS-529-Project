/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: HealthPoints.cpp
Purpose: Implement the HealthPoints component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#include "HealthPoints.h"
#include "Tag.h"
#include "..\GameObject.h"
#include "..\LevelManager.h"


extern LevelManager* gpLevelManager;


HealthPoints::HealthPoints() : Component("healthpoints") {
	health = 1;
}

HealthPoints::~HealthPoints() {

}

void HealthPoints::Update() {
	if (health < 0) {
		this->mpOwner->destroyed = true;

		if (!static_cast<Tag*>(mpOwner->GetComponent("tag"))->tagName.compare("enemy"))
			gpLevelManager->nbEnemiesLeft--;

		if (!static_cast<Tag*>(mpOwner->GetComponent("tag"))->tagName.compare("player"))
			gpLevelManager->nextLevel = -2; //lose screen
	}
}



void HealthPoints::Serialize(rapidjson::Value::ConstMemberIterator itr) {

	health = itr->value["value"].GetFloat();

}