#include "stdafx.h"
#include "FlowerActor.h"
#include <cstring>

FlowerActor::FlowerActor(char *q, char *name)
{
	question = q;
	answer = false;
	SetName(name);
	char taco[30];
	strcpy_s(taco, "CollisionStartWith");
	strcat_s(taco, name);
	theSwitchboard.SubscribeTo(this, taco);
}

FlowerActor::~FlowerActor()
{
	free(question);
}

void FlowerActor::answered()
{
	SetColor(1, 0, 0, 1);
	char taco[30];
	strcpy_s(taco, "CollisionStartWith");
	strcat_s(taco, GetName()._Myptr());
	theSwitchboard.UnsubscribeFrom(this, taco);
}

void FlowerActor::ReceiveMessage(Message *m)
{
	TypedMessage<char*> *mess = new TypedMessage<char*>("QuestionTime", question);
	theSwitchboard.Broadcast(mess);
}