#include "stdafx.h"
#include "FlowerActor.h"
#include "HoneyBee\FlowerMessage.h"
#include <cstring>

FlowerActor::FlowerActor(const char *q, char *name)
{
	question = q;
	//std::cout << question;
	answer = false;
	SetName(name);
	char taco[30];
	strcpy_s(taco, "CollisionStartWith");
	strcat_s(taco, this->GetName().c_str());
	theSwitchboard.SubscribeTo(this, taco);
}

FlowerActor::FlowerActor()
{}

FlowerActor::~FlowerActor()
{
	//delete(question);
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
	FlowerMessage *mess = new FlowerMessage("QuestionTime", question.c_str(), this);
	//std::cout << question;
	theSwitchboard.Broadcast(mess);
}

void FlowerActor::SetQuestion(char *q)
{
	//if (question == nullptr)
	//	question = q;
//	else
	{
	//	free(question);
//		question = q;
	}
}

void FlowerActor::SetAnswer(bool b)
{
	answer = b;
}