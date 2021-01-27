/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Button.h
Purpose: Header to the Button component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#pragma once
#include "Component.h"

class GameObject;

class Button : public Component {
public:
	Button();
	~Button();

	void Update();
	void Serialize(rapidjson::Value::ConstMemberIterator itr);

	void HandleEvent(Event* pEvent);

public:
	float mHalfWidth, mHalfHeight;

	bool mIsLevelLoader;

private:
private:
};