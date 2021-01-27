/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Component.h
Purpose: Header to the component class
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#pragma once
#include <fstream>
#include "../rapidjson/document.h"
#include "../rapidjson/filereadstream.h"
#include "../rapidjson/istreamwrapper.h"

class GameObject;
class Event;


//Abstract class cuz Update() is pure virtual
class Component {

public:
	Component(std::string Type);
	virtual ~Component() {}

	virtual void Update() = 0;

	std::string GetType() { return mType; }

	virtual void Serialize(rapidjson::Value::ConstMemberIterator itr) = 0;
	virtual void HandleEvent(Event* pEvent) {}

public:

	GameObject* mpOwner;


private:
private:
	std::string mType;
};