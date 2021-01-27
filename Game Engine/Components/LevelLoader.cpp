/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: LevelLoader.cpp
Purpose: Implement the LevelLoader component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#include "LevelLoader.h"
#include "..\LevelManager.h"

extern LevelManager* gpLevelManager;

LevelLoader::LevelLoader() : Component("levelloader") {
	mLevelID = 1;
}

LevelLoader::~LevelLoader() {

}

void LevelLoader::Update() {

}

void LevelLoader::Serialize(rapidjson::Value::ConstMemberIterator itr) {

	mLevelID = itr->value["id"].GetFloat();

}

void LevelLoader::LoadLevel() {
	gpLevelManager->nextLevel = mLevelID;
}