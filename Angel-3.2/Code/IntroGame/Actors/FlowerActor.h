#pragma once

#include "stdafx.h"
#include <cstdlib>

class FlowerActor : public PhysicsActor
{
public:
	FlowerActor();
	~FlowerActor();
	FlowerActor(const char *q, char *name);
	void answered();
	void ReceiveMessage(Message *m);
	void SetQuestion(char *q);
	void SetAnswer(bool b);
	String question;
	bool answer; //true for left, false for right
};