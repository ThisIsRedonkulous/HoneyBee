#include "stdafx.h"
#include "FlowerMessage.h"

FlowerMessage::FlowerMessage(char* messText, const char* questionText, FlowerActor *sender)
	: Message(messText, sender)
{
	flower = sender;
	question = questionText;
}