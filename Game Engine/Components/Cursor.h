/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: Crusor.h
Purpose: Header to the Cursor component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#pragma once
#include "Component.h"
#include "..\EventManager.h"

class GameObject;

class MouseClickEvent : public Event {
public:
	MouseClickEvent(bool heldDown, float mPosX, float mPosY);
	~MouseClickEvent() { }

	float mPosX, mPosY;
	bool heldDown;
};

//--------------------------------------------------


class Cursor : public Component {
public:
	Cursor();
	~Cursor();

	void Update();
	void Serialize(rapidjson::Value::ConstMemberIterator itr);

	void HandleEvent(Event* pEvent);

public:
	float mOffsetX;
	float mOffsetY;

private:
private:
};