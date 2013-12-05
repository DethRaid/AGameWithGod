#pragma once
#include "stdafx.h"
#include "BattleActor.h"
#include "Vector3.h" 

class Battle
{
public:
	Battle();
	Battle( Vector3 );
	~Battle();
	void init();
	void update();
	void render();
private:
	BattleActor *fighters;
	Vector3 center;
};

