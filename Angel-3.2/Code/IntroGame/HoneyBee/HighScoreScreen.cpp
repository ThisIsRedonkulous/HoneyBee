#include "DemoGameManager.h"
#include <cstdlib>
#include "stdafx.h"
#include <cstring>
#include "HighScoreScreen.h"
HighScoreScreen::HighScoreScreen()
{

}

void HighScoreScreen::Start()
{
//	theWorld.ResetWorld();
	loadFile(fopen("HoneyBee/scores.dat", "r"));
}
void HighScoreScreen::loadFile(FILE *infile)
{
	//std::cout << "loading";
	int temp = 1;
	String s = "";
	char *taco = new char[20];
	if (infile == nullptr)
		std::cout << "failed to load config.txt";
	else
	{
		for (int i = 0; i < 10; i++)
		{
			fscanf(infile, "%s %s", names[i].c_str(), scores[i].c_str());
		}
	}
}

void HighScoreScreen::Update(float dt)
{
	for (int i = 0; i < 10; i++)
	{
		DrawGameText(names[i], "Console", 200, i * 40 + 20, 0);
		DrawGameText(scores[i], "Console", 400, i * 40 + 20, 0);
	}
}