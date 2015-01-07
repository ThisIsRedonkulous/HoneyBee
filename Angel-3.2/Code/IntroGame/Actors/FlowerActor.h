#pragma once

#include "stdafx.h"
#include <cstdlib>

class FlowerActor : public PhysicsActor
{
public:
	~FlowerActor();
	FlowerActor(char *q, char *name);
	void answered();
	void ReceiveMessage(Message *m);
	char *question;
	bool answer; //true for left, false for right
};