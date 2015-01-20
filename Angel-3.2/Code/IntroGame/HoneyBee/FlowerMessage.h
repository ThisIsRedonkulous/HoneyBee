#pragma once

#include "stdafx.h"
#include <cstdlib>
#include "HoneyBee\FlowerMessage.h"
#include"Actors\FlowerActor.h"

class FlowerMessage : public Message
{
public:
	FlowerMessage(char* messName, const char* questionText, FlowerActor *sender);
	FlowerActor *flower;
	const char* question;
};