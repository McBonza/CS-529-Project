/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: EnemyGun.h
Purpose: Header to the EnemyGun component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#pragma once
#include "Component.h"

class GameObject;
class Body;
class Transform;

class EnemyGun : public Component {
public:
	EnemyGun();
	~EnemyGun();

	void Update();
	void Shoot();

	void Serialize(rapidjson::Value::ConstMemberIterator itr);

	//void HandleEvent(Event* pEvent);

public:
	float timeTillNextShot = 1000;
	float shootInterval = 1000; // in milliseconds
	int shootFluctuation = 1; // in milliseconds


	std::string targetTag;

	Body* targetBody;
	Transform* ownerTransform;

private:
private:
};