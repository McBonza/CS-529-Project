/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: LevelLoader.h
Purpose: Header to the LevelLoader component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#pragma once
#include "Component.h"


class LevelLoader : public Component {
public:
	LevelLoader();
	~LevelLoader();
	
	void Update();

	void Serialize(rapidjson::Value::ConstMemberIterator itr);

	void LoadLevel();

public:

	int mLevelID;


private:
private:
};