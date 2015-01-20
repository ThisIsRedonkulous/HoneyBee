#pragma once

#include "DemoGameManager.h"
#include <cstdlib>
#include "stdafx.h"
#include <cstring>
class HighScoreScreen : public DemoScreen
{
public:
	HighScoreScreen();
	void loadFile(FILE *file);
	virtual void Start();
	virtual void Update(float dt);
	void displayScore(String name, int score, int pos);
	//virtual void ReceiveMessage(Message *message);
private:
	String scores[10];
	String names[10];
};