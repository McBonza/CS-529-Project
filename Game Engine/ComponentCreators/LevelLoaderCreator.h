/*---------------------------------------------------------------------
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
File Name: LevelLoaderCreator.h
Purpose: create the LevelLoader component
Language: c++
Platform:  Visual Studio 2019, Windows 10 x64
Project: CS529_jeremy.l_final
Author: Jeremy Lucas, jeremy.l, 60001220
Creation date: 10/18/2020
----------------------------------------------------------------------*/
#pragma once
#include "ComponentCreator.h"
#include "../Components/LevelLoader.h"


class LevelLoaderCreator : public ComponentCreator {

public:
	virtual Component* Create() {

		return new LevelLoader();

	}

};